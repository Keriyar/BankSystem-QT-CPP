#ifndef TEXTFILEMODEL_H
#define TEXTFILEMODEL_H
#include<QStandardItemModel>
#include<QFile>
#include<QTextStream>

class TextFileModel:public QStandardItemModel
{
    Q_OBJECT
public:
    explicit TextFileModel(QObject *parent = nullptr);
    void loadData();
    void saveData();

private:
    QString m_fileName;
};

#endif // TEXTFILEMODEL_H
