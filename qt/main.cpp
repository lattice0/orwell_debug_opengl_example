#include <iostream>
#include <QApplication>
#include <QMediaPlayer>
#include <QPushButton>
#include <boost/thread.hpp>

#include <QGuiApplication>

#include <QtQuick/QQuickView>

#include "OpenGlVideoQtQuick2.h"


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QCoreApplication::addLibraryPath("./");
    qmlRegisterType<OpenGlVideoQtQuick2>("OpenGlVideoQtQuick2", 1, 0, "OpenGlVideoQtQuick2");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
