#include "planning_map_toolbar.h"
#include "segment_line_manager.h"

#include <QAction>

PlanningMapToolbar::PlanningMapToolbar(SegmentLineManager *mgr, QWidget *parent)
  : QToolBar(parent)
  , lineMgr(mgr)
{
    addAction("action", mgr, SLOT(calcLines()));
}
