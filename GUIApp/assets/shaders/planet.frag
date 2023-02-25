#version 430

in vec3 LightIntensity;

out vec4 FragColor;

uniform vec3 MainColor;

void main()
{
    FragColor = vec4(LightIntensity * MainColor,1.0);
}
