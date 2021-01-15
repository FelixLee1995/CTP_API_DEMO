cmake_minimum_required(VERSION 3.17)


#设定vckpg 路径
#SET(CMAKE_TOOLCHAIN_FILE, /to/your/vcpkgpath)


project(ctp_demo)


#设定CPP版本
set(CMAKE_CXX_STANDARD 11)


add_compile_options(-DENVSIMNOW)


include_directories(include)

link_directories(lib)


#扫描src目录, 获取.c .cpp 源码文件列表
file(GLOB_RECURSE DIR_SRCS ./src/*.cpp  ./src/*.c ./src/*/*.cpp)

file(GLOB_RECURSE TEST_SRCS ./test/*.cpp  ./test/*.c ./test/*/*.cpp  ./src/ctp/*.cpp)

# 可执行文件输出目录
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/runtime)


#使用源码列表生成可执行文件
ADD_EXECUTABLE(ctpdemo ${DIR_SRCS})
ADD_EXECUTABLE(ctptest ${TEST_SRCS})


target_link_libraries(ctpdemo thostmduserapi_se thosttraderapi_se)

target_link_libraries(ctptest thostmduserapi_se thosttraderapi_se gtest pthread)





