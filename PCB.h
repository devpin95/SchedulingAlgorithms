#ifndef SCHEDULINGALGORITHMS_PCB_H
#define SCHEDULINGALGORITHMS_PCB_H

struct PCB {
    int pid = -1;
    int arrival_time = -1;
    double finish_time = -1;
    double response_time = -1;
    int burst_time = -1;
    double turnaround_time = -1;
    int remaining_burst_time = -1;
    double waiting_time = 0;
    int context_switches = 0;
    int real_context_switches = 0;
};

#endif //SCHEDULINGALGORITHMS_PCB_H
