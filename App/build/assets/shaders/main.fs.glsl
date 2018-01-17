#version 330

#ifdef GL_OES_standard_derivatives
#extension GL_OES_standard_derivatives : enable
#endif

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec4 vColor_vs; // Couleur
in vec2 vUV_vs;

out vec4 fFragColor;

uniform bool uTexturedMesh;
uniform sampler2D uTexture;

void main()
{
	if(uTexturedMesh)
	{
		//texture
		fFragColor = vec4(texture(uTexture, vUV_vs).rgb, .5);

		if (fFragColor.r <= 0.05 && fFragColor.g <= 0.05 && fFragColor.b <= 0.05) {
			discard;
		}

		return;
	}

	//color + Rounded points + AA
	float r = 0.0, delta = 0.0, alpha = 1.0;
	vec2 cxy = 2.0 * gl_PointCoord - 1.0;
	r = dot(cxy, cxy);
#ifdef GL_OES_standard_derivatives
	delta = fwidth(r);
	alpha = 1.0 - smoothstep(1.0 - delta, 1.0 + delta, r);
#endif

	fFragColor = vColor_vs * alpha;

	//FragColor = vColor_vs;
}
