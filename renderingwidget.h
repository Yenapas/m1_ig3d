#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H
#define GL_GLEXT_PROTOTYPES
#include <QtOpenGL/QGLWidget>

class RenderingWidget : public QGLWidget
{
    Q_OBJECT
public:
    RenderingWidget(const QGLFormat & format, QWidget * parent = 0);
    ~RenderingWidget() {}

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent * e);

private:

};

#endif // RENDERINGWIDGET_H
