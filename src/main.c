
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include "data_types.h"


//TODO: FINISH THE THEME

#define assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

const char classname[] = "gooberClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
        PostQuitMessage(0);
        break;
        default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main(void){
    
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;
    
    
    //me like main no winmain here bois
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = classname;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if(!RegisterClassEx(&wc)){
        printf("couldn't register window\n");
        MessageBox(NULL, "couldn't register window", "error", MB_ICONERROR | MB_OK);
    }
    
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, classname, "goober", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hInstance, NULL);
    if(hwnd == NULL){
        printf("couldn't create  window\n");
        MessageBox(NULL, "couldn't create  window", "error", MB_ICONERROR | MB_OK);
    }
    
    ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);
    
    while(GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
