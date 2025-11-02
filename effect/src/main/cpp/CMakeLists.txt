# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22)
project(opencar_effect CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(effect_opencar SHARED
        EffectOpenCar.cpp
        opencar_dsp.h
        eq.h
        limiter.h
)
set_target_properties(effect_opencar PROPERTIES OUTPUT_NAME "effect_opencar")

find_library(log-lib log)
target_link_libraries(effect_opencar ${log-lib})
