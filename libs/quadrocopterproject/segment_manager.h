#ifndef SEGMENT_MANAGER_H
#define SEGMENT_MANAGER_H

#include <QObject>
#include <QVector>
#include <pointlatlng.h>

typedef QVector<internals::PointLatLng> Segment;

class SegmentManager : public QObject
{
    Q_OBJECT
public:
    SegmentManager(QObject *parent);

    int getSelection() const;

    int getTotalSections() const;
    void getSegment(int i, Segment &pts) const;

public slots:
    void addSegment(int i, const Segment &pts);
    void removeSegment(int i);
    void changeSegment(int i, const Segment &pts);
    void selectSegment(int i);

    void addPoint(const internals::PointLatLng &pt);
    void removeLastPoint();
    void clearPoints();

signals:
    void segmentAdded(int i, double area, const Segment &pts);
    void segmentChanged(int i, double area, const Segment &pts);
    void segmentDeleted(int i);
    void segmentSelected(int i);

private:
    QVector<Segment> segments;
    int selection;
};

#endif // SEGMENT_MANAGER_H
