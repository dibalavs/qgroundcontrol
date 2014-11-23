#ifndef BASENAVITEM_H
#define BASENAVITEM_H

#include <QGraphicsItem>

class BaseNavItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum { Type = UserType + 10 };
    virtual void RefreshPos() = 0;

    int type() const
    {
        return Type;
    }
};

#endif // BASENAVITEM_H
