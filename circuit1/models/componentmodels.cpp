#include "componentmodels.h"

ComponentModels::ComponentModels(QObject *parent)
    : QAbstractListModel{parent}
{}

int ComponentModels::rowCount(const QModelIndex &parent) const
{
    return m_components.size();
}

QVariant ComponentModels::data(const QModelIndex &index, int role) const
{
    const auto& comp = m_components[index.row()];
    switch(role)
    {
    case TypeRole:
        return comp.type;
    case XRole:
        return comp.position.x();
    case YRole:
        return comp.position.y();
    case RotationRole:
        return comp.rotation;
    case PinsRole:
    {
        QVariantList list;
        for(const auto& pin: comp.pins)
        {
            QVariantMap map;

            map["x"] = pin.localPosition.x();
            map["y"] = pin.localPosition.y();

            list.append(map);
        }
        return list;
    }
    }

    return {};
}

QHash<int, QByteArray> ComponentModels::roleNames() const
{
    return {
        {TypeRole,"type"},
        {XRole,"posX"},
        {YRole,"posY"},
        {RotationRole,"rotationAngle"},
        {PinsRole,"pins"}
    };
}

void ComponentModels::addComponent(const QString &type, qreal x, qreal y)
{
    ComponentData comp;
    comp.type = type;
    comp.position = QPointF(x,y);
    comp.rotation =0;
    if(type == "Resistor")
    {
        comp.pins = {
            {{startPinX,startPinY}},
            {{endPinX,endPinY}}
        };
    }
    beginInsertRows(QModelIndex(),m_components.size(),m_components.size());
  //  m_components.push_back({type,QPointF(x,y)});
    m_components.push_back(comp);

    endInsertRows();

}

void ComponentModels::moveComponent(int index, qreal x, qreal y)
{
    if(index < 0 || index >= m_components.size())
        return;

    m_components[index].position = QPointF(x,y);

    emit dataChanged(this->index(index),this->index(index),{XRole,YRole});
}

void ComponentModels::rotateComponent(int index)
{
    if(index < 0 || index >= m_components.size())
        return;

    auto& comp = m_components[index];

    comp.rotation += 90;

    if(comp.rotation >= 360)
        comp.rotation =0;

    emit dataChanged(this->index(index),
                     this->index(index),
                     {RotationRole});
}
