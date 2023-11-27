#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include"employee.h"
#include<QTime>

namespace Ui
{
    class options;
}

class options : public QDialog
{
    Q_OBJECT

public:
    explicit options(QWidget *parent = nullptr);
    ~options();
    int deposite_choose=3;
    int withdraw_choose=3;
    Employee em;
    QTime time;


private slots:
    void on_options_logoutButton_clicked();//注销按钮

    void on_options_depositButton_clicked();//存款

    void on_options_changeButton_clicked();//修改信息

    void on_options_passwdButton_clicked();//修改密码

    void on_options_lostButton_clicked();//挂失

    void on_options_withdrawButton_clicked();//取款

    void on_options_flowButton_clicked();//查看流水
    void on_options_roadButton_clicked();//查看路线

private:
    Ui::options *ui;
};

#endif // OPTIONS_H
