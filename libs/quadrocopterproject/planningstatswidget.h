#ifndef PLANNINGSTATSWIDGET_H
#define PLANNINGSTATSWIDGET_H

#include "segment_manager.h"
#include "segment_stat_widget.h"

#include <QMap>
#include <QWidget>

namespace Ui {
    class PlanningStats;
}

class PlanningStatsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlanningStatsWidget(SegmentManager *_sm, QWidget *parent = 0);
    ~PlanningStatsWidget();

public slots:
    void addSegment(int i, double area, const Segment &seg);
    void changeSegment(int i, double area, const Segment &seg);
    void removeSegment(int i);
    void selectSegment(int i);

private:
    void updateData();

private:
    Ui::PlanningStats *ui;
    SegmentManager *sm;
    QMap<int, double> segmentToArea;
    QMap<int, SegmentStatWidget*> segmentToWidget;
    int selected;
};

#endif // PLANNINGSTATSWIDGET_H
