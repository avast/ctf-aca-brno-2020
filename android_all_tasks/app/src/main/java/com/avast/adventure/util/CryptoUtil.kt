package com.avast.adventure.util

import android.security.keystore.KeyGenParameterSpec
import android.security.keystore.KeyProperties
import java.security.GeneralSecurityException
import java.security.Key
import java.security.KeyStore
import javax.crypto.Cipher
import javax.crypto.KeyGenerator
import javax.crypto.spec.IvParameterSpec

object CryptoUtil {
    fun generateSymmetricKey(keyAlias: String): Key {
        val keyStore = KeyStore.getInstance("AndroidKeyStore")
        keyStore.load(null)
        if (!keyStore.containsAlias(keyAlias)) {
            val keyGenerator = KeyGenerator.getInstance(KeyProperties.KEY_ALGORITHM_AES, "AndroidKeyStore")
            val keyGenParameterSpec =
                KeyGenParameterSpec.Builder(
                        keyAlias,
                        KeyProperties.PURPOSE_ENCRYPT or KeyProperties.PURPOSE_DECRYPT
                    )
                    .setBlockModes(KeyProperties.BLOCK_MODE_CBC)
                    .setEncryptionPaddings(KeyProperties.ENCRYPTION_PADDING_PKCS7)
                    .build()
            keyGenerator.init(keyGenParameterSpec)
            return keyGenerator.generateKey()
        }
        return keyStore.getKey(keyAlias, null)
    }

    fun encrypt(cipherAlgorithm: String, plainText: ByteArray, key: Key): Pair<ByteArray, ByteArray>? {
        return try {
            val cipher = Cipher.getInstance(cipherAlgorithm)
            cipher.init(Cipher.ENCRYPT_MODE, key)
            val cipherText = cipher.doFinal(plainText)
            Pair(cipherText, cipher.iv)
        } catch (exception: GeneralSecurityException) {
            null
        }
    }

    fun decrypt(cipherAlgorithm: String, cipherText: ByteArray, key: Key, iv: IvParameterSpec? = null): ByteArray? {
        val cipher = Cipher.getInstance(cipherAlgorithm)
        cipher.init(Cipher.DECRYPT_MODE, key, iv)
        val plainText = cipher.doFinal(cipherText)
        return plainText
    }
}