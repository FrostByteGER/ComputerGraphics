#version 330 core


layout(location = 0, index = 0) out vec4 finalColor;
in vec2 TexCoords;
uniform bool colorOnly;
uniform vec4 fragColor;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

uniform sampler2D texture_specular0;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;

uniform sampler2D texture_normal0;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;
uniform sampler2D texture_normal3;

uniform sampler2D texture_displacement0;
uniform sampler2D texture_displacement1;
uniform sampler2D texture_displacement2;
uniform sampler2D texture_displacement3;


void main( void )
{
    if(colorOnly){
        //finalColor = vec4(0,0.5,1,1);
        finalColor = fragColor;
    }else{
        finalColor = texture2D(texture_diffuse0, TexCoords);
    }
}
