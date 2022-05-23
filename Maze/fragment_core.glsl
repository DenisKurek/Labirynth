#version 440

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

struct Light {
	vec3 position;
	vec3 color;
	float intensity;
	float constant;
	float linear;
	float quadratic;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform Light light;
uniform vec3 cameraPos;

vec3 calculateAmbient(Material material) {
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos) {
	vec3 posToLightDirVec = normalize(lightPos - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, normalize(vs_normal)), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos, vec3 cameraPos) {
	vec3 lightToPosDirVec = normalize(vs_position - lightPos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.9), 2);
	//vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;
	vec3 specularFinal = material.specular * specularConstant;

	return specularFinal;
}

void main() {
	//fs_color = vec4(vs_color, 1.f);
	//fs_color = texture(texture0, vs_texcoord) * texture(texture1, vs_texcoord) * vec4(vs_color, 1.f);

	// Ambient light
	vec3 ambientFinal = calculateAmbient(material);

	// Diffuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, light.position);

	// Specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, light.position, cameraPos);

	// Attenuation
	float distance = length(light.position - vs_position);
	// Constant linear quadratic
	float attenuation = light.constant / (1.f + light.linear * distance + light.quadratic * (distance * distance));

	// Final lighting
	ambientFinal *= attenuation;
	diffuseFinal *= attenuation;
	specularFinal *= attenuation;

	fs_color = texture(material.diffuseTex, vs_texcoord) * (vec4(ambientFinal, 1.f)
		+ vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
}
