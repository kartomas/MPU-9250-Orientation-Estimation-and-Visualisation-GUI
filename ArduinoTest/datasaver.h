#ifndef DATASAVER_H
#define DATASAVER_H

#include <QObject>
#include "mainwindow.h"

class DataSaver : public QObject
{
    Q_OBJECT
public:
    explicit DataSaver(QObject *parent = nullptr);

signals:

};

#endif // DATASAVER_H
