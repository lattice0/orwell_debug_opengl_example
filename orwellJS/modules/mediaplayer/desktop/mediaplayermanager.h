#ifndef MediaPlayerManager_H
#define MediaPlayerManager_H

#include "componentmanagers/viewmanager.h"
#include "moduleinterface.h"
#include <QVariantMap>


class MediaPlayerManagerPrivate;
class MediaPlayerManager : public ViewManager {
    Q_OBJECT
    Q_INTERFACES(ModuleInterface)

    Q_DECLARE_PRIVATE(MediaPlayerManager)

public:
    Q_INVOKABLE MediaPlayerManager(QObject* parent = 0);
    ~MediaPlayerManager();
    Q_INVOKABLE void test(QString text, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    virtual ViewManager* viewManager() override;
    virtual QString moduleName() override;
    QList<ModuleMethod *> methodsToExport();
    //QVariantMap constantsToExport();
    void setBridge(Bridge *bridge);

protected:
    virtual QQuickItem* createView(const QVariantMap& properties) override;

private:
    QScopedPointer<MediaPlayerManagerPrivate> d_ptr;

};

#endif // MediaPlayerManager_H
