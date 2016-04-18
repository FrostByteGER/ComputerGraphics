#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

public slots:
    void setParamA( int newa );
    void setParamB( int newb );


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    int parama;
    int paramb;

};

#endif // OGLWIDGET_H
