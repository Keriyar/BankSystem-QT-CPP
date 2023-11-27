#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QMap>
#include <QPair>
#include <QVector>
#include <algorithm>
#include <cmath>
#include<climits>
using namespace std;
namespace Ui {
class Graph;
}

const int N=500,INF=9999;

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
    QString road;
    void setDefault();
    int locatevex(QString);
    void initgraph();
    void floyd();
    void print(int,int);
    int graph[N][N];
    QString name[N];
    int vertexNum,sizeNum;
    int pass[N][N];

private slots:
    void on_searchButton_clicked();

    void on_backButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
