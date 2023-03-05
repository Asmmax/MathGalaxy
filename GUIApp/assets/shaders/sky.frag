#version 430

out vec4 FragColor;

uniform vec3 BaseColor;

void main(void)
{
	FragColor = vec4(BaseColor, 1.0);
}
