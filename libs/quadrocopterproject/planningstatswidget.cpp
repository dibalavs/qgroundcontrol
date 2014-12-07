#include "planningstatswidget.h"
#include "ui_planning_stats.h"
#include "ui_segment_stat.h"

PlanningStatsWidget::PlanningStatsWidget(SegmentManager *_sm, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlanningStats)
    , sm(_sm)
    , selected(-1)
{
    ui->setupUi(this);

    connect(_sm, SIGNAL(segmentAdded(int,double,Segment)), this, SLOT(addSegment(int, double, Segment)));
    connect(_sm, SIGNAL(segmentChanged(int,double,Segment)), this, SLOT(changeSegment(int,double,Segment)));
    connect(_sm, SIGNAL(segmentDeleted(int)), this, SLOT(removeSegment(int)));
    connect(_sm, SIGNAL(segmentSelected(int)), this, SLOT(selectSegment(int)));
}

PlanningStatsWidget::~PlanningStatsWidget()
{
    delete ui;
}

void PlanningStatsWidget::addSegment(int i, double area, const Segment &seg)
{
    segmentToArea[i] = area;
    updateData();

    SegmentStatWidget *sw = new SegmentStatWidget(i, this);
    connect(sw, SIGNAL(focusReceived(int)), sm, SLOT(selectSegment(int)));
    sw->setStat(area, seg.size());
    segmentToWidget[i] = sw;
    ui->layout->addWidget(sw);
}

void PlanningStatsWidget::changeSegment(int i, double area, const Segment &seg)
{
    if (!segmentToArea.contains(i)) {
        return;
    }

    segmentToArea[i] = area;
    segmentToWidget[i]->setStat(area, seg.size());
    updateData();
}

void PlanningStatsWidget::removeSegment(int i)
{
    if (!segmentToArea.contains(i)) {
        return;
    }

    segmentToArea.remove(i);
    delete segmentToWidget[i];
    segmentToWidget.remove(i);

    QMap<int, double> newSegmentToArea;
    QMap<int, SegmentStatWidget*> newSegmentToWidget;

    foreach (int j, segmentToArea.keys()) {
        newSegmentToArea[j < i ? j : j - 1] = segmentToArea[j];
    }

    foreach (int j, segmentToWidget.keys()) {
        int idx = j < i ? j : j - 1;
        newSegmentToWidget[idx] = segmentToWidget[j];
        segmentToWidget[j]->setIndex(idx);
    }

    segmentToArea.swap(newSegmentToArea);
    segmentToWidget.swap(newSegmentToWidget);

    updateData();

}

void PlanningStatsWidget::selectSegment(int i)
{
    if (selected != -1) {
        segmentToWidget[selected]->setStyleSheet("");
        selected = -1;
    }

    if (!segmentToArea.contains(i)) {
        return;
    }

    selected = i;
    segmentToWidget[i]->setStyleSheet("background-color:green;");
}

void PlanningStatsWidget::updateData()
{
    double area = 0;
    foreach (double value, segmentToArea) {
        area += value;
    }

    ui->totalAreaValue->setNum(area);
    ui->totalSegmentsValue->setNum(segmentToArea.size());
}
