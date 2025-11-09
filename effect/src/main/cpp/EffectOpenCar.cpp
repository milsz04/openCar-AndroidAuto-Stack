//
// Created by milos on 01.11.2025.
//
#include <android/log.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include "opencar_dsp.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "OpenCar", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"OpenCar", __VA_ARGS__)

//Minimal effect interface types
extern "C" {
typedef int32_t (*effect_process_t)(void* self, float* in, float* out, uint32_t frames);
typedef int32_t (*effect_command_t)(void* self, uint32_t cmdCode, uint32_t cmdSize, void* cmdData);
struct effect_interface_s {
    effect_process_t process;
    effect_command_t command;
};
struct effect_handle_s {
    effect_interface_s itf;
    OpenCarDSP dsp;
};
}

// params IDs
enum : uint32_t { PARAM_ENABLE=1, PARAM_LOW=2, PARAM_MID=3, PARAM_HIGH=4, PARAM_LIMIT=5 };

static int32_t proc(void* self, float* in, float* out, uint32_t frames){
    auto* h = reinterpret_cast<effect_handle_s*>(self);

    for(uint32_t i=0;i<frames;i++){
        float L = in[2*i+0];
        float R = in[2*i+1];
        h->dsp.processFrame(L,R);
        out[2*i+0]=L; out[2*i+1]=R;
    }
    return 0;
}
static int32_t cmd(void* self, uint32_t code, uint32_t size, void* data){
    auto* h = reinterpret_cast<effect_handle_s*>(self);
    if(code==PARAM_ENABLE && size==sizeof(uint32_t)){ h->dsp.enabled = *reinterpret_cast<uint32_t*>(data)!=0; }
    else if(code==PARAM_LOW   && size==sizeof(float)){ h->dsp.low = *reinterpret_cast<float*>(data); h->dsp.update(); }
    else if(code==PARAM_MID   && size==sizeof(float)){ h->dsp.mid = *reinterpret_cast<float*>(data); h->dsp.update(); }
    else if(code==PARAM_HIGH  && size==sizeof(float)){ h->dsp.high= *reinterpret_cast<float*>(data); h->dsp.update(); }
    else if(code==PARAM_LIMIT && size==sizeof(uint32_t)){ h->dsp.useLimiter = *reinterpret_cast<uint32_t*>(data)!=0; }
    LOGI("Param %u set", code);
    return 0;
}


extern "C" __attribute__((visibility("default")))
int32_t create_effect(effect_handle_s** handle){
    auto* h = new effect_handle_s();
    h->itf.process = proc;
    h->itf.command = cmd;
    h->dsp.update();
    *handle = h;
    LOGI("create_effect");
    return 0;
}
extern "C" __attribute__((visibility("default")))
int32_t release_effect(effect_handle_s* handle){
    delete handle;
    LOGI("release_effect");
    return 0;
}
