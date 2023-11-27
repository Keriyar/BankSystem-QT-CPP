    #include "graph.h"
#include "ui_graph.h"

#include <QDialog>
#include <QMap>
#include <QPair>
#include <QVector>
#include <algorithm>
#include <cmath>
#include"options.h"
using namespace std;

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    setDefault();
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & ~Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(), this->height());
}

Graph::~Graph()
{
    delete ui;
}


void Graph::setDefault()
{
    initgraph();
    floyd();
    ui->graph_tableWidget->setColumnCount(1);
    QStringList HStrList;
    HStrList<<"银行名字";
    ui->graph_tableWidget->setHorizontalHeaderLabels(HStrList);
    ui->graph_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=1;i<=vertexNum;i++)
    {
        int count=ui->graph_tableWidget->rowCount();
        ui->graph_tableWidget->setRowCount(count +1);
        ui->graph_tableWidget->setItem(count,0,new QTableWidgetItem(name[i]));
    }
    ui->graph_tableWidget->show();
}

void Graph::on_deleteButton_clicked()
{
    QString deleteText= ui->deletelineEdit->text();
    int dele=locatevex(deleteText);
    if(dele==INF)
    {
        QMessageBox::critical(this,tr("警告"),tr("没有找到，请重新输入"));

    }
    else
    {
        for(int i=dele;i<=vertexNum;i++)
        {
            name[i]=name[i+1];
        }
        name[vertexNum]="";
        for(int i=1;i<=vertexNum;i++)
        {
            graph[i][dele]=INF;
            graph[dele][i]=INF;
        }
        ui->graph_tableWidget->removeRow(dele-1);
        vertexNum--;
        sizeNum--;
    }
    ui->deletelineEdit->setText("");

}

void Graph::on_backButton_clicked()
{
    options *options_windows;
    options_windows = new options();
    options_windows->show();
    this->close();
}

void Graph::on_addButton_clicked()
{
    QString begin =ui->beginAddlineEdit->text();
    QString end=ui->endAddlineEdit->text();
    int weight=ui->weightAddlineEdit->text().toInt();
    int beginNum=locatevex(begin);
    if(beginNum==INF)
    {
        QMessageBox::critical(this,tr("警告"),tr("没有找到，请重新输入"));
        ui->beginAddlineEdit->setText("");
        ui->endAddlineEdit->setText("");
    }
    else
    {
        vertexNum++;
        sizeNum++;
        graph[beginNum][vertexNum]=weight;
        graph[vertexNum][beginNum]=weight;
        name[vertexNum]=end;
        int count = ui->graph_tableWidget->rowCount();
        ui->graph_tableWidget->setRowCount(count+1);
        ui->graph_tableWidget->setItem(count,0,new QTableWidgetItem(end));
        ui->beginAddlineEdit->setText("");
        ui->endAddlineEdit->setText("");
        ui->weightAddlineEdit->setText("");
    }

}

void Graph::initgraph()
{
    vertexNum=4;
    sizeNum=4;
    for(int i=1;i<=N-1;i++)
    {
        for(int j=1;j<=N-1;j++)
        {
            if(i==j)
                graph[i][j]==0;
            else
            {
                graph[i][j]=INF;
            }
        }
    }
    //srand((unsigned)time(NULL));
    graph[1][2]=1;
    graph[2][1]=1;

    graph[2][3]=1;
    graph[3][2]=1;

    graph[3][4]=1;
    graph[4][3]=1;

    graph[4][1]=1;
    graph[1][4]=1;

    name[1]="中国建设银行";
    name[2]="中国银行";
    name[3]="中国农业银行";
    name[4]="中国工商银行";
}

void Graph::floyd()
{
    for(int k=1;k<=vertexNum;k++)
        {
            for(int i=1;i<=vertexNum;i++)
            {
                for(int j=1;j<=vertexNum;j++)
                {
                    if(graph[i][j]>graph[i][k]+graph[k][j])
                    {
                        graph[i][j]=graph[i][k]+graph[k][j];
                        pass[i][j]=k;
                    }

                }
            }
    }
}

void Graph::print(int i,int j)
{
    if(i==j)
        return;
    if(pass[i][j]==0)
    {
        road=road+name[i]+"->";
    }
    else
    {
        print(i,pass[i][j]);
        print(pass[i][j],j);
    }
}

void Graph::on_searchButton_clicked()
{
    QString begin= ui->beginSearchlineEdit->text();
    QString end=ui->endSearchlineEdit->text();
    int beginNum=locatevex(begin);
    int endNum=locatevex(end);
    if(beginNum==INF || endNum==INF)
    {
        QMessageBox::critical(this,tr("警告"),tr("没有找到，请重新输入"));

    }
    else
    {
        floyd();
        int distance=graph[beginNum][endNum];
        print(beginNum,endNum);
        road+=end;
        ui->textSearchBrowser->setText(road);
        ui->textDistanceBrowser->setText(QString::number(distance));
        road="";
        distance=0;
    }
    ui->beginSearchlineEdit->setText("");
    ui->endSearchlineEdit->setText("");

}

int Graph::locatevex(QString str)
{
    int i;
    for(i=1;i<=vertexNum;i++)
    {
        if(str==name[i])
            return i;
    }
    return INF;
}
