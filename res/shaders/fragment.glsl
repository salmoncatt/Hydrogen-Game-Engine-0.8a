#version 400 core
#extension GL_ARB_bindless_texture : require

in vec3 colour;
in vec2 pass_texture_coords;

out vec4 out_Color;

uniform sampler2D sampler;

void main(void){
	

	out_Color = texture(sampler, pass_texture_coords);
	//out_Color = vec4(pass_texture_coords.x, pass_texture_coords.y, 0, 1);

}