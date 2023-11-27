#include "options.h"
#include "bank.h"
#include "bankserver.h"
#include "deposit.h"
#include "editpasswd.h"
#include "editprofile.h"
#include "flowlist.h"
#include "ui_options.h"
#include "withdraw.h"
#include <QDebug>
#include <QMessageBox>
#include <ctime>
#include<QInputDialog>
#include<QLineEdit>
#include"employee.h"
#include"employeedb.h"
#include"graph.h"
#include<QTime>
extern bankServer bankserver;

options::options(QWidget *parent) : QDialog(parent),
                                    ui(new Ui::options)
{
    ui->setupUi(this);
    time.start();
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & ~Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(), this->height());
}

options::~options()
{
    delete ui;
}

void options::on_options_logoutButton_clicked()
{
    int s=QMessageBox::critical(this, tr("警告"), tr("确认注销吗?"), tr("确认"), tr("取消"), 0, 1);
    if(s==0)
    {

        QString emplo=QInputDialog::getText(this,tr("评分"),tr("请选择职员"),QLineEdit::Normal);
        int score=QInputDialog::getInt(this,tr("评分"),tr("请对职员进行打分"),QLineEdit::Normal);
        int n = em.strSearch(emplo);
        employeedb::vEmployee[n].second+=score;
        employeedb::personNum[n]++;
        QMessageBox::information(this,tr("提示"),tr("您的使用时间为")+QString::number(time.elapsed()/1000.0)+tr("秒"));
        bank *bank_windows;
        bank_windows = new bank();
        bank_windows->show();
        this->close();
    }
}

void options::on_options_depositButton_clicked()
{
    if(bankserver.GetIdentity()=="Normal")
    {
        while(deposite_choose)
        {
            QMessageBox::information(this,tr("提示"),tr("您不是VIP用户，需要排队,前面还有")+QString::number(deposite_choose)+tr("个人！"));
            deposite_choose--;
        }
    }

    deposit *deposit_windows;
    deposit_windows = new deposit();
    deposit_windows->show();
    this->close();
}

void options::on_options_changeButton_clicked()
{
    editprofile *editprofile_windows;
    editprofile_windows = new editprofile();
    editprofile_windows->show();
    this->close();
    delete this;
}

void options::on_options_passwdButton_clicked()
{
    editpasswd *editpasswd_windows;
    editpasswd_windows = new editpasswd();
    editpasswd_windows->show();
    this->close();
    delete this;
}

void options::on_options_lostButton_clicked()
{
    int result = QMessageBox::warning(this, tr(""), tr("确认挂失吗？"), tr("确认"), tr("取消"), 0, 1);
    switch (result)
    {
    case 0:
        QTime currenttime;
        currenttime.start();
        time_t tCurrentTime = currenttime.elapsed();
        bankserver.ReportLost(tCurrentTime);
        QMessageBox::information(this, tr(""), tr("账户已挂失！"), tr("确认"), 0);
        bank *bank_windows;
        bank_windows = new bank();
        bank_windows->show();
        this->close();
        break;
    }
}

void options::on_options_withdrawButton_clicked()
{
    if(bankserver.GetIdentity()=="Normal")
    {
        while(withdraw_choose)
        {
            QMessageBox::information(this,tr("提示"),tr("您不是VIP用户，需要排队,前面还有")+QString::number(withdraw_choose)+tr("个人！"));
            withdraw_choose--;
        }
    }
    withdraw *withdraw_windows;
    withdraw_windows = new withdraw();
    withdraw_windows->show();
    this->close();
}

void options::on_options_flowButton_clicked()
{
    flowlist *flowlist_windows;
    flowlist_windows = new flowlist();
    flowlist_windows->show();
    this->close();
}

void options :: on_options_roadButton_clicked()
{
    Graph* graph_windows;
    graph_windows=new Graph();
    graph_windows->show();
    this->close();

}


