#ifndef SCHEDULINGALGORITHMS_SJF_H
#define SCHEDULINGALGORITHMS_SJF_H

#include <limits>
#include "ISchedule.h"

class SJF : public ISchedule {
public:
    inline SJF() = default;
    inline explicit SJF( LinkedList& l ) : ISchedule(l) { };
    void run( void );
private:
    int findAndRemoveShortestJob( void );
};


#endif //SCHEDULINGALGORITHMS_SJF_H
