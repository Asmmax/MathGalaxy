#version 430

layout (location = 0) in vec3 Position;
layout (location = 0) in vec3 Normal;

out vec3 LightIntensity;

uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform vec4 LightPositions[10];
uniform int LightCount = 0;

void main()
{
	vec3 n_norm = normalize(NormalMatrix * Normal);
	vec4 eyeCoords = ModelViewMatrix * vec4(Position, 1.0f);
	
	vec3 sumLightIntensity = vec3(0.0f);
	for(int i = 0; i < LightCount; i++){
		vec3 s = normalize(vec3(ViewMatrix * LightPositions[i] - eyeCoords));
		sumLightIntensity += max(dot(s, n_norm), 0.0) * vec3(1.0f);
	}
	LightIntensity = sumLightIntensity;
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
