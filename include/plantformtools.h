/*
*    用于跨平台的工具
**/


#pragma once

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #pragma comment(lib,"ws2_32.lib")
#endif 


#if defined(__linux__)
    #include <unistd.h>
    #include <arpa/inet.h>
#endif 

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
    #define CommonSleep(mills)  Sleep(mills);
#endif

#if defined(__linux__)
    #define CommonSleep(mills)  usleep(mills*1000);
#endif
