#ifndef SCHEDULINGALGORITHMS_RR_H
#define SCHEDULINGALGORITHMS_RR_H


#include "ISchedule.h"

class RR : public ISchedule {
public:
    inline RR() = default;
    inline explicit RR( LinkedList& l ) : ISchedule(l) { };
    void run( void );
    inline void setQuantum( const int& q ) { quantum = q; };
private:
    int quantum = 1;
};


#endif //SCHEDULINGALGORITHMS_RR_H
