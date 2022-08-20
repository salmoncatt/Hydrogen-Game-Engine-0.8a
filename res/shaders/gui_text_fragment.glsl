#version 400 core

in vec3 colour;
in vec2 pass_texture_coord;

out vec4 out_Color;

uniform vec3 color;

uniform sampler2D sampler;

void main(void){
	//out_Color = vec4(1.0, 1.0, 1.0, 1.0);
	//out_Color = v4f(1, 1, 0, 1);
	//vec4 sampled = vec4(1, 1, 1, texture(sampler, pass_texture_coord).r);
	

	float glyph_color = texture(sampler, pass_texture_coord).r;

    //if (glyph_color < 0.5)
    //    discard;

    //vec4 sampled = vec4(glyph_color);
	out_Color = vec4(color, glyph_color * 2);


	//out_Color = vec4(pass_texture_coord.x, pass_texture_coord.y, 0, 1);

}