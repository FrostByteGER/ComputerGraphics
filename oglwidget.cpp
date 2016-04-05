#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setFocus();
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::setParamA(int newa)
{
    parama = newa * 0.9f; // Set new value
    this->setFocus();
    update();      // Trigger redraw of scene with paintGL
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    parama = 0.0f;
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(updateRenderMode){
        GLint renderMode;
        glGetIntegerv(GL_POLYGON_MODE, &renderMode);
        if(renderMode == GL_LINE){
            qWarning("FILL MODE");
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }else if(renderMode == GL_FILL){
            qWarning("LINE MODE");
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }else{
            qWarning("LINE MODE");
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        updateRenderMode = false;
    }
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.5f,0.5f,0.5f);
    glRotatef(-55,1.0f,1.0f,0.0f);
    glBegin(GL_QUADS);

        //Bottom
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        //Back
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);

        //Front
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        //Left
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        //Right
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    glPopMatrix();

    glLoadIdentity();
    glPushMatrix();
    glScalef(0.5f,0.5f,0.5f);
    glRotatef(-55,1.0f,1.0f,0.0f);
    glTranslatef(0.5f,0.5f,0);
    glRotatef(-parama,0.0f,0.0f,1.0f);
    glTranslatef(-0.5f,-0.5f,0);

    glBegin(GL_QUADS);
        //Top
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();
    glPopMatrix();

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
    case Qt::Key_Escape:
        QApplication::instance()->quit();
        break;
    case Qt::Key_F1:
        updateRenderMode = true;
        update();
        break;
    default:
        QOpenGLWidget::keyPressEvent( e );
    }
}

