#version 400 core

in vec3 colour;
in vec2 pass_texture_coords;

out vec4 out_Color;

sampler2D sampler;

void main(void){
	
	//out_Color = vec4(pass_texture_coords.x, pass_texture_coords.y, 0, 1);

	out_Color = texture(sampler, pass_texture_coords);

}