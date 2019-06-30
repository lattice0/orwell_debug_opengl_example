#include "mediaplayermanager.h"
#include "bridge.h"
#include "eventdispatcher.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QFileOpenEvent>

#include "OpenGlVideoQtQuick2.h"
#include <QScreen> 

#include <iostream>

namespace {
struct RegisterQMLMetaType {
  RegisterQMLMetaType() { qRegisterMetaType<MediaPlayerManager *>(); }
} registerMetaType;
} // namespace

class MediaPlayerManagerPrivate {
public:
  Bridge *bridge = nullptr;
};

MediaPlayerManager::MediaPlayerManager(QObject *parent)
    : ViewManager(parent), d_ptr(new MediaPlayerManagerPrivate) {

}

ViewManager* MediaPlayerManager::viewManager() {
    return this;
}

MediaPlayerManager::~MediaPlayerManager() {
}

QList<ModuleMethod *> MediaPlayerManager::methodsToExport() {
  return QList<ModuleMethod *>{};
}

void MediaPlayerManager::setBridge(Bridge *bridge) {
  Q_D(MediaPlayerManager);

  d->bridge = bridge;
}


QString MediaPlayerManager::moduleName() { return "RCTMediaPlayerManager"; }

void MediaPlayerManager::test(QString text, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {
  Q_D(MediaPlayerManager);
  std::cout << text.toStdString() << std::endl;
}

QQuickItem* MediaPlayerManager::createView(const QVariantMap& properties) {

    OpenGlVideoQtQuick2* item = new OpenGlVideoQtQuick2();

    //item->setWidth(200);
    //item->setHeight(200);
    std::cout << "returning custom item" << std::endl;
    return item;
}


