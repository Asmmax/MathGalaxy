#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec3 EyeNormal;
out vec3 ToEye;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

void main()
{
	EyeNormal = normalize(NormalMatrix * Normal);
	ToEye = normalize(-(ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz);
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
