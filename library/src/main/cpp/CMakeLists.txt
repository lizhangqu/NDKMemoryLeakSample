project(Test)
cmake_minimum_required (VERSION 3.6)

include_directories(
  ${PROJECT_SOURCE_DIR}/include/
  ${PROJECT_SOURCE_DIR}/../../../../thirdparty/LeakTracer/libleaktracer/include/
  )


set(LEAKTRACER_SOURCES
  ${PROJECT_SOURCE_DIR}/../../../../thirdparty/LeakTracer/libleaktracer/src/AllocationHandlers.cpp
  #${PROJECT_SOURCE_DIR}/../../../../thirdparty/LeakTracer/libleaktracer/src/LeakTracerC.c
  ${PROJECT_SOURCE_DIR}/../../../../thirdparty/LeakTracer/libleaktracer/src/MemoryTrace.cpp
  )

add_library(leaktracer STATIC ${LEAKTRACER_SOURCES})

set(TEST_FILES
    ${CMAKE_SOURCE_DIR}/native.cpp
)
add_library(
    test-jni
    SHARED
    ${TEST_FILES})

target_link_libraries(
   test-jni
   leaktracer
   log
)
