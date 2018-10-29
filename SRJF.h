#ifndef SCHEDULINGALGORITHMS_SRJF_H
#define SCHEDULINGALGORITHMS_SRJF_H

#include <limits>
#include "ISchedule.h"

class SRJF : public ISchedule {
public:
    inline SRJF() = default;
    inline explicit SRJF( LinkedList& l ) : ISchedule(l) { };
    void run( void );
    void setQuantum( const int &i ) {};
private:
    void findAndRemoveShortestJob(void);
};


#endif //SCHEDULINGALGORITHMS_SRJF_H
