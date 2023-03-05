#version 430

struct StarInfo 
{
	vec3 BaseColor;
	vec3 BoundColor;
	vec3 SpaceColor;
};

in vec3 EyeNormal;
in vec3 ToEye;

out vec4 FragColor;

uniform StarInfo Star;

void main(void)
{
	float pre_coef = 1.0 - abs(dot(EyeNormal, ToEye));
	
	float bound_coef = exp(-pre_coef + 0.5) - 0.8;
	
	float fon_coef = exp(-pre_coef) - 0.5;
	fon_coef = fon_coef > 0.2 ? 1.0 : fon_coef;
	
	FragColor = vec4(2.0*(Star.BaseColor*bound_coef + Star.BoundColor*(1.0 - bound_coef))*fon_coef + Star.SpaceColor*(1.0 - fon_coef), 1.0);
}
