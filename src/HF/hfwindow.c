#include "hfwindow.h"


void create_window(hf_window* w){
    // NOTE(salmoncatt): in case not using winmain
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    // NOTE(salmoncatt): set windows parameters
    w->wc.cbSize = sizeof(WNDCLASSEX);
    w->wc.style = 0;
    w->wc.lpfnWndProc = WndProc;
    w->wc.cbClsExtra = 0;
    w->wc.cbWndExtra = 0;
    w->wc.hInstance = hInstance;
    w->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    w->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    w->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    w->wc.lpszMenuName = NULL;
    w->wc.lpszClassName = w->title;
    w->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if(!RegisterClassEx(&w->wc)){
        printf("couldn't register window: %s");
        MessageBox(NULL, "couldn't register window", "error", MB_ICONERROR | MB_OK);
    }
}