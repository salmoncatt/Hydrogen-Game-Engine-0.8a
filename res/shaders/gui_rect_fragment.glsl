#version 400 core

in vec3 colour;
in vec2 pass_texture_coord;

out vec4 out_Color;

uniform vec4 color;

uniform sampler2D sampler;
uniform bool has_texture;

void main(void){
	//out_Color = vec4(1.0, 1.0, 1.0, 1.0);

	if(has_texture){
		out_Color = texture(sampler, pass_texture_coord);
	}else{
		out_Color = color;
	}

	//out_Color = vec4(pass_texture_coords.x, pass_texture_coords.y, 0, 1);

}