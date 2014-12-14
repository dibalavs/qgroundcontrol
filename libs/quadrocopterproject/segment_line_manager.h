#ifndef SEGMENT_LINE_MANAGER_H
#define SEGMENT_LINE_MANAGER_H

#include <QObject>

class SegmentManager;
class SegmentLineManager : public QObject
{
    Q_OBJECT
public:
    SegmentLineManager(SegmentManager *_sm, QObject *parent);

public slots:
    void calcLines();

private:
    SegmentManager *sm;
};

#endif // SEGMENT_LINE_MANAGER_H

