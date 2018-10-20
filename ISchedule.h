#ifndef SCHEDULINGALGORITHMS_ISCHEDULE_H
#define SCHEDULINGALGORITHMS_ISCHEDULE_H

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

    inline void calcStats() {
        for ( PCB proc : terminatedq ) {
            double context_switching_time = proc.context_switches * CONTEXT_SWITCH_OVERHEAD;
            avg_wait_time += proc.waiting_time;
            avg_wait_time += context_switching_time;
            avg_cpu_burst_time += proc.burst_time;
            avg_turnaround_time += (proc.finish_time + 1 + context_switching_time) - proc.arrival_time;
            avg_response_time += proc.response_time;
        }

        avg_wait_time /= num_processes;
        avg_cpu_burst_time /= num_processes;
        avg_turnaround_time /= num_processes;
        avg_response_time /= num_processes;
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
};

#endif //SCHEDULINGALGORITHMS_ISCHEDULE_H
