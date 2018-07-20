#include "SFLViewRender.h"
#include <QDebug>
#include <QKeyEvent>

SFLViewRender::SFLViewRender(QWidget *parent):QOpenGLWidget(parent)
{
    setFixedSize(700, 700);
}

void SFLViewRender::paintGL()
{

}

void SFLViewRender::initializeGL()
{
    initializeOpenGLFunctions();

    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    QOpenGLContext *defaultCtx = context();
    GLint attributeNumber;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeNumber);
    qDebug() << "Has default context: " <<  (defaultCtx != nullptr ? "Yes" : "No") << endl
             << "Default context is current context: " << (defaultCtx == ctx ? "Yes" : "No")  << endl
             << "Renderer: " << (const char*)glGetString(GL_RENDERER) << endl
             << "Version:  " << (ctx->isOpenGLES() ? "OpenGL ES" : "OpenGL") << (const char*)glGetString(GL_VERSION) << endl
             << "Shader Version:" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << endl
             << "R:" << ctx->format().redBufferSize() << endl
             << "G:" << ctx->format().greenBufferSize() << endl
             << "B:" << ctx->format().blueBufferSize() << endl
             << "A:" << ctx->format().alphaBufferSize() << endl
             << "Depth:   " << ctx->format().depthBufferSize() << endl
             << "Stencil: " << ctx->format().stencilBufferSize() << endl
             << "Pixel Radio: " << devicePixelRatio() << endl
             << "Support Attribute Number: " << attributeNumber << endl;

    const int pixelRadio = devicePixelRatio();
    glViewport(0, 0, pixelRadio * width(), pixelRadio * height());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void SFLViewRender::keyPressEvent(QKeyEvent *event)
{

}

void SFLViewRender::mousePressEvent(QMouseEvent *event)
{

}
void SFLViewRender::mouseMoveEvent(QMouseEvent *event)
{

}
void SFLViewRender::mouseReleaseEvent(QMouseEvent *event)
{

}
