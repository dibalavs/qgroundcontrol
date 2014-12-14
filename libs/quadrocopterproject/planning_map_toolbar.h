#ifndef PLANNING_MAP_TOOLBAR_H
#define PLANNING_MAP_TOOLBAR_H

#include <QToolBar>

class SegmentLineManager;
class PlanningMapToolbar : public QToolBar
{
    Q_OBJECT
public:
    PlanningMapToolbar(SegmentLineManager *mgr, QWidget *parent);

private:
    SegmentLineManager *lineMgr;
};

#endif // PLANNING_MAP_TOOLBAR_H

