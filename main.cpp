#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QProcess>

#include "message_handler.h"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Junbaibai");
    app.setOrganizationDomain("Junbaibai");
    app.setApplicationName("hoisavegames");
    QObject::connect(&app, &QGuiApplication::aboutToQuit, &app, [ = ]() {
        qDebug() << 1111;
        for (QObject *obj : QCoreApplication::instance()->children()) {
            if("QProcess" == QString(obj->metaObject()->className())) {
                QProcess * process = (QProcess*)obj;
                qInfo() << "wait for un finished process";
                process->waitForFinished();
            }
        };
    });
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/hoisavegames/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    &app, []() {
        QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
