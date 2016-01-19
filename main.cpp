
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include <GL/gl.h>
#include <QApplication>

#include "renderingwidget.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);

    RenderingWidget widget(glFormat);
    widget.show();

    return application.exec();
}
