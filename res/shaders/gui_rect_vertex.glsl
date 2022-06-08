#version 400 core

in vec2 position;
//in vec2 texture_coords;

out vec3 colour;
//out vec2 pass_texture_coords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main(void){

	//pass_texture_coords = texture_coords;
	//gl_Position = projection * view * transform * vec4(position, 1.0);
	gl_Position = transform * vec4(position, 0.0, 1.0);
	colour = vec3(position.x,0.0,position.y);
}