#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDialog>
#include<QDebug>
#include<QMessageBox>
#include<QTableWidget>
#include"employeedb.h"
#include<map>
#include<QTime>

namespace Ui {
class Employee;
}
typedef pair<QString,int> PII;
class Employee : public QDialog
{
    Q_OBJECT

public:
    explicit Employee(QWidget *parent = nullptr);
    ~Employee();
    void modify(QString,int);
    int strSearch(QString);
    int numSearch(int);

private slots:
    void on_Employee_backButton_clicked();
    void on_Employee_insertButton_clicked();
    void on_Employee_deleteButton_clicked();

    void appendOneRow(QString,int);
    bool deleteOneRow(QString);

    void on_Employee_searchButton_clicked();

private:
    Ui::Employee *ui;

    void SetDefault();
};

#endif // EMPLOYEE_H
