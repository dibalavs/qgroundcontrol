#include "segment_line_manager.h"
#include "segment_manager.h"

#include <QtCore>

SegmentLineManager::SegmentLineManager(SegmentManager *_sm, QObject *parent)
  : QObject(parent)
  , sm(_sm)
{
}

void SegmentLineManager::calcLines()
{
    qWarning() << "Hello from calcLines";
    for (int i = 0; i < sm->)
}
