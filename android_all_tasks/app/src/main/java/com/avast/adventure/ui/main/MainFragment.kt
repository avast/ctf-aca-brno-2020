package com.avast.adventure.ui.main

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.WindowManager
import android.widget.TextView
import androidx.core.view.isVisible
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import com.avast.adventure.MainActivity
import com.avast.adventure.R
import com.gjiazhe.panoramaimageview.GyroscopeObserver
import com.gjiazhe.panoramaimageview.PanoramaImageView

class MainFragment : Fragment() {

    companion object {
        fun newInstance() = MainFragment()
    }

    private lateinit var viewModel: MainViewModel
    private lateinit var vFeature: TextView
    private lateinit var vBackground: PanoramaImageView
    private lateinit var gyroscopeObserver: GyroscopeObserver

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        activity?.window?.decorView?.systemUiVisibility = (View.SYSTEM_UI_FLAG_LAYOUT_STABLE or View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN)
        activity?.window?.setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS)

        gyroscopeObserver = GyroscopeObserver()
        gyroscopeObserver.setMaxRotateRadian(Math.PI / 3);
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        return inflater.inflate(R.layout.main_fragment, container, false).also {
            vFeature = it.findViewById(R.id.feature)
            vBackground = it.findViewById(R.id.panorama_background)
        }
    }

    override fun onActivityCreated(savedInstanceState: Bundle?) {
        super.onActivityCreated(savedInstanceState)
        viewModel = ViewModelProvider(this).get(MainViewModel::class.java)

        vBackground.setGyroscopeObserver(gyroscopeObserver)

        if (shouldShowFeature()) {
            vFeature.isVisible = true
            vFeature.text = (activity as? MainActivity)?.stringFromJNI()
        }
    }

    override fun onResume() {
        super.onResume()
        gyroscopeObserver.register(context)
    }

    override fun onPause() {
        super.onPause()
        gyroscopeObserver.unregister()
    }

    private fun shouldShowFeature(): Boolean {
        return false
    }
}
