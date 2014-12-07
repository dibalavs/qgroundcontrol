#include "planning_map_widget.h"

#include <QAction>

SelectionItem::SelectionItem(SegmentManager *_sm, mapcontrol::MapGraphicItem *map)
{
    mmap = map;
    sm = _sm;

    connect(sm, SIGNAL(segmentChanged(int,double,Segment)), this, SLOT(changeSegment(int, double, Segment)));
    connect(sm, SIGNAL(segmentAdded(int,double,Segment)), this, SLOT(addSegment(int,double,Segment)));
    connect(sm, SIGNAL(segmentDeleted(int)), this, SLOT(deleteSelection(int)));
    connect(sm, SIGNAL(segmentSelected(int)), this, SLOT(setSelectedItem(int)));

    currentSelection = -1;
    selectionPen.setColor(QColor(Qt::white));
    selectionPen.setWidth(2);
    selectionBrush.setColor(QColor(100, 100, 255, 220));
    selectionBrush.setStyle(Qt::SolidPattern);

    currSelectionPen.setColor(QColor(Qt::yellow));
    currSelectionPen.setWidth(2);
    currSelectionBrush.setColor(QColor(150, 150, 0, 220));
    currSelectionBrush.setStyle(Qt::SolidPattern);

    dotBrush.setColor(Qt::yellow);
    dotBrush.setStyle(Qt::SolidPattern);
}

QRectF SelectionItem::boundingRect() const
{
    return QRectF();
}

void SelectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;

    if (currentSelection == -1) {
        return;
    }

    Segment& points = selections[currentSelection];
    if (!points.empty()) {
        core::Point pt = mmap->FromLatLngToLocal(points.last());
        int diff = 5;
        painter->setBrush(dotBrush);
        painter->drawPie(pt.X() - diff, pt.Y() - diff,  2 * diff, 2 * diff, 0, 5700);
    }
}

void SelectionItem::RefreshPos()
{
    for (int i = 0; i < selections.size(); ++i) {
        RefreshItem(i);
    }
}

void SelectionItem::RefreshItem(int i)
{
    QPolygonF poly;
    Segment& points = selections[i];
    QGraphicsPolygonItem* item = selectionItems[i];
    for (int i = 0; i < points.size(); ++i) {
        const core::Point pt = mmap->FromLatLngToLocal(points[i]);
        poly.append(QPointF(pt.X(), pt.Y()));
    }

    item->setPolygon(poly);
}

bool SelectionItem::setSelectedItem(int item)
{
    if (currentSelection != -1) {
        selectionItems[currentSelection]->setPen(selectionPen);
        selectionItems[currentSelection]->setBrush(selectionBrush);
        currentSelection = -1;
    }

    if (item < 0 || item > selections.size()) {
        updateActions();
        return false;
    }

    currentSelection = item;
    selectionItems[currentSelection]->setPen(currSelectionPen);
    selectionItems[currentSelection]->setBrush(currSelectionBrush);
    updateActions();
    return true;
}

void SelectionItem::updateActions()
{
    emit canAddPoint(currentSelection != -1);
    emit canDeletePoint(currentSelection != -1 && !selections[currentSelection].empty());
    emit canDeleteSelection(currentSelection != -1 && !selections.empty());
}

bool SelectionItem::deleteSelection(int item)
{
    if (item < 0 || item > selections.size()) {
        return false;
    }

    selections.removeAt(item);
    selectionItems[item]->setParentItem(NULL);
    delete selectionItems[item];
    selectionItems.removeAt(item);
    return true;
}

void SelectionItem::changeSegment(int i, double area, const Segment& seg)
{
    (void)area;
    if (i < 0 || i >= selections.size()) {
        return;
    }

    selections[i] = seg;
    RefreshItem(i);
    updateActions();
}

