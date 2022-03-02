#version 400 core

in vec3 position;

out vec3 colour;

uniform mat4 transform;

void main(void){

	gl_Position = transform * vec4(position, 1.0);
	colour = vec3(position.x+0.5,0.0,position.y+0.5);
}