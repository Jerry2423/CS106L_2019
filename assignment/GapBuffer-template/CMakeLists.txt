cmake_minimum_required (VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")
project(app)


#add multiple files to the executable target
#group files in src together, when add_executable(), even without #include or definition in bogglegui.cpp, bollgegui.cpp can still find definition for the function defined in bogglesearch.cpp!
file(GLOB app_SOURCES "/*.cpp" "/*.h")
# find the qt cmake path in qt directory
set(CMAKE_PREFIX_PATH /Users/bryant/Qt/6.4.1/macos/lib/cmake/)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Test)

qt_add_executable(app ${app_SOURCES})

target_link_libraries(app PRIVATE Qt6::Widgets)
target_link_libraries(app PRIVATE Qt6::Test)


# add stuff from res to target build directory
add_custom_command(TARGET app POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:app>)

