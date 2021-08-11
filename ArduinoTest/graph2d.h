#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QChart>
#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Graph2D : public QChart
{
public:
    Graph2D();
public slots:
    void updateGraph(qreal xData, qreal yData, qreal zData);
private:
//    QTimer m_timer;
    QLineSeries *x_series;
    QLineSeries *y_series;
    QLineSeries *z_series;

//    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal xVal;
    qreal yMin;
    qreal yMax;

};


#endif // GRAPH2D_H
