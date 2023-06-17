//#include "hfwindow.h"
#include "hfwindow_linux.h"

#ifdef __linux__
//http://mech.math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html

















/* 
b8 hf_gl_load_extenstions(){
    
}
 */

b8 _hf_linux_create_window(hf_window* w){
    printf("[HF] creating window: [%s]\n", w->title);
    
    //printf("test\n");
    w->display = XOpenDisplay(NULL);
    w->root = DefaultRootWindow(w->display);
    
    w->visual_info = glXChooseVisual(w->display, 0, w->attributes);
    w->color_map = XCreateColormap(w->display, w->root, w->visual_info->visual, AllocNone);
    w->set_win_att.colormap = w->color_map;
    w->set_win_att.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask;
    
    w->window = XCreateWindow(w->display, w->root, w->x, w->y, w->width, w->height, 0, w->visual_info->depth, InputOutput, w->visual_info->visual, CWColormap | CWEventMask | CWCursor, &w->set_win_att);
    XSelectInput(w->display, w->window, ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask) ;
    XMapWindow(w->display, w->window);
    XStoreName(w->display, w->window, w->title);
    
    w->glc = glXCreateContext(w->display, w->visual_info, NULL, GL_TRUE);
    glXMakeCurrent(w->display, w->window, w->glc);
    glEnable(GL_DEPTH_TEST);
    
    w->keyboard_descriptor = XkbGetMap(w->display, 0, XkbUseCoreKbd);
    XkbGetNames(w->display, XkbKeyNamesMask, w->keyboard_descriptor);
    
    
    
    
    //hf_swap_interval(w, 0);
    
    printf("[HF] created window: [%s], size: [%u, %u], pos: [%u, %u]\n\n", w->title, w->width, w->height, w->x, w->y);
    
    return 1;
}

b8 _hf_linux_destroy_window(hf_window* w){
    printf("[HF] destorying window: [%s]\n", w->title);
    glXMakeCurrent(w->display, None, NULL);
    glXDestroyContext(w->display, w->glc);
    XDestroyWindow(w->display, w->window);
    XCloseDisplay(w->display);
    //printf("test\n");
    
    printf("[HF] destroyed window: [%s]\n", w->title);
    return 1;
}

void _hf_linux_window_defaults(hf_window* window){
    window->width = 1000;
    window->height = 600;
    window->x = 300;
    window->y = 200;
    window->bits_per_pixel = 32;
    window->title = "HF window";
    window->vsync = 1;
    
    window->attributes[0] = GLX_RGBA;
    window->attributes[1] = GLX_DEPTH_SIZE;
    window->attributes[2] = 24;
    window->attributes[3] = GLX_DOUBLEBUFFER;
    window->attributes[4] = None;
}

void _hf_linux_window_set_icon(hf_window* w, i32 icon_id){
    
}

