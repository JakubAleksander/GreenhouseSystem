#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(const QColor color, const qreal minYRange, const qreal maxYRange, const QString &units, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    series(new QSplineSeries()),
    axisX(new QValueAxis()),
    axisY(new QValueAxis()),
    m_x(24),
    m_y(0)
{
    //Visual configuration
    setMargins(QMargins(0,0,0,0));
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);
    setTitleBrush(Qt::white);
    setBackgroundVisible(false);
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(true);
    axisY->setGridLinePen(QColor(55, 45, 20));
    QFont labelsFont;
    labelsFont.setPixelSize(10);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);
    axisX->setLabelsBrush(QColor(35,35,60));
    axisY->setLabelsBrush(Qt::white);
    QPen series_color(color);
    series_color.setWidth(3);
    series->setPen(series_color);

    //Add start point on the chart
    series->append(m_x, m_y);
    addSeries(series);

    addAxis(axisX, Qt::AlignBottom);
    addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    axisX->setTickCount(24);
    axisX->setRange(0, 24);

    axisY->setRange(minYRange, maxYRange);
    axisY->setTickCount(5);
    axisY->setTitleText(units);
}

void Chart::setAxisXTitle(const QString &title)
{
    axisX->setTitleText(title);
}

Chart::~Chart()
{

}

void Chart::addNewValue(const qreal& new_value)
{
    qreal offset = plotArea().width() / axisX->tickCount();
    m_x += 1;
    series->append(m_x, new_value);
    scroll(offset, 0);
}
