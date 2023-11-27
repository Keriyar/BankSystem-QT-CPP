#include "employee.h"
#include "ui_employee.h"
#include"bank.h"
#include<vector>
#include<QtAlgorithms>
#include<QMessageBox>

Employee::Employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
    SetDefault();
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & ~Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(),this->height());
}

Employee::~Employee()
{
    delete ui;
}

void Employee::on_Employee_backButton_clicked()
{
    bank *bank_windows;
    bank_windows = new bank();
    bank_windows->show();
    this->close();

}

void Employee::on_Employee_insertButton_clicked()
{
    QString e_num= ui->insert_line->text();
    appendOneRow(e_num,0);
    ui->insert_line->setText("");


}

void Employee::on_Employee_deleteButton_clicked()
{
    QString e_num= ui->delete_line->text();
    if(!deleteOneRow(e_num))
    {
        QMessageBox::critical(this,tr("警告"),tr("没有找到，请重新输入"));
    }
    ui->delete_line->setText("");

}

void Employee::on_Employee_searchButton_clicked()
{
    QString s_num = ui->search_line->text();
    int i =strSearch(s_num);
    if(i==employeedb::vEmployee.size())
    {
        QMessageBox::critical(this,tr("警告"),tr("没有找到，请重新输入"));
        ui->search_line->setText("");
    }
    else
    {
        QString sco = QString::number(employeedb::vEmployee[i].second);
        QMessageBox::information(this,tr("提示"),s_num+tr("号职员的评分为")+sco,0);
        ui->search_line->setText("");
    }


}

void Employee::modify(QString num, int score)
{

    int n =strSearch(num);
    employeedb::vEmployee[n].second=score;
}

int Employee::strSearch(QString str)
{
    int i;
    for(i=0;i<employeedb::vEmployee.size();i++)
    {
        if(str == employeedb::vEmployee[i].first)
        {
            return i;
        }
    }
    return i;
}

int Employee::numSearch(int num)
{
    for(int i=0;i<employeedb::vEmployee.size();i++)
    {
        if(num == employeedb::vEmployee[i].second)
        {
            return i;
        }
    }
}

void Employee::appendOneRow(QString num,int n)
{
    employeedb::vEmployee.push_back({num,n});
    int count = ui->Employee_tableWidget->rowCount();
    ui->Employee_tableWidget->setRowCount(count+1);
    //int n=strSearch(num);
    ui->Employee_tableWidget->setItem(count,0,new QTableWidgetItem(num));
    ui->Employee_tableWidget->setItem(count,1,new QTableWidgetItem(QString::number(n)));
}

bool Employee::deleteOneRow(QString num)
{
    bool flag=false;
    auto t = employeedb::vEmployee.begin();
    for(int i=0;i<employeedb::vEmployee.size();i++,t++)
    {
        if(num == t->first)
        {
            employeedb::vEmployee.erase(t);
            flag=true;
            ui->Employee_tableWidget->removeRow(i);
            break;
        }
    }

    return flag;

}


void Employee::SetDefault()
{
    //ui->Employee_tableWidget->setRowCount(edb.vEmployee.size());
    ui->Employee_tableWidget->setColumnCount(2);
    QStringList HStrLIst;
    HStrLIst<<"职员工号"<<"客户评分";
    ui->Employee_tableWidget->setHorizontalHeaderLabels(HStrLIst);

    ui->Employee_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<employeedb::vEmployee.size();i++)
    {
        int count = ui->Employee_tableWidget->rowCount();
         ui->Employee_tableWidget->setRowCount(count+1);
        ui->Employee_tableWidget->setItem(count,0,new QTableWidgetItem(employeedb::vEmployee[i].first));
        if(employeedb::personNum[i]==0.0)
        {
            ui->Employee_tableWidget->setItem(count,1,new QTableWidgetItem(QString::number(employeedb::vEmployee[i].second )));
        }
        else
        {
            ui->Employee_tableWidget->setItem(count,1,new QTableWidgetItem(QString::number(employeedb::vEmployee[i].second /employeedb::personNum[i])));
        }

    }

    ui->Employee_tableWidget->show();

}

