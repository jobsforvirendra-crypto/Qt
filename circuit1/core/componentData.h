#ifndef COMPONENTDATA_H
#define COMPONENTDATA_H
#include <QString>
#include <QPointF>
#include <QVector>
#include "pin.h"

struct ComponentData
{
    QString type;
    QPointF position;
    int rotation = 0;
    QVector<Pin> pins;
};

#endif // COMPONENTDATA_H
