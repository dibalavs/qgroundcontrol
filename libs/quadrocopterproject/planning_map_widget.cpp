#include "planning_map_widget.h"

#include <QAction>

SelectionItem::SelectionItem(mapcontrol::MapGraphicItem *map)
{
    mmap = map;

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

    Points& points = selections[currentSelection];
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
    Points& points = selections[i];
    QGraphicsPolygonItem* item = selectionItems[i];
    for (int i = 0; i < points.size(); ++i) {
        const core::Point pt = mmap->FromLatLngToLocal(points[i]);
        poly.append(QPointF(pt.X(), pt.Y()));
    }

    item->setPolygon(poly);
}

void SelectionItem::addPoint(const QPoint& pos)
{
    if (currentSelection == -1) {
        return;
    }

    selections[currentSelection].push_back(mmap->FromLocalToLatLng(pos.x(), pos.y()));
    RefreshItem(currentSelection);
    updateActions();
}

bool SelectionItem::getSelection(int item, QVector<internals::PointLatLng>& data)
{
    if (item < 0 || item >= selections.size()) {
        return false;
    }

    data = selections[item];
    return true;
}

int SelectionItem::getSelectionsNumber()
{
    return selections.size();
}

void SelectionItem::removePoint()
{
    if (currentSelection == -1) {
        return;
    }

    selections[currentSelection].removeLast();
    RefreshItem(currentSelection);
    updateActions();
}

void SelectionItem::clearPoints()
{
    if (currentSelection == -1) {
        return;
    }

    selections[currentSelection].clear();
    RefreshItem(currentSelection);
    updateActions();
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

    int oldSel = currentSelection;
    if (oldSel >= item) {
        setSelectedItem(-1);
    }

    selections.removeAt(item);
    selectionItems[item]->setParentItem(NULL);
    delete selectionItems[item];
    selectionItems.removeAt(item);

    if (oldSel >= item) {
        if (!setSelectedItem(oldSel - 1)) {
            if(!setSelectedItem(selections.size() - 1)) {
                currentSelection = -1;
            }
        }
    }

    return true;
}

void SelectionItem::deleteCurrentSelection()
{
    deleteSelection(currentSelection);
}

void SelectionItem::addNewSelection()
{
    QGraphicsPolygonItem *pi = new QGraphicsPolygonItem(mmap);
    pi->setPen(selectionPen);
    pi->setBrush(selectionBrush);
    selectionItems.push_back(pi);
    selections.push_back(Points());
    setSelectedItem(selections.size() - 1);
    emit canAddPoint(true);
    emit canDeletePoint(false);
    emit canDeleteSelection(true);
}

PlanningMapWidget::PlanningMapWidget(QWidget *parent)
    :mapcontrol::OPMapWidget(parent)
{
    //default appears to be Google Hybrid, and is broken currently
    #if defined MAP_DEFAULT_TYPE_BING
    this->SetMapType(MapType::BingHybrid);
    #elif defined MAP_DEFAULT_TYPE_GOOGLE
    this->SetMapType(MapType::GoogleHybrid);
    #else
    this->SetMapType(MapType::OpenStreetMap);
    #endif

    selection = new SelectionItem(map);
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
    connect(remPoint,SIGNAL(triggered()), selection,SLOT(removePoint()));
    this->addAction(remPoint);

    QAction *clearPoints = new QAction(this);
    clearPoints->setText("Clear point");
    connect(selection, SIGNAL(canDeletePoint(bool)), clearPoints,SLOT(setEnabled(bool)));
    connect(clearPoints,SIGNAL(triggered()), selection,SLOT(clearPoints()));
    this->addAction(clearPoints);

    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    this->addAction(separator);

    QAction *newSelections = new QAction(this);
    newSelections->setText("New selection");
    connect(newSelections,SIGNAL(triggered()),selection,SLOT(addNewSelection()));
    this->addAction(newSelections);

    QAction *delSelections = new QAction(this);
    delSelections->setText("Delete selection");
    connect(selection, SIGNAL(canDeleteSelection(bool)), delSelections,SLOT(setEnabled(bool)));
    connect(delSelections,SIGNAL(triggered()),selection,SLOT(deleteCurrentSelection()));
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
        selection->addPoint(currMousePos);
    }

    mapcontrol::OPMapWidget::mouseReleaseEvent(ev);
}

void PlanningMapWidget::addPointActionTriggered()
{
    selection->addPoint(currMousePos);
}
