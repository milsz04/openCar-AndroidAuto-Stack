//
// Created by milos on 01.11.2025.
//

#ifndef MYCAR1_EQ_H
#define MYCAR1_EQ_H

#endif //MYCAR1_EQ_H
#pragma once
#include <cmath>
struct Biquad {
    float b0=1,b1=0,b2=0,a1=0,a2=0, z1L=0,z2L=0,z1R=0,z2R=0;
    inline void set(float B0,float B1,float B2,float A1,float A2){ b0=B0;b1=B1;b2=B2;a1=A1;a2=A2; }
    inline void reset(){ z1L=z2L=z1R=z2R=0; }
    inline void process(float& L, float& R){
        float yL = b0*L + z1L; z1L = b1*L - a1*yL + z2L; z2L = b2*L - a2*yL;
        float yR = b0*R + z1R; z1R = b1*R - a1*yR + z2R; z2R = b2*R - a2*yR;
        L=yL; R=yR;
    }
};

inline void shelvingLow(float fs, float f0, float gainDB, float Q, Biquad& bq){
    float A = std::pow(10.f, gainDB/40.f);
    float w0=2.f*3.1415926535f*f0/fs, alpha=std::sin(w0)/(2.f*Q), cosw0=std::cos(w0);
    float b0 =    A*((A+1)-(A-1)*cosw0+2*std::sqrt(A)*alpha);
    float b1 =  2*A*((A-1)-(A+1)*cosw0);
    float b2 =    A*((A+1)-(A-1)*cosw0-2*std::sqrt(A)*alpha);
    float a0 =       (A+1+(A-1)*cosw0+2*std::sqrt(A)*alpha);
    float a1 =   -2*(A-1+(A+1)*cosw0);
    float a2 =       (A+1+(A-1)*cosw0-2*std::sqrt(A)*alpha);
    bq.set(b0/a0,b1/a0,b2/a0,a1/a0,a2/a0);
}
inline void peaking(float fs, float f0, float gainDB, float Q, Biquad& bq){
    float A = std::pow(10.f, gainDB/40.f);
    float w0=2.f*3.1415926535f*f0/fs, alpha=std::sin(w0)/(2.f*Q), cosw0=std::cos(w0);
    float b0 = 1 + alpha*A;
    float b1 = -2*cosw0;
    float b2 = 1 - alpha*A;
    float a0 = 1 + alpha/A;
    float a1 = -2*cosw0;
    float a2 = 1 - alpha/A;
    bq.set(b0/a0,b1/a0,b2/a0,a1/a0,a2/a0);
}
inline void shelvingHigh(float fs, float f0, float gainDB, float Q, Biquad& bq){
    float A = std::pow(10.f, gainDB/40.f);
    float w0=2.f*3.1415926535f*f0/fs, alpha=std::sin(w0)/(2.f*Q), cosw0=std::cos(w0);
    float b0 =    A*((A+1)+(A-1)*cosw0+2*std::sqrt(A)*alpha);
    float b1 = -2*A*((A-1)+(A+1)*cosw0);
    float b2 =    A*((A+1)+(A-1)*cosw0-2*std::sqrt(A)*alpha);
    float a0 =       (A+1-(A-1)*cosw0+2*std::sqrt(A)*alpha);
    float a1 =    2*(A-1-(A+1)*cosw0);
    float a2 =       (A+1-(A-1)*cosw0-2*std::sqrt(A)*alpha);
    bq.set(b0/a0,b1/a0,b2/a0,a1/a0,a2/a0);
}
