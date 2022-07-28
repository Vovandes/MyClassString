cmake_minimum_required(VERSION 3.15)

project(MyClassString)

add_executable(MyClassString
        "main.cpp"
        "myClassString.hpp"
        )

target_compile_features(MyClassString PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(MyClassString PUBLIC /W4 /WX)
else()
    target_compile_options(MyClassString PUBLIC -Wall -Wextra -Werror -pedantic)
endif()
