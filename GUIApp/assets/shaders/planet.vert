#version 430

layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;

out vec3 OutPosition;
out vec3 OutNormal;

uniform mat3 NormalMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

void main()
{
	OutNormal = normalize(NormalMatrix * Normal);
	OutPosition = (ModelMatrix * vec4(Position, 1.0f)).xyz;
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
