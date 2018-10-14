#include "SRJF.h"
#include <iostream>

void SRJF::run() {
    ran = true;
    int tick = 0;
    auto process_coming_in = newq.begin();

    while ( true ) {
        std::cout << tick << " " << running_process.pid
        << "[" << running_process.remaining_burst_time << "] "
        << "------------------------------------------" << std::endl;

        if ( process_coming_in != newq.end() ) {
            if ((*process_coming_in).arrival_time == tick) {
                // insert the new process at the back of the ready queue
                std::cout << std::endl << "Adding process " << (*process_coming_in).pid << std::endl;
                readyq.insertAtBack((*process_coming_in));
                ++process_coming_in;

                std::cout << "Ready Q: ";
                readyq.printVals();
                std::cout << std::endl;

                if ( tick == 0 ) {
                    std::cout << std::endl << "This is the first tick ";
                    running_process = *( readyq.begin() );
                    std::cout << "so we are going to run " << running_process.pid << std::endl;
                    readyq.deleteAtFront();
                    working = true;
                }
                else
                {
                    std::cout << std::endl << "Looking for new shortest job" << std::endl;
                    int runner = 0;
                    int shortest_job_pos = 0;
                    int shortest_job_time = std::numeric_limits<int>::max();
                    PCB shortest_job;

                    for (PCB &proc : readyq) {
                        std::cout << "\tComparing " << running_process.pid << "["
                            << running_process.remaining_burst_time << "] -> "
                            << proc.pid << "[" << proc.remaining_burst_time << "]" << std::endl;

                        ++runner;
                        if (proc.remaining_burst_time < shortest_job_time) {
                            shortest_job_time = proc.remaining_burst_time;
                            shortest_job_pos = runner;
                            shortest_job = proc;
                        }
                    }

                    if (shortest_job.pid != -1
                        && shortest_job.burst_time < running_process.remaining_burst_time) {
                        if ( shortest_job_pos == 1 )
                        {
                            readyq.deleteAtFront();
                        }
                        else if ( shortest_job_pos == readyq.length() )
                        {
                            readyq.deleteAtBack();
                        }
                        else
                        {
                            readyq.deleteBeforePosition(shortest_job_pos);
                        }

                        readyq.insertAtBack(running_process);
                        running_process = shortest_job;
                        std::cout << "Context switch to " << running_process.pid << std::endl;
                        ++num_context_switches;
                    } else {
                        std::cout << "Continue working on " << running_process.pid <<
                              "[" << running_process.remaining_burst_time << "]" << std::endl;
                    }

                }
            }
        }

        if ( !working && readyq.empty() ) {
            // we are not working and there are no more processes in the ready queue
            break;
        }

        if ( !working ) {
            // the ready queue is not empty so we know the iterator will not be nullptr
            std::cout << std::endl << "We finished " << running_process.pid <<
            " and now we need to find the next one" << std::endl;
            findAndRemoveShortestJob();
            std::cout<< "The next process is " << running_process.pid << std::endl;
            working = true;
        }

        for ( PCB &proc : readyq ) {
            ++(proc.waiting_time);  // update the waiting times for each process not running
        }

        if ( working ) {
            if ( running_process.response_time == -1 ) {
                // this is the first time working on the process
                running_process.response_time = tick;
            }
            // we need to do work on the currently running process
            --(running_process.remaining_burst_time);

            // check if the process is finished
            if ( running_process.remaining_burst_time == 0 ) {
                // it is finished
                // set the time it finished and add it to the terminated queue
                running_process.finish_time = tick;
                terminatedq.insertAtBack( running_process );
                working = false;
            }
        }

        ++tick;
    }

    std::cout << "Finished Processing" << std::endl;

    calcStats();
}

void SRJF::findAndRemoveShortestJob() {
    int runner = 0;
    int shortest_job_pos = 0;
    int shortest_job = std::numeric_limits<int>::max();

    for ( PCB &proc : readyq ) {
        std::cout << "\tComparing " << running_process.pid << "["
                  << running_process.remaining_burst_time << "] -> "
                  << proc.pid << "[" << proc.remaining_burst_time << "]" << std::endl;
        ++runner;
        if ( proc.remaining_burst_time < shortest_job ) {
            shortest_job = proc.remaining_burst_time;
            shortest_job_pos = runner;
            running_process = proc;
        }
    }

    if ( shortest_job_pos == 1 )
    {
        readyq.deleteAtFront();
    }
    else if ( shortest_job_pos == readyq.length() )
    {
        readyq.deleteAtBack();
    }
    else
    {
        readyq.deleteBeforePosition(shortest_job_pos);
    }
}