#version 330 core
in vec3 fColor;
in vec2 fTexCoord;

out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture0;

uniform float mixVal;
void main() {

	// FragColor = vec4(fColor, 1.0f);
	// FragColor = texture(Texture1, fTexCoord);
	// FragColor = texture(Texture1, fTexCoord) * texture(Texture2, fTexCoord);
	// FragColor = mix(texture(Texture1, fTexCoord),texture(Texture2, fTexCoord),mixVal) * vec4(fColor,1.0f);
	FragColor = mix(texture(texture0, fTexCoord),texture(texture1, fTexCoord),mixVal);
	
}