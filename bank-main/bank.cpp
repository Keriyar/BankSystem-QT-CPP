#include "bank.h"
#include "accountlist.h"
#include "bankserver.h"
#include "createaccount.h"
#include "login.h"
#include "ui_bank.h"
#include"employee.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QString>

extern bankServer bankserver;//声明全局变量
//构造函数
bank::bank(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::bank)
{
    ui->setupUi(this);
    //关闭窗口的一些按钮
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & ~Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(), this->height());//固定窗口的大小
}

bank::~bank()
{
    delete ui;
}

//打开登录，关闭当前窗口
void bank::on_loginButton_clicked()
{
    login *login_windows;
    login_windows = new login();
    login_windows->show();
    this->close();
}

void bank::on_createAccountButton_clicked()
{
    createaccount *createaccount_windows;
    createaccount_windows = new createaccount();
    createaccount_windows->show();
    this->close();
}

void bank::on_exitButton_clicked()//退出按钮
{
    switch (QMessageBox::critical(this, tr("警告"), tr("确认退出系统吗?"), tr("确认"), tr("取消"), 0, 1))
    {
    case 0:
        this->close();
        break;
    default:
        break;
    }
}

void bank::on_printAccountButton_clicked()//打印所有的账户
{
    accountlist *accountlist_windows;
    accountlist_windows = new accountlist();
    accountlist_windows->show();
    this->close();
}

void bank::on_employeeButton_clicked()
{
    Employee *employee_windows;
    employee_windows = new Employee();
    employee_windows->show();
    this->close();
}
