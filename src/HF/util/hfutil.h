/* date = August 16th 2021 0:46 pm */

#ifndef HFUTIL_H
#define HFUTIL_H


// NOTE(salmoncatt): assert functions

#define assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

// TODO(salmoncatt): add static asserts pls






// NOTE(salmoncatt): windows get last error
void printWindowsLastError();

#endif //HFUTIL_H
