#include "graph2d.h"

#include <QtCharts>
//Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
//    QChart(QChart::ChartTypeCartesian, parent, wFlags),
Graph2D::Graph2D():
 QChart(),
    x_series(0),
    y_series(0),
    z_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    xVal(0),
    yMin(0),
    yMax(0)

{

    // Create Series Objects and set names
    x_series = new QLineSeries(this);
    y_series = new QLineSeries(this);
    z_series = new QLineSeries(this);
    x_series->setName("X");
    y_series->setName("Y");
    z_series->setName("Z");
    //![1]

    //![2]
//    x_series->append(0, 6);
//    x_series->append(2, 4);
//    x_series->append(3, 8);
//    x_series->append(7, 4);
//    x_series->append(10, 5);
//    *x_series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    // Add series to the chart
    addSeries(x_series);
    addSeries(y_series);
    addSeries(z_series);
    // Add axes to the chart
    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    // Attach series to the axes
    x_series->attachAxis(m_axisX);
    x_series->attachAxis(m_axisY);
    y_series->attachAxis(m_axisX);
    y_series->attachAxis(m_axisY);
    z_series->attachAxis(m_axisX);
    z_series->attachAxis(m_axisY);
    // Set tick count and range
    m_axisX->setTickCount(20);
    m_axisX->setRange(0, 20);
    m_axisX->setTickInterval(10);
    m_axisX->applyNiceNumbers();
    m_axisX->hide();

    x_series->setUseOpenGL(true);
    y_series->setUseOpenGL(true);
    z_series->setUseOpenGL(true);
//    m_axisY->setRange(-300, 300);

}

void Graph2D::updateGraph(qreal xData, qreal yData, qreal zData){
//    qDebug()<<xData;
//    qDebug()<<yData;
//    qDebug()<<zData;
    xVal++;
//    qDebug()<<xVal;

    qreal xScroll = plotArea().width() / m_axisX->tickCount();
//    qDebug()<<plotArea().width();
//    qDebug()<<m_axisX->tickCount();
//    qDebug() << xScroll;
//    qDebug()<< (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    x_series->append(xVal, xData);
    y_series->append(xVal, yData);
    z_series->append(xVal, zData);
    // Adjust y axis range based on series data
    if(xData< yMin || xData > yMax || yData < yMin || yData > yMax || zData < yMin || zData > yMax){
        if(xData < yMin)
            yMin = xData;
        else if(xData> yMax)
            yMax = xData;
        else if (yData < yMin)
            yMin = yData;
        else if (yData > yMax)
            yMax = yData;
        else if (zData < yMin)
            yMin = zData;
        else if (zData > yMax)
            yMax = zData;

        m_axisY->setRange(yMin-20, yMax+20);
    }
    if(xVal>7){
        scroll(xScroll, 0);
//        if(xVal>20){
//            x_series->remove(0);
//            y_series->remove(0);
//            z_series->remove(0);
//        }

    }
}
