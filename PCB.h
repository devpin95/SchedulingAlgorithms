#ifndef SCHEDULINGALGORITHMS_PCB_H
#define SCHEDULINGALGORITHMS_PCB_H

struct PCB {
    int pid = -1;
    int arrival_time = -1;
    int finish_time = -1;
    int response_time = -1;
    int burst_time = -1;
    int remaining_burst_time = -1;
    int waiting_time = 0;
};

#endif //SCHEDULINGALGORITHMS_PCB_H
