#version 430

layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;

out vec3 OutNormal;
out vec3 ToEye;

uniform vec3 ViewOrigin;
uniform mat3 NormalMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

void main()
{
	OutNormal = normalize(NormalMatrix * Normal);
	vec3 OutPosition = (ModelMatrix * vec4(Position, 1.0f)).xyz;
	ToEye = normalize(ViewOrigin - OutPosition);
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
