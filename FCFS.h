#ifndef SCHEDULINGALGORITHMS_FCFS_H
#define SCHEDULINGALGORITHMS_FCFS_H

#include "ISchedule.h"

class FCFS : public ISchedule {
public:
    inline FCFS() = default;
    inline explicit FCFS( LinkedList& l ) : ISchedule(l) { };
    void run( void );
};


#endif //SCHEDULINGALGORITHMS_FCFS_H
