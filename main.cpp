#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "fund_http_manager.h"
#include <QSslSocket>
#include "fund_list.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    DataModel model;

    model.append("银河创新成长混合",519674,1.0,1.7447,-0.24,"123","123");
    model.append("诺安成长混合",320007,1.0,5.8416,-0.3,"123","123");
    model.append("招商中证白酒指数分级",161725,1.0,1.2081,3.43,"123","123");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("$Model",&model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
    //Fund_HTTP_Manager* tmp = Fund_HTTP_Manager::getInstance();
    //tmp->Slot_QueryFundInfo("320007");
    return app.exec();
}
