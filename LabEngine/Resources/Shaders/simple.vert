#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;

void main( void )
{
 gl_Position =  vec4(vertexPosition_modelspace, 1.0);
}
