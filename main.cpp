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

int main( int argc, char * argv[] ) {
    LinkedList ll;
    long algorithm = std::stol( argv[2] );

    if ( argc <= 1 ) {
        std::cout << "Error. Expecting a string and integer";
        return 1;
    }

    std::cout << argv[1] << " using ";

    std::string filename = argv[1];
    std::ifstream infile;
    infile.open(filename);

    if ( !infile ) {
        std::cout << "Error. Could not open file " << filename << std::endl;
        return 1;
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
            }
        }

        infile.close();

        ISchedule * scheduler;

        switch ( algorithm ) {
            case 1:
                std::cout << "First Come First Serve" << std::endl;
                scheduler = new FCFS(ll);
                scheduler->run();
                //FCFS FCFSscheduler(ll);
                break;
            case 2:
                std::cout << "Shortest Job First" << std::endl;
                scheduler = new SJF(ll);
                scheduler->run();
                //SJF SJFscheduler(ll);
                break;
            case 3:
                std::cout << "Shortest Remaining Job First" << std::endl;
                scheduler = new SRJF(ll);
                scheduler->run();
                //SRJF SRJFscheduler(ll);
                break;
            case 4:
                std::cout << "Round Robin Q=" << argv[3] << std::endl;
                scheduler = new RR(ll);
                scheduler->setQuantum( atoi( argv[3] ) );
                scheduler->run();
                //RR RRscheduler(ll);
                //RRscheduler.setQuantum( std::stoi( argv[3] ) );
                break;
            default: break;
        }

//        std::cout << "Avg Wait Time: " << scheduler.avgWaitTime() << std::endl;
//        std::cout << "Avg CPU Burst Time: " << scheduler.avgCPUBurstTime() << std::endl;
//        std::cout << "Avg Turnaround Time: " << scheduler.avgTurnaroundTime() << std::endl;
//        std::cout << "Avg Response Time: " << scheduler.avgResponseTime() << std::endl;
//        std::cout << "Context Switches: " << scheduler.numContextSwitches() << std::endl;
    }

    return 0;
}