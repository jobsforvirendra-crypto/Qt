#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/componentmodels.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ComponentModels componentModel;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("ComponentModel", &componentModel);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("circuit1", "Main");

    return app.exec();
}
