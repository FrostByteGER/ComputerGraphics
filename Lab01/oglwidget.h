#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QApplication>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public slots:
    void setParamA( int newa );

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void keyPressEvent( QKeyEvent* e );
    GLfloat parama;

private:
    GLboolean updateRenderMode = false;

};

#endif // OGLWIDGET_H
