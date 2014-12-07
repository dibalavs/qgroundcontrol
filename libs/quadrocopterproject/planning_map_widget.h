#ifndef PLANNING_MAP_WIDGET_H
#define PLANNING_MAP_WIDGET_H

#include "segment_manager.h"

#include "../libs/opmapcontrol/opmapcontrol.h"
#include "../libs/opmapcontrol/src/mapwidget/basenavitem.h"

// Choose one default map type
//#define MAP_DEFAULT_TYPE_BING
#define MAP_DEFAULT_TYPE_GOOGLE
//#define MAP_DEFAULT_TYPE_OSM

class SelectionItem : public BaseNavItem
{
    Q_OBJECT
public:
    SelectionItem(SegmentManager *_sm, mapcontrol::MapGraphicItem *map);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void RefreshPos();

public:
    void updateActions();

signals:
    void canAddPoint(bool);
    void canDeletePoint(bool);
    void canDeleteSelection(bool);

public slots:
    bool setSelectedItem(int item);
    bool deleteSelection(int item);

    // segment manager
    void changeSegment(int i, double area, const Segment& seg);
    void addSegment(int i, double area, const Segment& seg);

private:
    void RefreshItem(int i);

private:
    mapcontrol::MapGraphicItem *mmap;
    SegmentManager *sm;

    QVector<Segment> selections;
    QVector<QGraphicsPolygonItem*> selectionItems;

    int currentSelection;
    QBrush dotBrush;

    QPen selectionPen;
    QPen currSelectionPen;
    QBrush selectionBrush;
    QBrush currSelectionBrush;
};

class PlanningMapWidget : public mapcontrol::OPMapWidget
{
    Q_OBJECT
public:
    explicit PlanningMapWidget(SegmentManager *_sm, QWidget *parent = 0);
    ~PlanningMapWidget();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private slots:
    void addPointActionTriggered();
    void addNewSelection();
    void deleteCurrentSelection();
    void finishPoints();

private:
    SegmentManager *sm;
    QPoint currMousePos;
    class SelectionItem *selection;
};

#endif // PLANNING_MAP_WIDGET_H
