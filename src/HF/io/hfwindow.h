/* date = August 15th 2021 8:14 pm */

#ifndef _WINDOW_H
#define _WINDOW_H

// NOTE(salmoncatt): do platform specific functions like foo (calls wfoo or xfoo)

//https://www.cprogramming.com/tutorial/opengl_projections.html the god send of a website

#define WGL_DRAW_TO_WINDOW_ARB         0x2001
#define WGL_ACCELERATION_ARB           0x2003
#define WGL_SWAP_METHOD_ARB            0x2007
#define WGL_SUPPORT_OPENGL_ARB         0x2010
#define WGL_DOUBLE_BUFFER_ARB          0x2011
#define WGL_PIXEL_TYPE_ARB             0x2013
#define WGL_COLOR_BITS_ARB             0x2014
#define WGL_DEPTH_BITS_ARB             0x2022
#define WGL_STENCIL_BITS_ARB           0x2023
#define WGL_FULL_ACCELERATION_ARB      0x2027
#define WGL_SWAP_EXCHANGE_ARB          0x2028
#define WGL_TYPE_RGBA_ARB              0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092
#define GL_ARRAY_BUFFER                0x8892
#define GL_STATIC_DRAW                 0x88E4
#define GL_FRAGMENT_SHADER             0x8B30
#define GL_VERTEX_SHADER               0x8B31
#define GL_COMPILE_STATUS              0x8B81
#define GL_LINK_STATUS                 0x8B82
#define GL_INFO_LOG_LENGTH             0x8B84
#define GL_TEXTURE0                    0x84C0
#define GL_BGRA                        0x80E1
#define GL_ELEMENT_ARRAY_BUFFER        0x8893

// TODO(salmoncatt): get this to not error in console pls
//typedef (*hf_key_callback)(hf_window*, u32, u32);


//https://www.khronos.org/opengl/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib yoink for linux


// TODO(salmoncatt): come up with a better solution for callbacks than (typedef struct hf_def_window_struct)
typedef struct hf_window{
    u32 width;
    u32 height;
    u32 x;
    u32 y;
    u32 bits_per_pixel;
    const char* title;
    b8 vsync;
    
    void* allocated;
    
#ifdef _WIN32
    
    HINSTANCE hInstance;
    HWND hwnd;
    WNDCLASSEX wc;
    MSG msg;
    HDC hdc;
    HGLRC hrc;
    
    
    //WNDCLASSEX
    UINT      cbSize;
    UINT      style;
    WNDPROC   lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HICON     hIcon;
    HCURSOR   hCursor;
    HBRUSH    hbrBackground;
    LPCSTR    lpszMenuName;
    LPCSTR    lpszClassName;
    HICON     hIconSm;
    
    //pixelformatdescriptor
    WORD  nSize;
    WORD  nVersion;
    DWORD dwFlags;
    BYTE  iPixelType;
    BYTE  cColorBits;
    BYTE  cRedBits;
    BYTE  cRedShift;
    BYTE  cGreenBits;
    BYTE  cGreenShift;
    BYTE  cBlueBits;
    BYTE  cBlueShift;
    BYTE  cAlphaBits;
    BYTE  cAlphaShift;
    BYTE  cAccumBits;
    BYTE  cAccumRedBits;
    BYTE  cAccumGreenBits;
    BYTE  cAccumBlueBits;
    BYTE  cAccumAlphaBits;
    BYTE  cDepthBits;
    BYTE  cStencilBits;
    BYTE  cAuxBuffers;
    BYTE  iLayerType;
    BYTE  bReserved;
    DWORD dwLayerMask;
    DWORD dwVisibleMask;
    DWORD dwDamageMask;
#elif defined(__linux__)
    
    Display* display;
    i32 screen;
    Window root;
    Window window;
    i32 attributes[5];
    XVisualInfo* visual_info;
    Colormap color_map;
    XSetWindowAttributes set_win_att;
    GLXContext glc;
    
#endif
    
    
    
    
    
    
    //struct hf_window* test;
    // TODO(salmoncatt): get these callbacks to work
    /* 
        struct{
            hf_key_callback key_callback;
            
        }callbacks;
     */
    
    //void (*key_callback)(struct hf_window*, u32, u32);
    
} hf_window;

//sets default values for a window
void hf_window_defaults(hf_window* window);

b8 hf_create_window(hf_window* window);
b8 hf_gl_load_extenstions();
b8 hf_destroy_window(hf_window* window);

b8 hf_should_window_update(hf_window* window);
void hf_update_window(hf_window* window);

void hf_set_window_title(hf_window* window, const char* title);
void hf_window_set_icon(hf_window* w, i32 icon_id);

//void hf_window_set_ups(hf_window* window, u32 ups);
//void hf_window_remove_ups_constraint(hf_window* window);
#ifdef _WIN32
LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

// NOTE(salmoncatt): input handling and callbacks

// NOTE(salmoncatt):     window handle      [callback function]         [keycode] [key up or down]
//void hf_window_set_key_callback(hf_window* window, void (*hf_key_callback)(hf_window*, u32, u32));

// NOTE(salmoncatt): vsync
void hf_swap_interval(b8 vsync);

void hf_window_set_cursor_pos(hf_window* window, v2f pos);

#endif //_WINDOW_H
