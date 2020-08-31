package com.avast.adventure.util

import android.content.Context
import android.content.SharedPreferences

class SharedPrefs(context: Context) : BaseSharedPrefs(context) {
    companion object {
        const val PREFERENCES_NAME = "AvastPrefs"
    }

    override val sharedPreferences: SharedPreferences = context.getSharedPreferences(PREFERENCES_NAME, Context.MODE_PRIVATE)

    var latestInstalledVersionName by string("", "pref_key_string_latest_installed_version_name")
    var latestInstalledVersionCode by int(-1, "pref_key_string_latest_installed_version_code")
    var apiKey by string("", "pref_key_string_api_endpoint")
    var showSecretFeature by boolean(false, "pref_key_boolean_show_secret_feature")
}

/**
 * A simple sugarcoat method to simplify sharedPrefs calls
 */
fun slSharedPrefs(): SharedPrefs = SL[SharedPrefs::class.java]