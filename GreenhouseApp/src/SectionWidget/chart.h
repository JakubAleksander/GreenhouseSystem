#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QMargins>
#include <QFont>
#include <QBrush>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(const QColor color, const qreal minYRange, const qreal maxYRange, const QString &units,
          QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    void addNewValue(const qreal& new_value);
    void setAxisXTitle(const QString& title);
    ~Chart();

private:
    QSplineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    qreal m_x;
    qreal m_y;
};

#endif /* CHART_H */
