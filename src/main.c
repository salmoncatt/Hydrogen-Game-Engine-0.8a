
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include "data_types.h"


//TODO: FINISH THE THEME

#define assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

LRESULT CALLBACK wnd_procedure(HWND, UINT, WPARAM, LPARAM){
    
    
}

int main(void) {
    
    //me like main no winmain here bois
    HINSTANCE instance_handle = GetModuleHandle(NULL);
    
    WNDCLASS wndcl;
    
    
    
    memset(&wndcl, 0, sizeof(wndcl));
    
    wndcl.style = CS_OWNDC;
    wndcl.lpfnWndProc = wnd_procedure;
    wndcl.hInstance = instance_handle;
    wndcl.lpszClassName = TEXT("goober");
    RegisterClass(&wndcl);
    
    
}
