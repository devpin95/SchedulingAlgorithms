#include "SRJF.h"
#include <iostream>

void SRJF::run() {
    int tick = 0;
    auto process_coming_in = newq.begin();

    while ( true ) {
        if ( process_coming_in != newq.end() ) {
            if ((*process_coming_in).arrival_time == tick) {
                // insert the new process at the back of the ready queue
                readyq.insertAtBack((*process_coming_in));

                if ( (*process_coming_in).pid > highest_pid ) {
                    highest_pid = (*process_coming_in).pid;
                }

                ++process_coming_in;

                if ( tick == 0 ) {
                    running_process = *( readyq.begin() );
                    readyq.deleteAtFront();
                    working = true;
                }
                else
                {
                    int prev_pid = running_process.pid;
                    int runner = 0;
                    int shortest_job_pos = 0;
                    int shortest_job_time = std::numeric_limits<int>::max();
                    PCB shortest_job;

                    for (PCB &proc : readyq) {
                        ++runner;
                        if (proc.remaining_burst_time < shortest_job_time) {
                            shortest_job_time = proc.remaining_burst_time;
                            shortest_job_pos = runner;
                            shortest_job = proc;
                        }
                    }

                    if (shortest_job.pid != -1
                        && shortest_job.burst_time < running_process.remaining_burst_time
                        && shortest_job.pid != running_process.pid) {
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

                        ++running_process.real_context_switches;
                        readyq.insertAtBack(running_process);
                        running_process = shortest_job;
                        ++num_context_switches;
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
            findAndRemoveShortestJob();
            working = true;
        }

        for ( PCB &proc : readyq ) {
            ++(proc.waiting_time);  // update the waiting times for each process not running
        }

        if ( working ) {
            // the time after we have worked on this cycle
            double time = tick + 1 + (num_context_switches * CONTEXT_SWITCH_OVERHEAD);

            if ( running_process.response_time == -1 ) {
                // this is the first time working on the process
                running_process.response_time = time - 1 - running_process.arrival_time;
            }

            // we need to do work on the currently running process
            --(running_process.remaining_burst_time);

            // check if the process is finished
            if ( running_process.remaining_burst_time == 0 ) {
                // it is finished
                // set the time it finished and add it to the terminated queue
                running_process.finish_time = time;
                terminatedq.insertAtBack( running_process );
                working = false;
            }
        }

        ++tick;
    }


    std::cout << std::endl;
    std::cout << "Total Time: " << tick + (num_context_switches * CONTEXT_SWITCH_OVERHEAD) << std::endl;
    calcStats();
    printTable();
}

void SRJF::findAndRemoveShortestJob() {
    int runner = 0;
    int shortest_job_pos = 0;
    int shortest_job = std::numeric_limits<int>::max();

    for ( PCB &proc : readyq ) {
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