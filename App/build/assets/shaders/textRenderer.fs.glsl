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
	if(uTexturedMesh)
	{
		//texture

		float mRed = texture(uTexture, vUV_vs).r;
		float diff = 1.0 - mRed;

		fFragColor = vec4(diff, diff, diff, mRed);

		//fFragColor = texture(uTexture, vUV_vs).r * vec4(1, 1, 1, 1);

		return;
	}

	fFragColor = vec4(0, 0, 0, 0);
}
