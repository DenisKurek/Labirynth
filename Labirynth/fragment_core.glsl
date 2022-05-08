#version 440

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

uniform vec3 lightPos0;
uniform vec3 camPosition;
void main() {
	//fs_color = vec4(vs_color, 1.f);

	//ambient light
	vec3 ambientLight = material.ambient;

	//diffuse light
	vec3 posToLightDirVec = normalize(vs_position - lightPos0);
	float diffuse =clamp(dot(posToLightDirVec, vs_normal),0,1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	//Specular light
	vec3 lightToPosDirVec = normalize(lightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - camPosition);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = material.specular * specularConstant;


	fs_color =
		texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f)
		* (vec4(ambientLight, 1.f)+ vec4(diffuseFinal,1.f)+ vec4(specularFinal, 1.f));
}