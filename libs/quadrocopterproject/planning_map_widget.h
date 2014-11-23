#ifndef PLANNING_MAP_WIDGET_H
#define PLANNING_MAP_WIDGET_H

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
    SelectionItem(mapcontrol::MapGraphicItem *map);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void RefreshPos();

public:
    bool getSelection(int item, QVector<internals::PointLatLng>& data);
    int getSelectionsNumber();

    void updateActions();
signals:
    void canAddPoint(bool);
    void canDeletePoint(bool);
    void canDeleteSelection(bool);

public slots:
    void addPoint(const QPoint& pos);
    void removePoint();
    void clearPoints();

    bool setSelectedItem(int item);
    bool deleteSelection(int item);
    void deleteCurrentSelection();

    void addNewSelection();

private:
    void RefreshItem(int i);

private:
    mapcontrol::MapGraphicItem *mmap;

    typedef QVector<internals::PointLatLng> Points;

    QVector<Points> selections;
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
    explicit PlanningMapWidget(QWidget *parent = 0);
    ~PlanningMapWidget();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private slots:
    void addPointActionTriggered();

private:
    QPoint currMousePos;
    class SelectionItem *selection;
};

#endif // PLANNING_MAP_WIDGET_H
