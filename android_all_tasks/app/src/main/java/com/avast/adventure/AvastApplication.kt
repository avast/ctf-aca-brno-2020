package com.avast.adventure

import android.annotation.SuppressLint
import android.app.Application
import android.content.Context
import com.avast.adventure.util.CryptoUtil
import com.avast.adventure.util.SL
import com.avast.adventure.util.slSharedPrefs
import javax.crypto.spec.IvParameterSpec

class AvastApplication : Application() {
    companion object {
        @SuppressLint("StaticFieldLeak")
        var context: Context? = null

        const val CIPHER_AES = "AES/CBC/PKCS7Padding"
    }

    private var cipherText: ByteArray? = null
    private var iv: ByteArray? = null

    init {
        System.loadLibrary("native-lib");
    }

    override fun onCreate() {
        super.onCreate()
        context = this

        initServiceLocator()

        initCrypto()
        checkUpdate()
    }

    /** Initializes {@link SL} class. */
    private fun initServiceLocator() {
        SL.init(applicationContext)
    }

    private fun checkUpdate() {
        val latestSavedVersionCode = slSharedPrefs().latestInstalledVersionCode
        val currentVersionName = BuildConfig.VERSION_CODE

        if (latestSavedVersionCode < currentVersionName) {
            slSharedPrefs().apiKey = stringFromJNI()
            slSharedPrefs().showSecretFeature = false
            slSharedPrefs().latestInstalledVersionCode = currentVersionName
        }
    }

    private fun initCrypto() {
        val key = CryptoUtil.generateSymmetricKey("avast-adventure")

        CryptoUtil.encrypt(
            cipherAlgorithm = CIPHER_AES,
            plainText = "CTF".toByteArray(Charsets.UTF_8),
            key = key
        )?.apply {
            cipherText = first
            iv = second
        }

        val plainText = CryptoUtil.decrypt(
            cipherAlgorithm = CIPHER_AES,
            cipherText = cipherText!!,
            key = key,
            iv = IvParameterSpec(iv)
        )
    }

    private external fun stringFromJNI(): String?
}