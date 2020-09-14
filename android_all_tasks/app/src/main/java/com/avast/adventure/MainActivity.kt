package com.avast.adventure

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.avast.adventure.ui.main.MainFragment

class MainActivity : AppCompatActivity() {

    companion object {
        const val SOME_FORBIDDEN_THING = "avastCTF{ANDROID_STATIC_MDpWxscdKH6k}"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_activity)
        if (savedInstanceState == null) {
            supportFragmentManager.beginTransaction()
                .replace(R.id.container, MainFragment.newInstance())
                .commitNow()
        }
    }

    external fun stringFromJNI(): String?
}
