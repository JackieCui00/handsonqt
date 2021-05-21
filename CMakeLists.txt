cmake_minimum_required(VERSION 3.8.2)

project(hands_on_qt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql Charts)

add_executable(login main.cpp mainwindow.cpp mainwindow.ui resources.qrc)
target_link_libraries(login Qt5::Widgets Qt5::Core Qt5::Sql Qt5::Charts)

add_executable(learn_charts ./learn_charts/main.cpp ./learn_charts/window.cpp ./learn_charts/learn_charts.ui)
target_link_libraries(learn_charts Qt5::Widgets Qt5::Core Qt5::Sql Qt5::Charts)

add_executable(learn_view ./learn_view/main.cpp ./learn_view/window.cpp ./learn_view/learn_view.ui)
target_link_libraries(learn_view Qt5::Widgets Qt5::Core Qt5::Sql)

add_executable(image_viewer ./image_viewer/main.cpp ./image_viewer/mainwindow.cpp ./image_viewer/image_viewer.ui)
target_link_libraries(image_viewer Qt5::Widgets Qt5::Core)
