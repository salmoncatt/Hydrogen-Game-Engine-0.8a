#include "HF/hf.h"



int main(void){
    
    hf_app app = hf_app_defaults();
    app.name = "pong";
    app.parameters = HF_APP_USE_OPENGL | HF_APP_CREATE_WINDOW;
    hf_app_init(&app);
    
    app.window.title = "pong";
    hf_app_start(&app);
    
    //hf_ecs* ecs = &app.ecs;
    
    
    glClearColor(0, 0, 0, 1);
    
    v2f dot_pos = {app.window.width / 2, app.window.height / 2};
    v2f dot_vel = {5, 4};
    
    
    f32 paddle_speed = 400.0f;
    u32 dot_size = 10;
    u32 paddle_height = 200;
    u32 paddle_l_height = 20;
    
    u32 paddle_l_desired = 0;
    
    v2f paddle_l_pos = {0, app.window.height / 2 - paddle_height / 2};
    v2f paddle_r_pos = {0, app.window.height / 2 - paddle_height / 2};
    
    
    b8 collided = 0;
    u32 frame_index, red_frame_amount = 20;
    
    hf_gui_panel panel = hf_gui_panel_defaults();
    panel.x = 100;
    panel.y = 100;
    panel.w = 100;
    panel.h = 100;
    
    u32 l_score = 0, r_score = 0;
    
    f32 bot_speed = 0.03f;
    f32 dot_speed = 1;
    
    b8 debug_enable = 0;
    
    while(hf_app_should_update(&app) && !hf_input_get_key(HF_KEY_ESCAPE)){
        
        panel.x = app.window.width / 2.0 - panel.w / 2.0;
        
        hf_gui_panel_begin(&panel, "score", HF_TITLE_BAR);
        
        char text[64];
        sprintf(text, "  [%u | %u]", l_score, r_score);
        
        
        char text2[64];
        sprintf(text2, "  [bot speed: %.3f]", bot_speed);
        
        char text3[64];
        sprintf(text3, "  [dot speed: (%.3f, %.3f)]", dot_vel.x * dot_speed, dot_vel.y * dot_speed);
        
        hf_gui_text(text, 0);
        
        if(debug_enable){
            hf_gui_text(text2, 0);
            hf_gui_text(text3, 0);
            hf_gui_slider(80, 15, hf_v4f(0.9, 0.6, 0, 1), hf_v4f(0.5, 0.5, 0.5, 1), &dot_speed, 0, 5);
        }
        
        if(hf_input_get_key_down(HF_KEY_BACKSLASH)){
            debug_enable = !debug_enable;
        }
        
        
        hf_gui_panel_end(&panel);
        
        
        paddle_l_pos.x = app.window.width / 4.0;
        paddle_r_pos.x = app.window.width / 4.0 * 3.0;
        
        //render paddles
        hf_render_rect(paddle_l_pos.x, paddle_l_pos.y, 10, paddle_l_height, (v4f){1, 1, 1, 1});
        hf_render_rect(paddle_r_pos.x, paddle_r_pos.y, 10, paddle_height, (v4f){1, 1, 1, 1});
        
        if(hf_input_get_key(HF_KEY_DOWN) && paddle_r_pos.y + paddle_height < app.window.height){
            paddle_r_pos.y += paddle_speed * hf_get_delta_time();
        }else if(hf_input_get_key(HF_KEY_UP) && paddle_r_pos.y > 1){
            paddle_r_pos.y -= paddle_speed * hf_get_delta_time();
        }
        
        //dot checks
        if(hf_2d_aabb_intersect(dot_pos.x, dot_pos.y, dot_size, dot_size, paddle_r_pos.x, paddle_r_pos.y, 10, paddle_height) || hf_2d_aabb_intersect(dot_pos.x, dot_pos.y, dot_size, dot_size, paddle_l_pos.x, paddle_l_pos.y, 10, paddle_l_height)){
            collided = 1;
            dot_vel.x = -dot_vel.x;
            
            
            //dot_vel.x *= 1.01f;
            //dot_vel.y *= 1.05f;
        }
        if(dot_pos.y + dot_size >= app.window.height){
            dot_vel.y = -dot_vel.y;
            collided = 1;
        }
        if(dot_pos.y <= 0){
            dot_vel.y = -dot_vel.y;
            collided = 1;
        }
        if(dot_pos.x + dot_size >= app.window.width){
            dot_vel.x = -dot_vel.x;
            collided = 1;
        }
        if(dot_pos.x <= 0){
            dot_vel.x = -dot_vel.x;
            collided = 1;
        }
        
        //someone loses
        if((dot_pos.x + dot_size > (paddle_r_pos.x + 3))){
            dot_pos.x = app.window.width / 2;
            dot_pos.y = app.window.height / 2;
            l_score += 1;
            if(bot_speed > 0.005f){
                bot_speed -= 0.005f;
            }
            
        }else if((dot_pos.x < (paddle_l_pos.x + 7))){
            dot_pos.x = app.window.width / 2;
            dot_pos.y = app.window.height / 2;
            r_score += 1;
            bot_speed += 0.005f;
        }
        
        
        if(dot_vel.x < 0){
            f32 paddle_y = (dot_vel.y / dot_vel.x) * (paddle_l_pos.x - dot_pos.x) + dot_pos.y - paddle_l_height / 2;
            
            
            
            //printf("%.1f\n", paddle_y);
            
            if(paddle_y < 0){
                paddle_y = 0;
            }else if((paddle_y + paddle_l_height) > app.window.height){
                paddle_y = app.window.height - paddle_l_height;
            }
            
            paddle_l_desired = paddle_y;
            //paddle_l_pos.y = paddle_y;
        }
        
        paddle_l_pos.y = hf_lerp(paddle_l_pos.y, paddle_l_desired, bot_speed);
        
        
        
        //render dot
        hf_render_rect(dot_pos.x, dot_pos.y, dot_size, dot_size, (frame_index > 0) ? (v4f){1, 0, 0, 1} : (v4f){0, 1, 0, 1});
        
        
        dot_pos = hf_add_v2f(dot_pos, hf_mul_v2f(dot_vel, (v2f){dot_speed, dot_speed}));
        
        if(collided){
            frame_index = 1;
        }
        
        if(frame_index > 0 && frame_index <= red_frame_amount){
            frame_index += 1;
        }else{
            frame_index = 0;
        }
        
        
        
        
        collided = 0;
        
        hf_limit_fps(300);
    }
    
    
    hf_app_stop(&app);
}