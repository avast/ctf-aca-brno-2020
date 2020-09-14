package com.avast.adventure.util

import android.annotation.SuppressLint
import android.content.Context
import androidx.annotation.StringRes
import com.github.ajalt.timberkt.Timber
import java.util.HashMap

// Suppressing because this is quite a old but reliable code so
// I didn't want to polish it.
@SuppressLint("StaticFieldLeak")
@SuppressWarnings("ReturnCount", "TooGenericExceptionCaught")

/**
 * Service locator class.
 *
 * Use call like `SL.get(context, GlobalMessageService.class)` to get singleton instance of desired
 * class or interface implementation.
 *
 * Adapted from Java version of `SL` class used in various Inloop and Inmite projects.
 *
 * See https://medium.com/@daniel_novak/af3830924c69 for more info.
 */
object SL {

    private val sServicesInstances = HashMap<String, Any>()
    private val sServicesCreators = HashMap<String, ((context: Context) -> Any)?>()

    private val sServicesImplementationsMapping = HashMap<String, Class<*>>()
    private lateinit var mContext: Context

    private val sServicesInstancesLock = Any()

    fun init(context: Context) {
        mContext = context.applicationContext
    }

    /**
     * Return instance of desired class or object that implement desired interface.
     */
    @Suppress("UNCHECKED_CAST")
    operator fun <T> get(clazz: Class<T>): T {
        return getService(clazz.name, mContext) as T
    }

    operator fun get(@StringRes stringRes: Int): String = mContext.getString(stringRes)

    /**
     * This method allow bind custom service implementation to some interface.
     *
     * @param interfaceClass      interface
     * @param implementationClass class which implement interface specified in first param
     */
    fun bindCustomServiceImplementation(interfaceClass: Class<*>, implementationClass: Class<*>) {
        synchronized(sServicesInstancesLock) {
            sServicesImplementationsMapping.put(interfaceClass.name, implementationClass)
        }
    }

    /** This method allows bind custom service creator.
     * @param
     */
    fun <T> bindCustomServiceCreator(
        interfaceClass: Class<T>, creator: (context: Context) -> Any,
        vararg classesToInvalidate: Class<*>
    ) {
        synchronized(sServicesInstancesLock) {
            val name = interfaceClass.name
            sServicesCreators[name] = creator
            sServicesInstances.remove(name)
            for (clazz in classesToInvalidate) {
                sServicesInstances.remove(clazz.name)
            }
        }
    }

    private fun getService(name: String, applicationContext: Context): Any {
        synchronized(sServicesInstancesLock) {
            val o = sServicesInstances[name]
            return o ?: try {

                val serviceInstance: Any

                // if creator exists then let's call it
                val creator = sServicesCreators[name]
                if (creator != null) {
                    serviceInstance = creator(applicationContext)

                    Timber.v {
                        "App.getSystemService() - instantiate custom service" +
                            " $name as object $serviceInstance using creator."
                    }
                } else {
                    // we don't have creator so let's do reflection magic
                    val clazz: Class<*> = if (sServicesImplementationsMapping.containsKey(name)) {
                        sServicesImplementationsMapping[name]!!
                    } else {
                        Class.forName(name)
                    }

                    serviceInstance = try {
                        val constructor = clazz.getConstructor(Context::class.java)
                        constructor.newInstance(applicationContext)
                    } catch (exception: NoSuchMethodException) {
                        val constructor = clazz.getConstructor()
                        constructor.newInstance()
                    }
                    Timber.v {
                        "App.getSystemService() - instantiate custom service" +
                            " $name as object $serviceInstance using reflection."
                    }
                }

                sServicesInstances[name] = serviceInstance

                return serviceInstance

            } catch (e: ClassNotFoundException) {
                throw IllegalArgumentException("Requested service class was not found: $name", e)
            } catch (e: Exception) {
                throw IllegalArgumentException("Cannot initialize requested service: $name", e)
            }
        }
    }
}