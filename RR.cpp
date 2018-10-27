#include "RR.h"
#include <iostream>

void RR::run() {
    int quantum_counter = 0;
    int tick = 0;
    auto process_coming_in = newq.begin();
    bool did_context_switch = false;

    while ( true ) {

//        std::cout << std::endl << tick << "-----------------------------------------------";
//        readyq.printVals();
//        std::cout << std::endl;

        if ( process_coming_in != newq.end() ) {
            if ((*process_coming_in).arrival_time == tick) {

//                std::cout << std::endl << "Adding process " << (*process_coming_in).pid << "["
//                          << (*process_coming_in).remaining_burst_time << "]" << std::endl;

                readyq.insertAtBack((*process_coming_in));

                if ( (*process_coming_in).pid > highest_pid ) {
                    highest_pid = (*process_coming_in).pid;
                }

//                std::cout << "Updated Ready Queue: ";
//                readyq.printVals();
//                std::cout << std::endl;

                ++process_coming_in;
            }
        }

        if ( !working && readyq.empty() ) {
            // we are not working and there are no more processes in the ready queue
            break;
        }

        if ( !working ) {
            // the ready queue is not empty so we know the iterator will not be nullptr

            auto temp_itr = readyq.begin();
            running_process = (*temp_itr);
            (void)readyq.deleteAtFront();

//            std::cout << std::endl << "Now working on " << running_process.pid << "["
//                      << running_process.remaining_burst_time << "]" << std::endl;

            working = true;
            quantum_counter = 0;
        }
        else if ( quantum_counter >= quantum ) {
            int prev_pid = running_process.pid;

            ++running_process.real_context_switches;
            readyq.insertAtBack( running_process );
            running_process = *( readyq.begin() );

            readyq.deleteAtFront();

            if ( tick != 0 && prev_pid != running_process.pid ) {
                ++num_context_switches;
                quantum_counter = 0;

                //++running_process.context_switches;
//                std::cout << "__ ";

                did_context_switch = true;
                ++running_process.context_switches;
                //++running_process.real_context_switches;
            } else {
                --running_process.real_context_switches;
            }
        }

        for ( PCB &proc : readyq ) {
            ++(proc.waiting_time);  // update the waiting times for each process not running
            if ( did_context_switch ) {
                ++(proc.context_switches);
            }
        }

        did_context_switch = false;

        if ( working ) {
            // the time after we have worked on this cycle
            double time = tick + 1 + (num_context_switches * CONTEXT_SWITCH_OVERHEAD);
            // see if this is the first time working on the process
            if ( running_process.response_time == -1 ) {
                // this is the first time working on it so set it's response time
                //subtract 1 because we haven't worked on this cycle yet
                running_process.response_time = time - 1 - running_process.arrival_time;
            }
            // we need to do work on the currently running process
            --(running_process.remaining_burst_time);

//            std::cout << running_process.pid << " ";

//            std::cout << std::endl << "Q = " << quantum_counter + 1 << " " << running_process.pid << "["
//                      << running_process.remaining_burst_time << "]" << std::endl;

            if ( running_process.remaining_burst_time == 0 ) {
                running_process.finish_time = time;
                terminatedq.insertAtBack( running_process );
                working = false;

                if ( tick != 0 ) {
//                    std::cout << "Finished " << running_process.pid << "["
//                              << running_process.remaining_burst_time << "]" << std::endl;
                }
            }
        }

        ++tick;
        ++quantum_counter;
    }

    std::cout << std::endl;
    std::cout << "Total Time: " << tick + (num_context_switches * CONTEXT_SWITCH_OVERHEAD) << std::endl;
    calcStats();
    printTable();
    std::cout << std::endl;
}