#include "glwidget.h"

GLWidget::GLWidget( const QGLFormat& format, QWidget* parent ) : QGLWidget( format, parent ), vertexBuffer( QOpenGLBuffer::VertexBuffer )
{
}

void GLWidget::initializeGL()
{
    QGLFormat glFormat = QGLWidget::format();
    if ( !glFormat.sampleBuffers() )
        qWarning() << "Could not enable sample buffers";

    // Enable Z-Buffering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    //By default, render the textures and colors.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Prepare a complete shader program…
    if ( !prepareShaderProgram( vertexPath, fragmentPath ) )
        return;

	cameraPosition = QVector3D(0,0,5);

    // Set up MVP camera
    projection.perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    view.lookAt(cameraPosition,QVector3D(0,0,0),QVector3D(0,1,0)); // Move first vector to variable to control camera position
	model = QMatrix4x4();

    // Create our first VAO(A triangle in this case)
    vao1.create();
    vao1.bind();

	//Generate the vertices for the sphere
	generateSphere(vertices);

    // VertexBuffer
    vertexBuffer.create();
    vertexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    if ( !vertexBuffer.bind() )
    {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }
	vertexBuffer.allocate( &vertices[0], vertices.size() * sizeof( GLfloat ) );

    // Bind the shader program so that we can associate variables from our application to the shaders
    if ( !shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    // Enable the "vertexPosition_modelspace" attribute to bind it to our currently bound vertex buffer.
    shader.setAttributeBuffer( "vertexPosition_modelspace", GL_FLOAT, 0, 3 );
    shader.enableAttributeArray( "vertexPosition_modelspace" );

    // We attached everything important to our VAO, now release it and repeat to other VAOs if neccessary
    vao1.release();

}

void GLWidget::resizeGL( int w, int h )
{
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, qMax( h, h ) );
}

void GLWidget::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    if(updateRenderMode)
    {
        changeRenderMode();
    }

    // Transfer the now calculated MVP matrix to the vertex shader
    shader.setUniformValue("MVP",projection * view * model);
	model.rotate(10.0f,QVector3D(0,1,0));
    // Draw stuff
    // For every VAO, bind, draw and then release. Repeat to EVERY VAO!
    vao1.bind();
	glDrawArrays( GL_TRIANGLES, 0, vertices.size() );
    vao1.release();
}

void GLWidget::changeRenderMode()
{
    glGetIntegerv(GL_POLYGON_MODE, &renderMode);
    if(renderMode == GL_LINE){
        qWarning() << "FILL MODE";
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }else if(renderMode == GL_FILL){
        qWarning() << "LINE MODE";
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        qWarning() << "LINE MODE";
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    updateRenderMode = false;
}

void GLWidget::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
    case Qt::Key_Escape:
        QApplication::instance()->quit();
        break;
    case Qt::Key_F1:
        updateRenderMode = true;
        repaint();
        break;
	case Qt::Key_F2:
		repaint();
		break;
    default:
        QGLWidget::keyPressEvent( e );
    }
}

bool GLWidget::prepareShaderProgram( const QString& vertexShaderPath, const QString& fragmentShaderPath )
{
    // First we load and compile the vertex shader…
    bool result = shader.addShaderFromSourceFile( QGLShader::Vertex, vertexShaderPath );
    if ( !result )
        qWarning() << shader.log();

    // …now the fragment shader…
    result = shader.addShaderFromSourceFile( QGLShader::Fragment, fragmentShaderPath );
    if ( !result )
        qWarning() << shader.log();

    // …and finally we link them to resolve any references.
    result = shader.link();
    if ( !result )
        qWarning() << "Could not link shader program:" << shader.log();

    return result;
}

void GLWidget::generateSphere(std::vector<GLfloat>& outVertices)
{
//	outVertices = {
//		-1.0f,-1.0f,-1.0f,
//		-1.0f,-1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f,
//		 1.0f, 1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f,-1.0f,
//		 1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f,-1.0f,
//		 1.0f,-1.0f,-1.0f,
//		 1.0f, 1.0f,-1.0f,
//		 1.0f,-1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f,-1.0f,
//		 1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,
//		-1.0f,-1.0f, 1.0f,
//		 1.0f,-1.0f, 1.0f,
//		 1.0f, 1.0f, 1.0f,
//		 1.0f,-1.0f,-1.0f,
//		 1.0f, 1.0f,-1.0f,
//		 1.0f,-1.0f,-1.0f,
//		 1.0f, 1.0f, 1.0f,
//		 1.0f,-1.0f, 1.0f,
//		 1.0f, 1.0f, 1.0f,
//		 1.0f, 1.0f,-1.0f,
//		-1.0f, 1.0f,-1.0f,
//		 1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,
//		 1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f,
//		 1.0f,-1.0f, 1.0f
//	};

	outVertices = {
		0.0f , 0.0f , 0.0f ,
		1.0f , 0.0f , 1.5707964f ,
		6.123234E-17f , 1.0f , 1.5707964f ,

		0.0f , 0.0f , 0.0f ,
		6.123234E-17f , 1.0f , 1.5707964f ,
		-1.0f , 1.2246469E-16f , 1.5707964f ,

		-0.0f , 0.0f , 0.0f ,
		-1.0f , 1.2246469E-16f , 1.5707964f ,
		-1.8369701E-16f , -1.0f , 1.5707964f ,

		-0.0f , -0.0f , 0.0f ,
		-1.8369701E-16f , -1.0f , 1.5707964f ,
		1.0f , 0.0f , 1.5707964f ,


		//Duplicate?
		1.0f , 0.0f , 1.5707964f ,
		0.0f , 0.0f , 0.0f ,
		0.0f , 0.0f , 0.0f ,

		6.123234E-17f , 1.0f , 1.5707964f ,
		0.0f , 0.0f , 0.0f ,
		-0.0f , 0.0f , 0.0f ,

		-1.0f , 1.2246469E-16f , 1.5707964f ,
		-0.0f , 0.0f , 0.0f ,
		-0.0f , -0.0f , 0.0f ,

		-1.8369701E-16f , -1.0f , 1.5707964f ,
		-0.0f , -0.0f , 0.0f ,
		0.0f , 0.0f , 0.0f

	};
}
