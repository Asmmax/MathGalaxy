#version 430

const float PI = 3.14159265;

in vec3 GlobalCoords;

out vec4 FragColor;

uniform vec3 BaseColor;
uniform sampler2D skyMap;


vec2 vec3ToUV( vec3 vector )
{
    float theta = acos(-vector.z);
    float phi = -atan(vector.y, vector.x);
    float u = ( phi) / (2. * PI);
    float v = theta / PI;
    return vec2(u,v);
}

void main(void)
{
	vec2 uv = vec3ToUV(normalize(GlobalCoords));
	FragColor = texture(skyMap, uv);
}
