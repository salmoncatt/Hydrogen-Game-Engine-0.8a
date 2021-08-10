
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>


#define FG_RED      31
#define FG_GREEN    32
#define FG_BLUE     34
#define FG_DEFAULT  39
#define BG_RED      41
#define BG_GREEN    42
#define BG_BLUE     44
#define BG_DEFAULT  49

//TODO: f32, b8, etc..


#define assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

/*#define static_assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define static_assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }*/



int main(void) {
    
    //HDC hdc;
    
    //HGLRC hglrc = wglCreateContext(hdc);
    
    int a = 1;
    assertf(a == 2, "goober");
    
    //printf("\033[%im goober  \n \n", FG_RED);
    
    //initTerminal();
    //SetConsoleTitle("Mini Desktop App"); 
    
    
    /*if (!glfwInit())
        printf("glfw could not be created \n");
    else
        printf("glfw was created \n");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(400, 600, "goober", NULL, NULL);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Glad could not be initialized");
    }    
    
    if (!window)
        printf("could not create window \n");
    else
        printf("created window \n");
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwShowWindow(window);
    
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();*/
    
    //system("pause>nul");
}
