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
//            std::cout << std::endl << "Quantum reached by " << running_process.pid << "["
//                      << running_process.remaining_burst_time << "]" << std::endl;

            readyq.insertAtBack( running_process );
            running_process = *( readyq.begin() );

//            std::cout << "Ready Q: ";
//            readyq.printVals();
//            std::cout << std::endl;

            readyq.deleteAtFront();

            if ( tick != 0 && prev_pid != running_process.pid ) {
//                std::cout << "Context switching (" << num_context_switches + 1 << ") to " << running_process.pid << "["
//                          << running_process.remaining_burst_time << "]" << std::endl;
                ++num_context_switches;
                quantum_counter = 0;

                //++running_process.context_switches;
                std::cout << "__ ";

                did_context_switch = true;
                ++running_process.context_switches;
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
            if ( running_process.response_time == -1 ) {
                // this is the first time working on the process
                running_process.response_time = tick - running_process.arrival_time + ( running_process.context_switches * CONTEXT_SWITCH_OVERHEAD );
            }
            // we need to do work on the currently running process
            --(running_process.remaining_burst_time);

            std::cout << running_process.pid << " ";

//            std::cout << std::endl << "Q = " << quantum_counter + 1 << " " << running_process.pid << "["
//                      << running_process.remaining_burst_time << "]" << std::endl;

            if ( running_process.remaining_burst_time == 0 ) {
                running_process.finish_time = tick;
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

    calcStats();
//    std::cout << std::endl << std::endl;
//    for ( int i = 1; i <= 10; ++i ) {
//        for (PCB &proc : terminatedq) {
//            if ( proc.pid == i ) {
//                //std::cout << proc.pid;
//                //std::cout << "[" << proc.burst_time << "]";
//                std::cout << "[" << proc.waiting_time << "]";
//                //std::cout << "[" << proc.arrival_time << "]";
//                //std::cout << "[" << proc.finish_time + 1 << "]";
//                std::cout << "[" << proc.context_switches << "]";
//                std::cout << std::endl;
//                continue;
//            }
//        }
//    }
    std::cout << std::endl << std::endl;
}