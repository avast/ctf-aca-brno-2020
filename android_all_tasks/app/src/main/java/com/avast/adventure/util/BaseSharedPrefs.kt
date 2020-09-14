package com.avast.adventure.util

import android.content.Context
import android.content.SharedPreferences
import kotlin.properties.ReadWriteProperty
import kotlin.reflect.KProperty

/**
 * Base shared preferences wrapper class with convenience methods allowing creation of wrapper delegated properties
 * An implementing class only needs to instantiate the shared preferences (set the file name) and setup the delegated
 * preference value properties. If more complicated behaviour is needed, the SharedPreferences instance can be used directly
 *
 * This class is meant be used as a SL-backed service
 */
@Suppress("SameParameterValue")
abstract class BaseSharedPrefs(protected val context: Context) {

    protected abstract val sharedPreferences: SharedPreferences

    protected fun int(default: Int = 0, key: String? = null) =
        sharedPreferences.delegate(default, key, SharedPreferences::getInt, SharedPreferences.Editor::putInt)

    protected fun long(default: Long = 0, key: String? = null) =
        sharedPreferences.delegate(default, key, SharedPreferences::getLong, SharedPreferences.Editor::putLong)

    protected fun float(default: Float = 0f, key: String? = null) =
        sharedPreferences.delegate(default, key, SharedPreferences::getFloat, SharedPreferences.Editor::putFloat)

    protected fun boolean(default: Boolean = false, key: String? = null) =
        sharedPreferences.delegate(default, key, SharedPreferences::getBoolean, SharedPreferences.Editor::putBoolean)

    protected fun string(default: String = "", key: String? = null) =
        sharedPreferences.delegate(default, key, SharedPreferences::getString, SharedPreferences.Editor::putString)

    protected fun stringSet(default: Set<String> = emptySet(), key: String? = null) =
        sharedPreferences.delegate(default, key, SharedPreferences::getStringSet, SharedPreferences.Editor::putStringSet)

    // Creates a delegated property backed by shared preferences: https://hackernoon.com/kotlin-delegates-in-android-development-part-1-50346cf4aed7
    private inline fun <T> SharedPreferences.delegate(
        defaultValue: T,
        key: String?,
        crossinline getter: SharedPreferences.(String, T) -> T,
        crossinline setter: SharedPreferences.Editor.(String, T) -> SharedPreferences.Editor
    ): ReadWriteProperty<Any, T> {
        return object : ReadWriteProperty<Any, T> {
            override fun getValue(thisRef: Any, property: KProperty<*>) =
                getter(key ?: property.name, defaultValue)

            override fun setValue(thisRef: Any, property: KProperty<*>, value: T) =
                edit().setter(key ?: property.name, value).apply()
        }
    }
}