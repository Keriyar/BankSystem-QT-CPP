#include "employeedb.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <fstream>
#include <map>
#include<vector>

using namespace std;

vector<pair<QString,int> > employeedb::vEmployee = employeedb::InitvEmployee();

vector<pair<QString,int> > employeedb::InitvEmployee()
{
    vector<pair<QString,int> > qm;
    qm.push_back({"77",0});
    return qm;
}

vector<double> employeedb::personNum = employeedb::InitpersonNum();
vector<double> employeedb::InitpersonNum()
{
    vector<double> v;
    v.push_back(0.0);
    return v;

}


/*
void employeedb::AddEmployee(QString num)
{
    vEmployee[num]=0;
}
bool employeedb::DeleteEmployee(QString num)
{
    bool flag=false;
    auto t = vEmployee.find(num);
    if(t != vEmployee.end())
    {
        vEmployee.erase(num);
        flag=true;
    }
    return flag;
}
*/

