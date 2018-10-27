#ifndef SCHEDULINGALGORITHMS_ISCHEDULE_H
#define SCHEDULINGALGORITHMS_ISCHEDULE_H

#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "PCB.h"

#define CONTEXT_SWITCH_OVERHEAD .5

class ISchedule {
protected:
    // scheduling queues
    LinkedList newq;            // the orig list of processes
    LinkedList readyq;          // the list of processes ready to run
    LinkedList terminatedq;     // the list of processes that have finished

    // scheduling stats
    double avg_wait_time = 0.0;
    double avg_cpu_burst_time = 0.0;
    double avg_turnaround_time = 0.0;
    double avg_response_time = 0.0;
    int num_context_switches = 0;

    int num_processes = 0;
    PCB running_process;
    bool working = false;
    int highest_pid = 0;

    inline void calcStats() {
        for ( PCB &proc : terminatedq ) {
            double context_switching_time = proc.context_switches * CONTEXT_SWITCH_OVERHEAD;

            avg_wait_time += (proc.finish_time - proc.arrival_time) - proc.burst_time;
            avg_cpu_burst_time += proc.burst_time;
            proc.turnaround_time = proc.finish_time - proc.arrival_time;
            avg_turnaround_time += proc.finish_time - proc.arrival_time;
            avg_response_time += proc.response_time;
        }

        avg_wait_time /= num_processes;
        avg_cpu_burst_time /= num_processes;
        avg_turnaround_time /= num_processes;
        avg_response_time /= num_processes;
    }

    inline void printTable( void ) {

        // table headers
        std::cout << std::left << std::setw(pid_width) << std::setfill(sep) << "pid";
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Arrival Time";
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Burst Time";
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Finish Time";
        std::cout << std::left << std::setw(col_width) << "Wait Time";
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Turnaround";
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Response";
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Context Switches";
        std::cout << std::endl;
        std::cout << std::left << std::setw(col_width*8) << std::setfill('-') << "-";
        std::cout << std::endl;

        for ( int i = 1; i <= highest_pid; ++i ) {
            for (PCB &pcd : terminatedq) {
                if ( pcd.pid == i ) {
                    std::cout << std::left << std::setw(pid_width) << std::setfill(sep) << pcd.pid;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << pcd.arrival_time;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << pcd.burst_time;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << pcd.finish_time;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << (pcd.finish_time - pcd.arrival_time) - pcd.burst_time;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << pcd.turnaround_time;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << pcd.response_time;
                    std::cout << std::left << std::setw(col_width) << std::setfill(sep) << pcd.real_context_switches;
                    std::cout << std::endl;
                }
            }
        }

        std::cout << std::left << std::setw(col_width*8) << std::setfill('-') << "-";
        std::cout << std::endl;
        std::cout << std::left << std::setw(25) << std::setfill(sep) << "AVERAGE";
        std::cout << std::left << std::setw(col_width*2) << std::setfill(sep) << avg_cpu_burst_time;
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << avg_wait_time;
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << avg_turnaround_time;
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << avg_response_time;
        std::cout << std::left << std::setw(col_width) << std::setfill(sep) << "Total: " + std::to_string(num_context_switches);
    }
public:
    inline ISchedule() = default;
    inline explicit ISchedule( LinkedList& l ) { newq = l; num_processes = newq.length(); };
    inline double avgWaitTime( void ) const { return avg_wait_time; };
    inline double avgCPUBurstTime( void ) const { return avg_cpu_burst_time; };
    inline double avgTurnaroundTime( void ) const { return avg_turnaround_time; };
    inline double avgResponseTime( void ) const { return avg_response_time; };
    inline int numContextSwitches( void ) const { return num_context_switches; };

private:
    // print table values
    const char sep = ' ';
    const int pid_width = 10;
    const int col_width = 15;
};

#endif //SCHEDULINGALGORITHMS_ISCHEDULE_H
