cmake_minimum_required(VERSION 3.10)
project(DataManager)  

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp          
    src/data_manager.cpp  
)

target_include_directories(${PROJECT_NAME} PRIVATE include)