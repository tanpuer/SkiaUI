cmake_minimum_required(VERSION 3.10.2)

project("skiaui")

set(JNI_LIBS_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

include_directories(
        ${JNI_LIBS_DIR}/skia
        ${JNI_LIBS_DIR}/skia/include
        ${JNI_LIBS_DIR}/skia/module
        ${JNI_LIBS_DIR}/skia/skresources
        ${JNI_LIBS_DIR}/skia/svg

        src/main/cpp
        src/main/cpp/base
        src/main/cpp/flexbox
        src/main/cpp/gl
        src/main/cpp/fliter
        src/main/cpp/yoga
        src/main/cpp/yoga/event
        src/main/cpp/yoga/internal
        src/main/cpp/widget
)

link_directories(
        ${JNI_LIBS_DIR}/${ANDROID_ABI}
)

set(LINK_LIB_LIST
        skia
        skshaper
        svg)

aux_source_directory(src/main/cpp srcs)
aux_source_directory(src/main/cpp/base srcs)
aux_source_directory(src/main/cpp/flexbox srcs)
aux_source_directory(src/main/cpp/gl srcs)
aux_source_directory(src/main/cpp/fliter srcs)
aux_source_directory(src/main/cpp/yoga srcs)
aux_source_directory(src/main/cpp/yoga/event srcs)
aux_source_directory(src/main/cpp/yoga/internal srcs)
aux_source_directory(src/main/cpp/widget srcs)

add_library(native-lib SHARED ${srcs})

find_library(log-lib log)
find_library(z-lib z)
find_library(android-lib android)

target_link_libraries(native-lib
        android EGL GLESv3 jnigraphics
        ${LINK_LIB_LIST} ${log-lib} ${z-lib} ${android-lib})