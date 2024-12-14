// SECURITY WARNING
// ------------------------------------------------------------
// As this is an open-sourced project, you are allowed to 
// change these files. However, please note that modifying 
// any of these files could expose you to potential security 
// risks or theft of assets. While we cannot stop you from 
// changing these files, we highly recommend that you do NOT 
// alter them to avoid compromising the security and integrity 
// of the project. Any modifications are made at your own risk!
// ------------------------------------------------------------

#include <iostream>
#include <string>
#include <openssl/aes.h>
#include <openssl/rand.h>

class AdvancedEncryptor {
public:
    static std::string generateKey() {
        unsigned char key[AES_BLOCK_SIZE];
        if (RAND_bytes(key, AES_BLOCK_SIZE) != 1) {
            std::cerr << "Error generating random key.\n";
            return "";
        }
        return std::string(reinterpret_cast<char*>(key), AES_BLOCK_SIZE);
    }

    static std::string encrypt(const std::string& data, const std::string& key) {
        unsigned char iv[AES_BLOCK_SIZE] = { 0 };  // Initialization vector
        unsigned char encrypted[data.size() + AES_BLOCK_SIZE];
        AES_KEY encryptKey;
        AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &encryptKey);
        AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(data.c_str()), encrypted, data.size(), &encryptKey, iv, AES_ENCRYPT);

        return std::string(reinterpret_cast<char*>(encrypted), data.size() + AES_BLOCK_SIZE);
    }

    static std::string decrypt(const std::string& encryptedData, const std::string& key) {
        unsigned char iv[AES_BLOCK_SIZE] = { 0 };
        unsigned char decrypted[encryptedData.size()];
        AES_KEY decryptKey;
        AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &decryptKey);
        AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(encryptedData.c_str()), decrypted, encryptedData.size(), &decryptKey, iv, AES_DECRYPT);

        return std::string(reinterpret_cast<char*>(decrypted), encryptedData.size());
    }
};

int main() {
    std::string key = AdvancedEncryptor::generateKey();
    std::string data = "Sensitive Game Data";

    std::string encrypted = AdvancedEncryptor::encrypt(data, key);
    std::cout << "Encrypted: " << encrypted << "\n";

    std::string decrypted = AdvancedEncryptor::decrypt(encrypted, key);
    std::cout << "Decrypted: " << decrypted << "\n";

    return 0;
}