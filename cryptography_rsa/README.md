# RSA

"I heard RSA is super-secure, so I use it to encrypt my notes. You can try to decrypt one of them, but I even create my keys by hand - that way I´m sure to avoid any OpenSSL vulnerabilities. Hint: flag was encrypted using the enclosed public key. Submit the solution in format avastCTF{text}."

Provide players with files `encrypted` and `rsa.public`.
Solution: File `encrypted` contains `flag.txt` encrypted by weak RSA public key. Fermat´s factorization can be used to factor n, private key can be reconstructed and used to decrypt flag.
