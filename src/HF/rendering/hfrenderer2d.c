#include "hfrenderer2d.h"

hf_mesh hf_renderer_quad = {};
hf_shader hf_gui_rect_shader = {};
hf_shader hf_gui_text_shader = {};

hf_font hf_main_font = {};

void hf_renderer_init_2d(hf_app* app) {
    f32 hf_quad_vertices[] = {0, 1, 0, 0, 1, 1, 1, 0};
    f32 hf_quad_texture_coords[] = {0, 1, 0, 0, 1, 1, 1, 0};
    
    
    hf_renderer_quad.type = 2; //2d
    hf_renderer_quad.vertices = hf_array_create_from_data(&hf_quad_vertices, f32, 8);
    hf_renderer_quad.texture_coords = hf_array_create_from_data(&hf_quad_texture_coords, f32, 8);
    hf_mesh_create(&hf_renderer_quad);
    
    
    hf_gui_rect_shader.name = "gui rect shader";
    hf_shader_create(&hf_gui_rect_shader, "../res/shaders/gui_rect_vertex.glsl", "../res/shaders/gui_rect_fragment.glsl");
    
    hf_gui_text_shader.name = "gui text shader";
    hf_shader_create(&hf_gui_text_shader, "../res/shaders/gui_text_vertex.glsl", "../res/shaders/gui_text_fragment.glsl");
    
    hf_main_font = hf_font_from_file("../res/fonts/ProggyClean.ttf", 12);
    hf_main_font.color = (v3f){0.9, 0.9, 0.9};
    
    
    
    hf_log("[HF] initialized HF Renderer 2D\n\n");
}

void hf_renderer_destroy_2d(hf_app* app) {
    hf_mesh_destroy(&hf_renderer_quad);
    hf_shader_destroy(&hf_gui_rect_shader);
    hf_shader_destroy(&hf_gui_text_shader);
    hf_log("[HF] destroyed HF Renderer 2D\n");
}

void hf_set_alpha_blending(b8 in){
    if(in){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }else
        glDisable(GL_BLEND);
}

void hf_set_depth_test(b8 in){
    if(in)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void hf_render_mesh_2d(hf_mesh* mesh, hf_shader* shader, hf_transform* transform){
    glBindVertexArray(mesh->vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    
    hf_shader_bind(shader);
    hf_shader_set_uniform_v3f(shader, "pos", &transform->pos);
    
    if(mesh->texture.image.data != NULL){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->texture.texture_id);
    }
    
    m4f transformation = hf_transformation_m4f(transform->pos, transform->rot, transform->scale);
    hf_shader_set_uniform_m4f(shader, "transform", &transformation);
    //position
    
    if(hf_array_size(mesh->indices) > 0)
        glDrawElements(GL_TRIANGLES, hf_array_size(mesh->indices), GL_UNSIGNED_INT, 0);
    else if(hf_array_size(mesh->vertices) > 0)
        glDrawArrays(GL_TRIANGLES, 0, (int)(hf_array_size(mesh->vertices) / mesh->type));
    
    
    hf_shader_unbind();
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}

void hf_render_rect(u32 x, u32 y, u32 w, u32 h, v4f color){
    if(w == 0 || h == 0){
        return; //dont waste a draw call on an empty rectangle
    }
    
    glBindVertexArray(hf_renderer_quad.vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    hf_shader_bind(&hf_gui_rect_shader);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);//very important
    
    /* 
        if(mesh->texture.image.data != NULL){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh->texture.texture_id);
        }
     */
    
    m4f transformation = hf_transformation_m4f_2d(hf_v2f(x, y), 0, hf_v2f(w, h));
    m4f model_proj = hf_mul_m4f(hf_renderer_pixel_ortho, transformation);
    hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "transform", &model_proj);
    //hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "transform", &transformation);
    hf_shader_set_uniform_v4f(&hf_gui_rect_shader, "color", &color);
    hf_shader_set_uniform_b8(&hf_gui_rect_shader, "has_texture", 0);
    //hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "proj", &hf_renderer_pixel_ortho);
    //position
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (u32)(hf_array_size(hf_renderer_quad.vertices)) / 2);
    
    
    hf_shader_unbind();
    
    glEnable(GL_CULL_FACE);//very important
    glEnable(GL_DEPTH_TEST);
    
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void hf_render_rect_texture(u32 x, u32 y, u32 w, u32 h, hf_texture* texture){
    if(w == 0 || h == 0){
        return; //dont waste a draw call on an empty rectangle
    }
    
    glBindVertexArray(hf_renderer_quad.vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    hf_shader_bind(&hf_gui_rect_shader);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);//very important
    
    
    if(texture->image.data != NULL){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->texture_id);
    }
    
    
    m4f transformation = hf_transformation_m4f_2d(hf_v2f(x, y), 0, hf_v2f(w, h));
    m4f model_proj = hf_mul_m4f(hf_renderer_pixel_ortho, transformation);
    hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "transform", &model_proj);
    hf_shader_set_uniform_b8(&hf_gui_rect_shader, "has_texture", 1);
    //hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "transform", &transformation);
    //hf_shader_set_uniform_v4f(&hf_gui_rect_shader, "color", &color);
    //hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "proj", &hf_renderer_pixel_ortho);
    //position
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (u32)(hf_array_size(hf_renderer_quad.vertices)) / 2);
    
    
    hf_shader_unbind();
    
    glEnable(GL_CULL_FACE);//very important
    glEnable(GL_DEPTH_TEST);
    
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void hf_render_font(hf_font* font){
    if(!font->vertices || !font->texture_coords){
        return;
    }else if(hf_array_size(&font->vertices) == 0){
        return;
    }
    
    //copy all characters into the vbo
    
    
    glBindBuffer(GL_ARRAY_BUFFER, font->vbo_vert);
    glBufferSubData(GL_ARRAY_BUFFER, 0, hf_array_size(font->vertices) * sizeof(f32), font->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, font->vbo_tex);
    glBufferSubData(GL_ARRAY_BUFFER, 0, hf_array_size(font->texture_coords) * sizeof(f32), font->texture_coords);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    hf_set_alpha_blending(1);
    
    
    //render all the characters
    
    glBindVertexArray(font->vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    hf_shader_bind(&hf_gui_text_shader);
    glDepthMask(GL_FALSE); // Don't write into the depth buffer
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);//very important
    
    
    if(font->atlas_texture.image.data != NULL){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, font->atlas_texture.texture_id);
    }
    
    
    //m4f transformation = hf_transformation_m4f_2d(hf_v2f(x, y), 0, hf_v2f(w, h));
    //m4f model_proj = hf_mul_m4f(hf_renderer_pixel_ortho, transformation);
    hf_shader_set_uniform_m4f(&hf_gui_text_shader, "proj", &hf_renderer_pixel_ortho);
    hf_shader_set_uniform_v3f(&hf_gui_text_shader, "color", &font->color);
    //hf_shader_set_uniform_b8(&hf_gui_text_shader, "has_texture", 1);
    
    glDrawArrays(GL_TRIANGLES, 0, (u32)(hf_array_size(font->vertices)) / 2);
    
    
    hf_shader_unbind();
    
    glEnable(GL_CULL_FACE);//very important
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    
    hf_set_alpha_blending(0);
    
    //reset the array
    hf_array_free(font->vertices);
    hf_array_free(font->texture_coords);
    font->vertices = hf_array_create(f32);
    font->texture_coords = hf_array_create(f32);
    font->char_count = 0;
}


void hf_renderer_update_2d(){
    hf_render_font(&hf_main_font);
}



/* 
void hf_render_rect_ss(hf_button* button){
    
}
 */