set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_TYPE_NAMES ${REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_TYPE_NAMES}
                                                     \"MediaPlayerManager\" PARENT_SCOPE)

set(REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_SRC ${REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_SRC}
                                              ${CMAKE_CURRENT_SOURCE_DIR}/mediaplayermanager.cpp
                                              PARENT_SCOPE)

set(ORWELL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)
set(REACT_QT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../node_modules/react-native/ReactQt/runtime/src)

add_subdirectory(${ORWELL_DIR} orwell_subdir)

set(REACT_NATIVE_DESKTOP_EXTERNAL_PROJECT_DEPS ${REACT_NATIVE_DESKTOP_EXTERNAL_PROJECT_DEPS}
                                              orwell
                                              PARENT_SCOPE)

#find_package(Boost COMPONENTS thread system REQUIRED)
#TODO: use find_package instead of passing the l name

set(REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_LIBS ${REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_LIBS}
                                              orwell boost_thread boost_system
                                              PARENT_SCOPE)

set(REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_INCLUDE_DIRS ${REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_INCLUDE_DIRS}
                                              ${ORWELL_DIR}
                                              ${ORWELL_DIR}/myRtspClient/myRtspClient/include
                                              ${ORWELL_DIR}/myRtspClient/
                                              ${ORWELL_DIR}/jrtplib
                                              ${REACT_QT_DIR}
                                              PARENT_SCOPE)


include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)