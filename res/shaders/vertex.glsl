#version 400 core

in vec3 position;
in vec2 texture_coords;

out vec3 colour;
out vec2 pass_texture_coords;

uniform mat4 transform;

void main(void){

	pass_texture_coords = texture_coords;
	gl_Position = transform * vec4(position, 1.0);
	colour = vec3(position.x+0.5,0.0,position.y+0.5);
}