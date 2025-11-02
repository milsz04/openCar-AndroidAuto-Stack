//
// Created by milos on 01.11.2025.
//

#ifndef MYCAR1_OPENCAR_DSP_H
#define MYCAR1_OPENCAR_DSP_H
#pragma once
#include "eq.h"
#include "limiter.h"
struct OpenCarDSP {
    float fs=48000.f;
    float low=0, mid=0, high=0; // dB
    bool enabled=true, useLimiter=true;
    Biquad bqL, bqM, bqH;
    void update(){
        shelvingLow(fs, 120.f, low, 0.7f, bqL);
        peaking    (fs,1000.f, mid, 1.0f, bqM);
        shelvingHigh(fs,8000.f, high, 0.7f, bqH);
    }
    void reset(){ bqL.reset(); bqM.reset(); bqH.reset(); }
    inline void processFrame(float& L, float& R){
        if(!enabled){ if(useLimiter) softclipStereo(L,R); return; }
        bqL.process(L,R); bqM.process(L,R); bqH.process(L,R);
        if(useLimiter) softclipStereo(L,R);
    }
};

#endif //MYCAR1_OPENCAR_DSP_H
