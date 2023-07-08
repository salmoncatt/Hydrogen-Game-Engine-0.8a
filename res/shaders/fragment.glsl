#version 400 core

in vec3 colour;
in vec2 pass_texture_coords;

out vec4 out_Color;

uniform sampler2D sampler;

void main(void){
	
	//out_Color = vec4(colour.xyz, 1.0);
	out_Color = texture(sampler, pass_texture_coords);
	//out_Color = vec4(pass_texture_coords.x, pass_texture_coords.y, 0, 1);

}