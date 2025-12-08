cmake_minimum_required(VERSION 3.10)
project(Proj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_PATH $HOME/学习平台/lib) # 自行更改

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE STATICLIBS "lib/*/*.a")
file(GLOB_RECURSE SOLIBS "lib/*/*.so")
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

set(EXECUTABLE_OUTPUT_PATH ../target/)
add_executable(markdowntool ${SRC_FILES})

target_include_directories(markdowntool PRIVATE include)

target_link_libraries(markdowntool
    ${wxWidgets_LIBRARIES}
    ${STATICLIBS}
    ${SOLIBS}
)

# GLib GObject
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0 gobject-2.0)
target_compile_options(markdowntool PRIVATE ${GLIB_CFLAGS})
target_link_libraries(markdowntool ${GLIB_LIBRARIES})

# libsigc++
find_package(PkgConfig REQUIRED)
pkg_check_modules(SIGCXX REQUIRED sigc++-3.0)
target_include_directories(markdowntool PRIVATE ${SIGCXX_INCLUDE_DIRS})
target_link_directories(markdowntool PRIVATE ${SIGCXX_LIBRARY_DIRS})
target_link_libraries(markdowntool ${SIGCXX_LIBRARIES})

# sqlite3 
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(SQLITE3 REQUIRED sqlite3)
# target_include_directories(markdowntool PRIVATE ${SQLITE3_INCLUDE_DIRS})
# target_link_directories(markdowntool PRIVATE ${SQLITE3_LIBRARY_DIRS})
# target_link_libraries(markdowntool ${SQLITE3_LIBRARIES})

# hunter-hongg/clog
target_include_directories(markdowntool PRIVATE $ENV{HOME}/clog/include)
target_link_directories(markdowntool PRIVATE $ENV{HOME}/clog/lib/)
target_link_libraries(markdowntool libCLogger.so)

target_compile_options(markdowntool PRIVATE -w)

# MarkdownTool系列库
target_include_directories(markdowntool PRIVATE 
    $ENV{HOME}/MarkdownTool/MarkdownParser/include 
    $ENV{HOME}/MarkdownTool/MarkdownSQLite/include 
    $ENV{HOME}/MarkdownTool/MarkdownFile/include 
)
target_link_directories(markdowntool PRIVATE 
    $ENV{HOME}/MarkdownTool/MarkdownParser/lib
    $ENV{HOME}/MarkdownTool/MarkdownSQLite/lib
)
target_link_libraries(markdowntool 
    libMdSQLite.a 
    libMdParser.a 
)

target_link_options(markdowntool PRIVATE -lsqlite3)

# 查找 SQLite3 库
find_package(SQLite3 REQUIRED)

# 链接到你的可执行文件
target_link_libraries(markdowntool SQLite::SQLite3)

