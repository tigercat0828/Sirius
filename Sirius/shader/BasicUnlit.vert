#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fColor;
out vec2 fTexCoord;

void main(){
	
	gl_Position =  projection* view *  model* vec4(vPos, 1.0);
	//fColor = vColor;
	fTexCoord = vTexCoord;
}