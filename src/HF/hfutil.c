#include "hfutil.h"
#include <stdio.h>
#include "math/hfmath.h"
#include <windows.h>

void print_windows_last_error(){
    
    DWORD errorID = GetLastError();
    if(!errorID){
        printf("[ERROR] windows error returned with 0");
        return;
    }
    
    LPSTR messageBuffer = NULL;
    
    u64 size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    char message[size];
    strcpy(message, messageBuffer);
    
    // TODO(salmoncatt): make output something cooler than windows error
    printf("[ERROR] windows error returned with: [ID]: %lu [MESSAGE]: %s", errorID, message);
    
    LocalFree(message);
    free(message);
}