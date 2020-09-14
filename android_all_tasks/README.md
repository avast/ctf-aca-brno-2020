Source code of Android tasks on Avast Cyber Adventure 2020 https://www.avast-adventure.com/ .





CPT keys

1. In assets folder, plaintext in assets/data.csv
- unzip the apk (with any unarchiver), find the folder assets and read the file

2. In strings resources (strings.xml)
- when opened as zip, the strings are in binary file resources.arsc .
- way to get is using apktool - https://ibotpeaches.github.io/Apktool/ and decoding the apk file
- after decoding with apktool, the file is plaintext in res/values/strings.xml

3. In Kotlin/Java static field, in MainActivity.kt
- apktool decompiles the dexed files into human-readable .smali files
- it can be found when reading through the file in /smali_classes2/com/avast/MainActivity.smali

4. In shared preferences (android permanent storage)
- this requires rooted Android device or root access from adb (can be done using standard Android emulator)
- xml file can be found in data/data/com.avast.adventure/shared_prefs/AvastPrefs.xml

5. Enable secret feature - tamper the source code to enable the hidden feature. It will show the key on main screen.
- it requires to decode the apk using apktool, then edit the smali code in smali_classes2/com/avast/adventure/util/FeatureHelper.smali
- rebuild the apk using apktool, sign it and install to device
