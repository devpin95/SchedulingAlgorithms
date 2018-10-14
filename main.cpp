#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "PCB.h"
#include "FCFS.h"
#include "SJF.h"
#include "SRJF.h"
#include "RR.h"

int main() {
    LinkedList ll;
    int num_processes = 0;
    std::string filename = "/home/devpin/CLionProjects/SchedulingAlgorithms/input100";
    std::ifstream infile;
    infile.open(filename);

    if ( !infile ) {
        std::cout << "Could not open file " << filename << std::endl;
    }
    else {
        std::string temp;
        std::stringstream ss;

        while ( !infile.eof() ) {
            getline(infile, temp);

            PCB pcb;
            if ( !temp.empty() ) {
                // file format
                // pid      arrival time      CPU burst time
                ss << temp;

                ss >> pcb.pid;
                ss >> pcb.arrival_time;
                ss >> pcb.burst_time;
                ss.str("");

                pcb.remaining_burst_time = pcb.burst_time;

                ll.insertAtBack(pcb);

                ++num_processes;
            }
        }
        infile.close();

        RR scheduler(ll);
        scheduler.setQuantum( 20 );
        scheduler.run();

        //ll.printVals();
        std::cout << std::endl << "Stats" << std::endl;
        std::cout << "Avg Wait Time: " << scheduler.avgWaitTime() << std::endl;
        std::cout << "Avg CPU Burst Time: " << scheduler.avgCPUBurstTime() << std::endl;
        std::cout << "Avg Turnaround Time: " << scheduler.avgTurnaroundTime() << std::endl;
        std::cout << "Avg Response Time: " << scheduler.avgResponseTime() << std::endl;
        std::cout << "Context Switches: " << scheduler.numContextSwitches() << std::endl;
    }

    return 0;
}