b8 _hf_linux_should_window_update(hf_window* w){
    //XNextEvent(w->display, &w->xev);
    
    while(XPending(w->display) > 0){
        XNextEvent(w->display, &w->xev);
        
        KeySym key;
        
        switch(w->xev.type){
            
            
            
            case Expose:{
                XGetWindowAttributes(w->display, w->window, &w->gwa);
                
            }
            break;
            
            case ButtonPress:
            hf_input_buttons[w->xev.xbutton.button] = 1;
            break;
            case ButtonRelease:
            hf_input_buttons[w->xev.xbutton.button] = 0;
            break;
            
            /* 
                        case MotionNotify:{
                            XDeviceMotionEvent *m = (XDeviceMotionEvent *)&w->xev;
                            
                            hf_input_cursor_pos.x = (f32)m->axis_data[0];
                            hf_input_cursor_pos.y = (f32)m->axis_data[1];
                            
                            //hf_input_cursor_pos.x = (f32)((XMotionEvent)w->xev).x;
                            //hf_input_cursor_pos.y = (f32)((XMotionEvent)w->xev).y;
                            
                            //printf("[%f %f]\n", hf_input_cursor_pos.x, hf_input_cursor_pos.y);
                            
                                            if(hf_input_cursor_pos.x < 0)
                                                hf_input_cursor_pos.x = 0;
                                            if(hf_input_cursor_pos.y < 0)
                                                hf_input_cursor_pos.y = 0;
                             
                        }
             */
            
            case KeyPress: {
                key = XLookupKeysym(&w->xev.xkey, 0);
                hf_input_keys[key] = 1;
                
            }
            //hf_input_keys[w->xev.xkey.keycode] = 1;
            
            
            /* 
                    if(key == XK_backslash){
                        printf("backslash pressed\n");
                        //hf_renderer_toggle_wireframe();
                    }
             */
            
            break;
            case KeyRelease:{
                key = XLookupKeysym(&w->xev.xkey, 0);
                hf_input_keys[key] = 0;
                
            }
            //hf_input_keys[w->xev.xkey.keycode] = 0;
            
            
            /* 
                    if(key == XK_backslash){
                        printf("backslash pressed\n");
                        //hf_renderer_toggle_wireframe();
                    }
             */
            
            break;
            /* 
                        case ClientMessage:
                        if (w->xev.xclient.data.l[0] == atomWmDeleteWindow) {
                            return 0;
                        }
                        break;
             */
            case DestroyNotify:
            return 0;
            break;
            
            /* 
                        case MotionNotify:
                        //omx = mx;
                        //omy = my;
                        break;
             */
            
            /* 
                        default:
                        XGetWindowAttributes(w->display, w->window, &w->gwa);
                        glViewport(0, 0, w->gwa.width, w->gwa.height);
                        glXSwapBuffers(w->display, w->window);
                        break;
             */
            
        }
    }
    
    /* 
        if(w->xev.type == Expose){
            XGetWindowAttributes(w->display, w->window, &w->gwa);
            glViewport(0, 0, w->gwa.width, w->gwa.height);
            glXSwapBuffers(w->display, w->window);
        }
     */
    
    hf_update_window(w);
    return 1;
}

void _hf_linux_update_window(hf_window* w){
    
    //glViewport(0, 0, w->gwa.width, w->gwa.height);
    w->width = w->gwa.width;
    w->height = w->gwa.height;
    glXSwapBuffers(w->display, w->window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    i32 x = 0, y = 0;
    
    
    Window r, c;
    i32 rx, ry;
    u32 m;
    XQueryPointer(w->display, w->window, &r, &c, &rx, &ry, &x, &y, &m);
    
    hf_input_cursor_pos.x = x;
    hf_input_cursor_pos.y = y;
    
    //printf("[%f %f]\n", hf_input_cursor_pos.x, hf_input_cursor_pos.y);
    
    
    
    
    
    
    // NOTE(salmoncatt): i dont understand how but i managed to ooga booga this shit into working with so little code
    
    hf_input_center = hf_v2f(w->width / 2, w->height / 2);
    hf_input_cursor_movement = hf_sub_v2f(hf_input_cursor_pos, hf_input_cursor_pos_last);
    
    if(hf_input_cursor_visibility){
        hf_input_cursor_pos_last = hf_input_cursor_pos;
    }else{
        v2f input_movement = hf_v2f(hf_abs(hf_input_cursor_movement.x), hf_abs(hf_input_cursor_movement.y));
        
        if(input_movement.x > 0 || input_movement.y > 0){
            hf_window_set_cursor_pos(w, hf_input_center);
            //POINT point;
            //GetCursorPos(&point);
            
            hf_input_cursor_pos_last = hf_input_center;
        }
        
    }
    
    hf_input_cursor_visibility_last = hf_input_cursor_visibility;
    
    
    
    
    //printf("test\n");
}

void _hf_linux_set_window_title(hf_window* w, const char* title){
    XStoreName(w->display, w->window, title);
}

void _hf_linux_swap_interval(hf_window* w, b8 vsync){ 
    glXSwapIntervalEXT(w->display, w->window, vsync);
}

void _hf_linux_window_set_cursor_pos(hf_window* w, v2f pos){
    XWarpPointer(w->display, None, w->window, 0, 0, 0, 0, pos.x, pos.y);
}


#endif

