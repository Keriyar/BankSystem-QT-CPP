#ifndef ECONOMICCALC_H
#define ECONOMICCALC_H

#include "bankdb.h"
#include <time.h>
#include <vector>

class economiccalc
{
public:
    economiccalc();
    void SetType(int);
    void Add(double, time_t);
    void Sub(double, time_t);
    double Query(time_t);
    double QueryPrepare(time_t);

private:
    int iType; /// type
    /*
    the struct of Flow is like a chain.
     *       when we deposit, the chain adds,
     *       when we withdraw, the chain minus.
     */
    struct Flow
    {
        double dMoney; /// money change
                       /// -# +:deposit
                       /// -# -:withdraw
        time_t tTime;  /// time of operation
    };
    double dMoney; /// money till some point of time
    vector<Flow> vFlow;
};

#endif // ECONOMICCALC_H
