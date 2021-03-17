cmake_minimum_required(VERSION 3.17)


#设定vckpg �?�?
#SET(CMAKE_TOOLCHAIN_FILE, /to/your/vcpkgpath)


project(ctp_demo)


#设定CPP版本
set(CMAKE_CXX_STANDARD 11)


add_compile_options(-DENVSIMNOW)


include_directories(include)

link_directories(lib)


#�?描src�?�?, 获取.c .cpp 源码文件列表
file(GLOB_RECURSE DIR_SRCS ./src/*.cpp  ./src/*.c ./src/*/*.cpp)
file(GLOB_RECURSE TEST_SRCS ./test/test_order_insert.cpp ./src/ctp/*.cpp)
file(GLOB_RECURSE TEST_SRCS1 ./test/test_md_sub.cpp ./src/ctp/*.cpp)
file(GLOB_RECURSE TEST_SRCS2 ./test/test_order_time_record.cpp ./src/ctp/*.cpp)
file(GLOB_RECURSE TEST_SRCS3 ./test/test_base_qry.cpp ./src/ctp/*.cpp)


# �?执�?�文件输出目�?
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/runtime)


#使用源码列表生成�?执�?�文�?
ADD_EXECUTABLE(ctpdemo ${DIR_SRCS})
ADD_EXECUTABLE(orderinserttest ${TEST_SRCS})
ADD_EXECUTABLE(ctp_md_sub_test ${TEST_SRCS1})
ADD_EXECUTABLE(ctp_order_time_record_test ${TEST_SRCS2})
ADD_EXECUTABLE(ctp_base_qry_test ${TEST_SRCS3})


target_link_libraries(ctpdemo thostmduserapi_se thosttraderapi_se pthread)
target_link_libraries(orderinserttest thosttraderapi_se thostmduserapi_se gtest pthread)
target_link_libraries(ctp_md_sub_test thosttraderapi_se thostmduserapi_se gtest pthread)
target_link_libraries(ctp_order_time_record_test thosttraderapi_se thostmduserapi_se gtest pthread)
target_link_libraries(ctp_base_qry_test thosttraderapi_se thostmduserapi_se gtest pthread)