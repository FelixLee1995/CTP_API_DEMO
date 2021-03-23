/**
*  File: coredump.h
*  Desc: 设置系统产生coredump文件大小
*  Created by felix on 2020/09/01
*/
#ifndef JUPITER_COREDUMP_H
#define JUPITER_COREDUMP_H


#ifdef linux
#include <sys/resource.h>
#endif
#include <iostream>


namespace jupiter{
#define CORE_SIZE 1024 * 1024 * 10000

    int SetCoredump(){

#ifdef linux
        struct rlimit rlmt;
    if (getrlimit(RLIMIT_CORE, &rlmt) == -1) {
        return -1;
    }

    rlmt.rlim_cur = (rlim_t) CORE_SIZE;
    rlmt.rlim_max = (rlim_t) CORE_SIZE;

    if (setrlimit(RLIMIT_CORE, &rlmt) == -1) {
        printf("setrlimit fail!\n");
        return -1;
    } else {
        printf("setrlimit success!\n");
    }
#endif
        return 0;
    }
}

#endif //JUPITER_COREDUMP_H