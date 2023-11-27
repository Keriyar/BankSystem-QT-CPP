#ifndef EMPLOYEEDB_H
#define EMPLOYEEDB_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <fstream>
#include <map>
#include <time.h>
#include<vector>
#include<QTime>

using namespace std;

class employeedb
{
public:
    explicit employeedb(QWidget *parent = nullptr);
    /*
    //文件操作
    void GetFile();
    void WriteFile();

    //employee操作
    void AddEmployee(QString);
    bool DeleteEmployee(QString);

    bool CheckEmployee();
    */
    //employee信息  
    static vector<pair<QString,int> > vEmployee;
    static vector<double> personNum;
    static vector<pair<QString,int> > InitvEmployee();
    static vector<double> InitpersonNum();

};

#endif // EMPLOYEEDB_H
