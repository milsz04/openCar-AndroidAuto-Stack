//
// Created by milos on 01.11.2025.
//

#ifndef MYCAR1_LIMITER_H
#define MYCAR1_LIMITER_H
#pragma once

#include <__clang_cuda_math_forward_declares.h>

inline float softclip(float x){
    float ax = std::fabs(x);
    return x / (1.f + ax); // simple, stable soft clip
}
inline void softclipStereo(float& L, float& R){
    L = softclip(L); R = softclip(R);
}

#endif //MYCAR1_LIMITER_H
