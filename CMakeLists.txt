cmake_minimum_required(VERSION 3.1.0)

project(orwell)

find_library(AVCODEC_LIBRARY avcodec)
find_library(AVUTIL_LIBRARY avutil)
find_library(SWSCALE_LIBRARY swscale)


set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOUIC ON) # Create code from a list of Qt designer ui files

find_package(OpenGL REQUIRED)
find_package(Boost COMPONENTS thread system REQUIRED)
find_package(Qt5 COMPONENTS Qml Quick Gui Widgets Multimedia MultimediaWidgets) #OpenGLWidgets) 

add_subdirectory(myRtspClient)
include_directories(myRtspClient/myRtspClient/include)
#this is ugly but what can I do? :( I need to include reactitem.h and I will not download just it to put here
include_directories(orwellJS/node_modules/react-native/ReactQt/runtime/src)

#qt5_add_resources(QRCS resources.qrc) #what this does?
#qt5_add_resources(qml_QRC qml.qrc)    #what this does?

file(GLOB orwell_SRCS "*.cpp" "*.ui")

add_library(orwell SHARED ${orwell_SRCS})

#TODO: decide either qtquick or qt widgets libs
target_link_libraries( orwell PRIVATE ${AVCODEC_LIBRARY} ${AVUTIL_LIBRARY} ${SWSCALE_LIBRARY} Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Boost::thread myRtspClient pthread Qt5::Qml Qt5::Quick)
