cmake_minimum_required(VERSION 3.20)

# 这里修改为你的项目名称
project(Bank-rtthread)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.3\\mingw_64\\lib\\cmake")

# 这里设置 qt大的版本号
set(QTVersion 6)


# 同时添加你的需要的qt依赖
find_package(Qt${QTVersion}
        COMPONENTS
        Core
        Gui
        Widgets
        Network
        SerialPort
        Sql
        REQUIRED
)


# 包含 ui.h
include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")
#递归查找源文件
file(GLOB   SRCS  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  LIST_DIRECTORIES false   *.cpp  *.ui)
#添加额外的 源文件 例如资源文件等


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/my_ui
                    ${CMAKE_CURRENT_SOURCE_DIR}/Core/inc
                    )
# debug 模式带黑框 release不带
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message("Debug Build")
    add_executable(${PROJECT_NAME}   ${SRCS}
            Core/src/EventBus.cpp
            Core/inc/EventBus.h
            Core/src/crc.cpp
            Core/src/serial_pack.cpp
            Core/inc/crc.h
            Core/inc/serial_pack.h
            my_ui/serialport.h my_ui/serialport.cpp my_ui/serialport.ui
            my_ui/charge.h my_ui/charge.cpp my_ui/charge.ui
            my_ui/card_id.h
            my_ui/card_id.ui
            my_ui/card_id.cpp
    )
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(${PROJECT_NAME}   ${SRCS}
            Core/src/EventBus.cpp
            Core/inc/EventBus.h
            Core/src/crc.cpp
            Core/src/serial_pack.cpp
            Core/inc/crc.h
            Core/inc/serial_pack.h
            my_ui/serialport.h my_ui/serialport.cpp my_ui/serialport.ui
            my_ui/charge.h my_ui/charge.cpp my_ui/charge.ui
            my_ui/card_id.h
            my_ui/card_id.ui
            my_ui/card_id.cpp
    )
endif()


target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::SerialPort
        Qt::Sql
)
