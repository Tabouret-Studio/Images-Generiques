#version 330

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec4 vColor_vs; // Couleur
in vec2 vUV_vs;

out vec4 fFragColor;

uniform bool uTexturedMesh;
uniform sampler2D uTexture;

void main()
{
	vec4 sampled = texture(uTexture, vUV_vs);

	if(sampled.a < 0.05)
		discard;

	fFragColor = vec4(vec3(vColor_vs.xyz), 1.0) * sampled;

	/*fFragColor = vec4(vColor_vs.xyz, 1.0) * sampled;*/


	return;
}
