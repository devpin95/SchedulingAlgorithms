#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "PCB.h"

// file format
// pid      arrival time      CPU burst time

void testLL( LinkedList& ll ) {
    for ( auto i = ll.begin(); i != ll.end(); ++i ) {
        std::cout << (*i).pid << "\t";
    }
}

int main() {
    LinkedList ll;
    int num_processes = 0;
    std::string filename = "/home/devpin/CLionProjects/SchedulingAlgorithms/input10";
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
                ss << temp;

                ss >> pcb.pid;
                ss >> pcb.arrival_time;
                ss >> pcb.burst_time;
                ss.str("");

                ll.insertAtBack(pcb);

                ++num_processes;
            }
        }

        testLL(ll);

        infile.close();
    }

    return 0;
}