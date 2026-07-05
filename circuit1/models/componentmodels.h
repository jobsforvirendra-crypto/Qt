#ifndef COMPONENTMODELS_H
#define COMPONENTMODELS_H

#include <QAbstractListModel>
#include "../core/componentData.h"

class ComponentModels : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        TypeRole=Qt::UserRole + 1,
        XRole,
        YRole,
        RotationRole,
        PinsRole
    };
    explicit ComponentModels(QObject *parent = nullptr);
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void addComponent(const QString& type, qreal x,qreal y);
    Q_INVOKABLE void moveComponent(int index, qreal x, qreal y);
    Q_INVOKABLE void rotateComponent(int index);

signals:

private:
    QVector<ComponentData> m_components;

};

#endif // COMPONENTMODELS_H
