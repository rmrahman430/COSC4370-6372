#version 330 core
out vec4 color;

in vec2 UV;
uniform sampler2D myTextureSampler;

void main() {
	// Sample the texture using the UV coordinates
	vec4 texColor = texture(myTextureSampler, UV);

	// Set the fragment color to the texture color
	color = texColor;
}
