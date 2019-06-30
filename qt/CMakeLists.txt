cmake_minimum_required(VERSION 3.1.0)

project(orwell)

find_library(AVCODEC_LIBRARY avcodec)
find_library(AVUTIL_LIBRARY avutil)
find_library(SWSCALE_LIBRARY swscale)


set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOUIC ON) # Create code from a list of Qt designer ui files

find_package(OpenGL REQUIRED)
find_package(Boost COMPONENTS thread system REQUIRED) #todo: erase system, not necessary I guess
find_package(Qt5 COMPONENTS Qml Quick Gui Widgets Multimedia MultimediaWidgets) #OpenGLWidgets) 

set(REACT_NATIVE_REACTQT_DIR "../react-native-desktop/ReactQt/runtime/src/") 
add_subdirectory(../myRtspClient myrtsp)
include_directories(../myRtspClient/myRtspClient/include)
include_directories(..)
include_directories(${REACT_NATIVE_REACTQT_DIR})
include_directories(${REACT_NATIVE_REACTQT_DIR}/layout)

#qt5_add_resources(QRCS resources.qrc) #what this does?
qt5_add_resources(qml_QRC qml.qrc)    #what this does?

add_subdirectory(../react-native-desktop RND)

file(GLOB orwell_SRCS "../*.cpp" main.cpp "*../.ui")

add_executable(orwell ${orwell_SRCS} ${QRCS} ${qml_QRC})
add_dependencies(orwell react-native)
#TODO: decide either qtquick or qt widgets libs
target_link_libraries( orwell PRIVATE ${AVCODEC_LIBRARY} ${AVUTIL_LIBRARY} ${SWSCALE_LIBRARY} 
		       Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Boost::thread Qt5::Qml Qt5::Quick 
		       myRtspClient pthread react-native)

#RUN WITH:
#/home/lz/cmake-3.14.0-rc2-Linux-x86_64/bin/cmake -DCMAKE_PREFIX_PATH=/home/lz/Qt5.11.2/5.11.2/gcc_64 -DCMAKE_BUILD_TYPE=Debug .
