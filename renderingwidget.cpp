#include "renderingwidget.h"

#include <QCoreApplication>
#include <QKeyEvent>

RenderingWidget::RenderingWidget(const QGLFormat & format, QWidget * parent)
    : QGLWidget(format, parent) {
}

void RenderingWidget::initializeGL() {

    const GLuint WIDTH = 800, HEIGHT = 600;
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void RenderingWidget::resizeGL(int w, int h) {

}

void RenderingWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingWidget::keyPressEvent(QKeyEvent * e) {

    switch (e->key())
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;

        default:
            QGLWidget::keyPressEvent(e);
    }
}
