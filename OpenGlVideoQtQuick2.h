#ifndef OpenGlVideoQtQuick2_H
#define OpenGlVideoQtQuick2_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QString>
#include <iostream>
#include <boost/thread.hpp>
#include <QTimer>
#include <QMatrix4x4>
#include <QQmlListProperty>
#include "reactitem.h"
#include <QQuickPaintedItem>

//#include "reactitem.h"


class OpenGlVideoQtQuick2Renderer2 : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGlVideoQtQuick2Renderer2() {        
    }
    ~OpenGlVideoQtQuick2Renderer2();
    void updateData(unsigned char**data, int frameWidth, int frameHeight);
    void setWindow(QQuickWindow *window) { m_window = window; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setPosition(const QPoint &position) { m_position = position; }
    void setDimensions(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    QMatrix4x4 qQuickVideoMatrix;

public slots:
    void render();

private:
    QSize m_viewportSize;
    QOpenGLShaderProgram* program;
    QQuickWindow *m_window;
    GLuint unis[3] = {0};
    GLuint texs[3] = { 0 };
    unsigned char *datas[3] = { 0 };
    bool firstRender = true;
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
    QPoint m_position;
    int frameWidth;
    int frameHeight;
};

class OpenGlVideoQtQuick2 : public ReactItem
{
    Q_OBJECT
    Q_PROPERTY(QString uri WRITE setUri)// NOTIFY uriChanged)


public:
    OpenGlVideoQtQuick2();
    OpenGlVideoQtQuick2(std::string uri);
    QMatrix4x4 getModelMatrix();
    std::string uri;
    void setUri(const QString &a) {
        uri = a.toStdString();
    }
    void paint(QPainter* painter){};
    QSGNode * updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) {}// https://stackoverflow.com/questions/56658299/opengl-strange-behaviour-in-qt-when-inheriting-from-qquickitem-versus-qquickpain


signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();
    void update();//Updates the window


private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    OpenGlVideoQtQuick2Renderer2 *openGlVideoQtQuick2Renderer2;

};

#endif // OpenGlVideoQtQuick2_H
