This project demonstrates a simple in-car audio processing pipeline built for Android Automotive OS (AAOS) and standard Android devices.
It implements a 3-band parametric equalizer and soft-clip limiter in modern C++, exposed as a native AudioEffect library (libeffect_opencar.so) controllable from a Kotlin UI.
The goal is to replicate a small part of a vehicle infotainment audio stack — giving hands-on experience with embedded DSP, Android NDK, and system integration.
Features:
-  Low shelf (120 Hz), Peaking (1 kHz), High shelf (8 kHz), ±12 dB range
-  Soft-clip limiter
-  Prevents digital clipping during EQ boost
-  Android AudioEffect plug-in
-  Built with CMake + NDK, registered via audio_effects.xml
-  Kotlin controller app
-  Simple UI with sliders & switches to control bands and limiter in real time
-  Real-time safe DSP core
-  Fixed-memory processing loop (no mallocs or locks)
-  Emulator-ready
-  Tested on Android 13–14 (x86_64 Google APIs images)