void SelectionItem::addSegment(int i, double area, const Segment& seg)
{
    (void)area;
    if (i < selections.size()) {
        return;
    }

    QGraphicsPolygonItem *pi = new QGraphicsPolygonItem(mmap);
    pi->setPen(selectionPen);
    pi->setBrush(selectionBrush);
    selectionItems.insert(i, pi);
    selections.insert(i, seg);
    updateActions();
}

PlanningMapWidget::PlanningMapWidget(SegmentManager *_sm, QWidget *parent)
    :mapcontrol::OPMapWidget(parent)
    ,sm(_sm)
{
    //default appears to be Google Hybrid, and is broken currently
    #if defined MAP_DEFAULT_TYPE_BING
    this->SetMapType(MapType::BingHybrid);
    #elif defined MAP_DEFAULT_TYPE_GOOGLE
    this->SetMapType(MapType::GoogleHybrid);
    #else
    this->SetMapType(MapType::OpenStreetMap);
    #endif

    selection = new SelectionItem(sm, map);
    selection->setParentItem(map);
    selection->setZValue(3);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction *addPoint = new QAction(this);
    addPoint->setText("Add point");
    connect(selection, SIGNAL(canAddPoint(bool)), addPoint,SLOT(setEnabled(bool)));
    connect(addPoint,SIGNAL(triggered()),this,SLOT(addPointActionTriggered()));
    this->addAction(addPoint);

    QAction *remPoint = new QAction(this);
    remPoint->setText("Remove point");
    connect(selection, SIGNAL(canDeletePoint(bool)), remPoint,SLOT(setEnabled(bool)));
    connect(remPoint,SIGNAL(triggered()), sm,SLOT(removeLastPoint()));
    this->addAction(remPoint);

    QAction *finishPoints = new QAction(this);
    finishPoints->setText("Finish point");
    connect(selection, SIGNAL(canDeletePoint(bool)), finishPoints,SLOT(setEnabled(bool)));
    connect(finishPoints,SIGNAL(triggered()), this,SLOT(finishPoints()));
    this->addAction(finishPoints);

    QAction *clearPoints = new QAction(this);
    clearPoints->setText("Clear point");
    connect(selection, SIGNAL(canDeletePoint(bool)), clearPoints,SLOT(setEnabled(bool)));
    connect(clearPoints,SIGNAL(triggered()), sm,SLOT(clearPoints()));
    this->addAction(clearPoints);

    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    this->addAction(separator);

    QAction *newSelections = new QAction(this);
    newSelections->setText("New selection");
    connect(newSelections,SIGNAL(triggered()),this,SLOT(addNewSelection()));
    this->addAction(newSelections);

    QAction *delSelections = new QAction(this);
    delSelections->setText("Delete selection");
    connect(selection, SIGNAL(canDeleteSelection(bool)), delSelections,SLOT(setEnabled(bool)));
    connect(delSelections,SIGNAL(triggered()),this,SLOT(deleteCurrentSelection()));
    this->addAction(delSelections);

    selection->updateActions();
}

PlanningMapWidget::~PlanningMapWidget()
{

}

void PlanningMapWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton || ev->button() == Qt::LeftButton) {
        currMousePos = ev->pos();
    }

    mapcontrol::OPMapWidget::mousePressEvent(ev);
}

void PlanningMapWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton && currMousePos == ev->pos()) {
        sm->addPoint(map->FromLocalToLatLng(currMousePos.x(), currMousePos.y()));
    }

    mapcontrol::OPMapWidget::mouseReleaseEvent(ev);
}

void PlanningMapWidget::addPointActionTriggered()
{
    sm->addPoint(map->FromLocalToLatLng(currMousePos.x(), currMousePos.y()));
}

void PlanningMapWidget::addNewSelection()
{
    sm->addSegment(sm->getTotalSections(), Segment());
}

void PlanningMapWidget::deleteCurrentSelection()
{
    sm->removeSegment(sm->getSelection());
}

void PlanningMapWidget::finishPoints()
{
    sm->selectSegment(-1);
}
