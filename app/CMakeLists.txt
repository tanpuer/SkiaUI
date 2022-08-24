cmake_minimum_required(VERSION 3.22.1)

project("skiaui")

set(JNI_LIBS_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

include_directories(
        ${JNI_LIBS_DIR}/skia
        ${JNI_LIBS_DIR}/skia/include
        ${JNI_LIBS_DIR}/skia/modules

        src/main/cpp
        src/main/cpp/base
        src/main/cpp/gl
        src/main/cpp/fliter
        src/main/cpp/yoga
        src/main/cpp/yoga/event
        src/main/cpp/yoga/internal
        src/main/cpp/widget
        src/main/cpp/test
        src/main/cpp/scroll
        src/main/cpp/touch
        src/main/cpp/anim
)

link_directories(
        ${JNI_LIBS_DIR}/${ANDROID_ABI}
)

set(LINK_LIB_LIST
        freetype2
        harfbuzz
        icu
        skcms
        skia
        skparagraph
        skresources
        skshaper
        skunicode
        svg
        )

aux_source_directory(src/main/cpp srcs)
aux_source_directory(src/main/cpp/base srcs)
aux_source_directory(src/main/cpp/gl srcs)
aux_source_directory(src/main/cpp/fliter srcs)
aux_source_directory(src/main/cpp/yoga srcs)
aux_source_directory(src/main/cpp/yoga/event srcs)
aux_source_directory(src/main/cpp/yoga/internal srcs)
aux_source_directory(src/main/cpp/widget srcs)
aux_source_directory(src/main/cpp/test srcs)
aux_source_directory(src/main/cpp/scroll srcs)
aux_source_directory(src/main/cpp/touch srcs)
aux_source_directory(src/main/cpp/anim srcs)

add_library(native-lib SHARED ${srcs})

find_library(log-lib log)
find_library(z-lib z)
find_library(android-lib android)

target_link_libraries(native-lib
        android EGL GLESv3 jnigraphics
        ${LINK_LIB_LIST} ${log-lib} ${z-lib} ${android-lib})