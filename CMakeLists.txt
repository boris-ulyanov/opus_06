cmake_minimum_required(VERSION 3.8)


if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(PROJECT_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(PROJECT_BUILD_NUMBER "45")
endif()

project(matrix VERSION 1.2.${PROJECT_BUILD_NUMBER})

# global
# set_property() - not work
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-Wpedantic;-Wall;-Wextra")

# sanitaizers
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")


# lib
add_subdirectory("./toolbox")


# app
add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(${PROJECT_NAME}
    toolbox
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)


# tests
option(ENABLE_TESTS "Enable tests" ON)
if (${ENABLE_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()


# packing
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT xyz@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
