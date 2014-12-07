#ifndef SEGMENT_STAT_WIDGET_H
#define SEGMENT_STAT_WIDGET_H

#include <QWidget>

namespace Ui {
    class SegmentStat;
}

class SegmentStatWidget : public QWidget
{
    Q_OBJECT
public:
    SegmentStatWidget(int i, QWidget *parent);
    ~SegmentStatWidget();

    void setStat(double area, int points);
    void setIndex(int i);

signals:
    void focusReceived(int i);

private:
    virtual void mouseReleaseEvent(QMouseEvent *);
    void setTitle();

private:
    Ui::SegmentStat *ui;
    int index;
};

#endif // SEGMENT_STAT_WIDGET_H
