#include "segment_stat_widget.h"
#include "ui_segment_stat.h"

SegmentStatWidget::SegmentStatWidget(int i, QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::SegmentStat())
  , index(i)
{
    ui->setupUi(this);
    setTitle();
}

SegmentStatWidget::~SegmentStatWidget()
{
    delete ui;
}

void SegmentStatWidget::setTitle()
{
    ui->segmentNo->setTitle(QString("Segment %1").arg(index + 1));
}

void SegmentStatWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit SegmentStatWidget::focusReceived(index);
}

void SegmentStatWidget::setIndex(int i)
{
    index = i;
    setTitle();
}

void SegmentStatWidget::setStat(double area, int points)
{
    ui->areaValue->setNum(area);
    ui->pointsValue->setNum(points);
}
