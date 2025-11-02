package com.example.effect

class NativeLib {

    /**
     * A native method that is implemented by the 'effect' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'effect' library on application startup.
        init {
            System.loadLibrary("effect")
        }
    }
}