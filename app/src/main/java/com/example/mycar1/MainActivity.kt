package com.example.mycar1

import android.media.AudioAttributes
import android.media.MediaPlayer
import android.media.audiofx.AudioEffect
import android.os.Bundle
import android.widget.SeekBar
import android.widget.Switch
import androidx.appcompat.app.AppCompatActivity
import java.nio.ByteBuffer
import java.util.UUID

class MainActivity : AppCompatActivity() {
    private val EFFECT_UUID = UUID.fromString("5e0a0a10-7f2a-4b3a-8b92-11aa22bb33cc")
    private var effect: AudioEffect? = null
    private lateinit var player: MediaPlayer

    private fun packInt(v: Int) = ByteBuffer.allocate(4).putInt(v).array()
    private fun packFloat(f: Float) = ByteBuffer.allocate(4).putFloat(f).array()

    private fun setParam(code: Int, payload: ByteArray) {
        val ef = effect ?: return
        ef.setParameter(ByteBuffer.allocate(4).putInt(code).array(), payload)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // basic type of player
        player = MediaPlayer.create(this, android.provider.Settings.System.DEFAULT_RINGTONE_URI).apply {
            isLooping = true
            setAudioAttributes(
                AudioAttributes.Builder()
                    .setUsage(AudioAttributes.USAGE_MEDIA)
                    .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                    .build()
            )
            start()
        }
        effect = AudioEffect(EFFECT_UUID, AudioEffect.EFFECT_TYPE_NULL, 0, player.audioSessionId).apply {
            enabled = true
        }

        val swEnable = findViewById<Switch>(R.id.switchEnable)
        val swLimiter = findViewById<Switch>(R.id.switchLimiter)
        val low = findViewById<SeekBar>(R.id.seekLow)
        val mid = findViewById<SeekBar>(R.id.seekMid)
        val high = findViewById<SeekBar>(R.id.seekHigh)

        fun sbToDb(sb: SeekBar) = (sb.progress - 120) / 10f  // -12..+12 dB

        swEnable.setOnCheckedChangeListener { _, isChecked ->
            setParam(1, packInt(if (isChecked) 1 else 0))
        }
        swLimiter.setOnCheckedChangeListener { _, isChecked ->
            setParam(5, packInt(if (isChecked) 1 else 0))
        }
        listOf(low to 2, mid to 3, high to 4).forEach { (bar, code) ->
            bar.progress = 120
            bar.setOnSeekBarChangeListener(object: SeekBar.OnSeekBarChangeListener {
                override fun onProgressChanged(sb: SeekBar?, progress: Int, fromUser: Boolean) {
                    setParam(code, packFloat(sbToDb(bar)))
                }
                override fun onStartTrackingTouch(p0: SeekBar?) {}
                override fun onStopTrackingTouch(p0: SeekBar?) {}
            })
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        effect?.release()
        player.release()
    }
}

private fun AudioEffect.setParameter(array: ByteArray, payload: ByteArray) {}
