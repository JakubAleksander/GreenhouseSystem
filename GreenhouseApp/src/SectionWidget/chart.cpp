#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(const QColor color, const qreal minYRange, const qreal maxYRange, const QString &units, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    series(nullptr),
    axisX(new QValueAxis()),
    axisY(new QValueAxis()),
    m_step(0),
    m_x(9),
    m_y(1)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    m_timer.setInterval(1000);

    visualConfig();

    series = new QSplineSeries(this);
    QPen green(color);
    green.setWidth(3);
    series->setPen(green);
    series->append(m_x, m_y);

    addSeries(series);

    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    axisX->setTickCount(10);
    axisX->setRange(0, 10);
    axisY->setRange(minYRange, maxYRange);
    axisY->setTickCount(5);
    axisY->setTitleText(units);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / axisX->tickCount();
    qreal y = (axisX->max() - axisX->min()) / axisX->tickCount();
    m_x += y;
    m_y = QRandomGenerator::global()->bounded(10, 50);
    series->append(m_x, m_y);
    scroll(x, 0);
    if (m_x == 100.0)
        m_timer.stop();
}

void Chart::visualConfig()
{
    setMargins(QMargins(0,0,0,0));
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);

    setBackgroundVisible(false);
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);

    QFont labelsFont;
    labelsFont.setPixelSize(10);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    //QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(Qt::white);
    axisY->setLabelsBrush(Qt::white);
}
