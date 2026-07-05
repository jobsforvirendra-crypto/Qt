#ifndef PIN_H
#define PIN_H
#include <QPointF>
constexpr int startPinX = 0;
constexpr int startPinY = 25;
constexpr int endPinX = 100;
constexpr int endPinY = 25;
struct Pin
{
    QPointF localPosition;
};
#endif // PIN_H
