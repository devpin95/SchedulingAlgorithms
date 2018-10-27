#include "SJF.h"

void SJF::run() {
    int tick = 0;
    auto process_coming_in = newq.begin();

    while ( true ) {
        if ( process_coming_in != newq.end() ) {
            if ((*process_coming_in).arrival_time == tick) {
                readyq.insertAtBack((*process_coming_in));

                if ( (*process_coming_in).pid > highest_pid ) {
                    highest_pid = (*process_coming_in).pid;
                }

                ++process_coming_in;
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
            int time = tick + 1;
            if ( running_process.response_time == -1 ) {
                // this is the first time working on the process
                running_process.response_time = time - 1 - running_process.arrival_time;
            }
            // we need to do work on the currently running process
            --(running_process.remaining_burst_time);

            if ( running_process.remaining_burst_time == 0 ) {
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

int SJF::findAndRemoveShortestJob() {
    int runner = 0;
    int shortest_job_pos = 0;
    int shortest_job = std::numeric_limits<int>::max();

    for ( PCB &proc : readyq ) {
        ++runner;
        if ( proc.burst_time < shortest_job ) {
            shortest_job = proc.burst_time;
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