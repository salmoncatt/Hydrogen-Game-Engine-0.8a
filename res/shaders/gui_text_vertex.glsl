#version 400 core

in vec2 position;
in vec2 texture_coord;



//out vec3 colour;
out vec2 pass_texture_coord;

uniform mat4 proj;

void main(void){

	gl_Position = proj * vec4(position, 0.0, 1.0);

	pass_texture_coord = texture_coord;

	//pass_texture_coords = texture_coords;
	//gl_Position = projection * view * transform * vec4(position, 1.0);
	//colour = vec3(position.x, position.y, 0);
}