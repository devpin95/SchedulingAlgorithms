#include "RR.h"
#include <iostream>

void RR::run() {
    int quantum_counter = 0;
    int tick = 0;
    auto process_coming_in = newq.begin();

    while ( true ) {
        std::cout << std::endl << tick << " "
        << "Q = " <<  quantum_counter << " " << running_process.pid << "["
        << running_process.remaining_burst_time << "] ----------------------------" << std::endl;

        if ( process_coming_in != newq.end() ) {
            if ((*process_coming_in).arrival_time == tick) {

                std::cout << std::endl << "Adding process " << (*process_coming_in).pid << "["
                          << (*process_coming_in).remaining_burst_time << "]" << std::endl
                          << "Ready Q: ";
                readyq.printVals();
                std::cout << std::endl;

                readyq.insertAtBack((*process_coming_in));
                ++process_coming_in;
            }
        }

        if ( !working && readyq.empty() ) {
            // we are not working and there are no more processes in the ready queue
            break;
        }

        if ( !working ) {
            // the ready queue is not empty so we know the iterator will not be nullptr

            std::cout << "Finished " << running_process.pid << "[ "
            << running_process.remaining_burst_time << "]" << std::endl;

            auto temp_itr = readyq.begin();
            running_process = (*temp_itr);
            (void)readyq.deleteAtFront();

            std::cout << "Now working on " << running_process.pid << "[ "
                      << running_process.remaining_burst_time << "]" << std::endl;

            working = true;
            quantum_counter = 0;
        }
        else if ( quantum_counter > quantum ) {
            std::cout << "Quantum reached by " << running_process.pid << "[ "
                      << running_process.remaining_burst_time << "]" << std::endl;

            readyq.insertAtBack( running_process );
            running_process = *( readyq.begin() );
            readyq.deleteAtFront();

            std::cout << "Context switching to " << running_process.pid << "[ "
                      << running_process.remaining_burst_time << "]" << std::endl;

            ++num_context_switches;
            quantum_counter = 0;
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

            if ( running_process.remaining_burst_time == 0 ) {
                running_process.finish_time = tick;
                terminatedq.insertAtBack( running_process );
                working = false;
            }
        }

        ++tick;
        ++quantum_counter;
    }

    calcStats();
}