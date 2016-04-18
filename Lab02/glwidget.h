#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QApplication>
#include <QOpenGLBuffer>
#include <QGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include <QOpenGLTexture>



class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget( const QGLFormat& format, QWidget* parent = 0 );


protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();
    virtual void keyPressEvent( QKeyEvent* e );

private:
    bool prepareShaderProgram( const QString& vertexShaderPath, const QString& fragmentShaderPath );
    void changeRenderMode();
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QVector3D cameraPosition;
    QGLShaderProgram shader;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vao1;
    GLint renderMode;
	GLboolean updateRenderMode = false;
	const QString vertexPath   = ":/Resources/Shaders/simple.vert";
	const QString fragmentPath = ":/Resources/Shaders/simple.frag";

    std::vector<GLfloat> vertices;
};

#endif // GLWIDGET_H
