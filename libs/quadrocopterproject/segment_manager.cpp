#include "segment_manager.h"

SegmentManager::SegmentManager(QObject *parent)
  : QObject(parent)
  , selection(-1)
{

}

static double calcSegmentArea(const Segment& segment)
{
    return 1.2;
}

void SegmentManager::addSegment(int i, const Segment &pts)
{
    segments.insert(i, pts);
    emit segmentAdded(i, calcSegmentArea(segments[i]), segments[i]);
    selectSegment(i);
}

void SegmentManager::changeSegment(int i, const Segment &pts)
{
    segments[i] = pts;
    emit segmentChanged(i, calcSegmentArea(segments[i]), segments[i]);
}

void SegmentManager::removeSegment(int i)
{
    if (segments.empty() || i < 0 || i >= segments.size()) {
        return;
    }

    int oldSelection = selection;
    if (selection >= i) {
        selectSegment(-1);
    }

    segments.removeAt(i);
    emit segmentDeleted(i);

    if (oldSelection >= i) {
        oldSelection--;
        selectSegment(oldSelection);
    }
}

void SegmentManager::addPoint(const internals::PointLatLng &pt)
{
    if (selection == -1) {
        return;
    }

    segments[selection].append(pt);
    emit segmentChanged(selection, calcSegmentArea(segments[selection]), segments[selection]);
}

void SegmentManager::removeLastPoint()
{
    if (selection == -1) {
        return;
    }

    if (segments[selection].empty()) {
        return;
    }

    segments[selection].removeLast();
    emit segmentChanged(selection, calcSegmentArea(segments[selection]), segments[selection]);
}

void SegmentManager::clearPoints()
{
    if (selection == -1) {
        return;
    }

    if (segments[selection].empty()) {
        return;
    }

    segments[selection].clear();
    emit segmentChanged(selection, calcSegmentArea(segments[selection]), segments[selection]);
}

void SegmentManager::selectSegment(int i)
{
    if (i >= -1 && i < segments.size()) {
        selection = i;
        emit segmentSelected(i);
    }
}

int SegmentManager::getSelection() const
{
    return selection;
}

int SegmentManager::getTotalSections() const
{
    return segments.size();
}
