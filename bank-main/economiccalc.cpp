#include "economiccalc.h"
#include <QDebug>

economiccalc::economiccalc()
{
    dMoney = 0;
    vFlow.clear();
}


void economiccalc::SetType(int iSetType)
{
    iType = iSetType;
}


void economiccalc::Add(double dMoney, time_t tTime)
{
    Flow tmpFlow;
    tmpFlow.tTime = tTime;
    tmpFlow.dMoney = dMoney;
    vFlow.push_back(tmpFlow);
}


void economiccalc::Sub(double dMoney, time_t tTime)
{
    double dMoneyNeeded = dMoney;
    int iTmpPos = vFlow.size() - 1; /// pointer to the flow
    while (dMoneyNeeded > 0 && iTmpPos >= 0)
    {
        if (tTime < vFlow[iTmpPos].tTime) /// time no match
        /**
         * @note actually this will not happen.
         *       i write this just to debug.
         */
            iTmpPos--;
        else if (vFlow[iTmpPos].dMoney > dMoneyNeeded) /// enough money
        {
            vFlow[iTmpPos].dMoney -= dMoneyNeeded;
            dMoneyNeeded = 0;
            iTmpPos--;
        }
        else /// money not enough
        {
            dMoneyNeeded -= vFlow[iTmpPos].dMoney;
            vFlow[iTmpPos].dMoney = 0;
            iTmpPos--;
        }
    }
}

double economiccalc::Query(time_t tTime)
{
    double dAns = 0; /// ans for the query
    int iTmpTime; /// relate to type
    double dInterest; /// store the interest
    switch (iType)
    {
    case 0: /// 1 year
        iTmpTime = 31536000;
        dInterest = 1.98;
        break;
    case 1: /// 3 year
        iTmpTime = 94608000;
        dInterest = 2.25;
        break;
    case 2: /// 5 year
        iTmpTime = 157680000;
        dInterest = 3.5;
        break;
    }

    for (int i = 0; i < (int)vFlow.size(); i++)
    {
        /**
         * @note it can calculate yield compound interest
         */
        int iYieldInterestYear = ((int)difftime(tTime, vFlow[i].tTime)) / iTmpTime;
        double dYieldInterest = vFlow[i].dMoney;
        for (int j = 1; j <= iYieldInterestYear; j++)
            dYieldInterest = dYieldInterest * (1 + (dInterest / 100));
        dAns += dYieldInterest;
    }
    return dAns;
}


double economiccalc::QueryPrepare(time_t tTime2)
{
    time_t tTime1 = time(nullptr);
    double dAns = 0; /// ans for the query
    int iTmpTime; /// relate to type
    double dInterest; /// store the interest
    switch (iType)
    {
    case 0: /// 1 year
        iTmpTime = 31536000;
        dInterest = 1.98;
        break;
    case 1: /// 3 year
        iTmpTime = 94608000;
        dInterest = 2.25;
        break;
    case 2: /// 5 year
        iTmpTime = 157680000;
        dInterest = 3.5;
        break;
    }

    for (int i = 0; i < (int)vFlow.size(); i++)
    {
        int iDifftime1 = (int)difftime(tTime1, vFlow[i].tTime);
        int iDifftime2 = (int)difftime(tTime2, vFlow[i].tTime);
        if (((iDifftime1 / iTmpTime) + 1) * iTmpTime <= iDifftime2)
        {
            int iYieldInterestYear = iDifftime2 / iTmpTime;
            double dYieldInterest = vFlow[i].dMoney;
            for (int j = 1; j <= iYieldInterestYear; j++)
                dYieldInterest = dYieldInterest * (1 + (dInterest / 100));
            dAns += dYieldInterest;
        }
    }
    return dAns;
}
