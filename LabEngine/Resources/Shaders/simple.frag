#version 430 core


layout(location = 0, index = 0) out vec4 finalColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 LightPosition;
uniform bool colorOnly;
uniform vec4 fragColor;
uniform vec4 lightColor;

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
    // Calculate the default ambient color of the model.
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;

    // Calculate Lighting and Diffuse component
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    // Calculate Specular
    float specularStrength = 0.5; //TODO: Expose as variable
    float shininess = 32.0; //TODO: Expose as variable
    vec3 viewDir = normalize(-FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec4 specular = specularStrength * lightColor * spec;

    // Either render a solid color or a texture.
    if(colorOnly){
        finalColor = (ambient + diffuse + specular) * fragColor;
    }else{
        finalColor = (ambient + diffuse + specular) * texture(texture_diffuse0, TexCoords);
    }
}
