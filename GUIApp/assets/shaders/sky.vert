#version 430

layout (location = 0) in vec3 Position;

out vec3 GlobalCoords;

uniform vec4 Origin;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 MVP;

void main()
{
	GlobalCoords = (ModelMatrix * vec4(Position, 1.0f)).xyz - Origin.xyz;
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
