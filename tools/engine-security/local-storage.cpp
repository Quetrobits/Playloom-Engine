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
#include <fstream>
#include <string>
#include <openssl/aes.h>

class CookieManager {
private:
    static const std::string encryptionKey;

public:
    static void saveCookie(std::string cookieData) {
        std::string encryptedData = encrypt(cookieData);
        std::ofstream cookieFile("cookies.enc", std::ios::binary);
        if (cookieFile.is_open()) {
            cookieFile.write(encryptedData.c_str(), encryptedData.size());
            cookieFile.close();
        } else {
            std::cerr << "Error saving encrypted cookie data.\n";
        }
    }

    static std::string loadCookie() {
        std::ifstream cookieFile("cookies.enc", std::ios::binary);
        if (cookieFile.is_open()) {
            std::string encryptedData((std::istreambuf_iterator<char>(cookieFile)), std::istreambuf_iterator<char>());
            cookieFile.close();
            return decrypt(encryptedData);
        }
        return "";
    }

private:
    static std::string encrypt(const std::string& data) {
        unsigned char encrypted[AES_BLOCK_SIZE * ((data.size() / AES_BLOCK_SIZE) + 1)];
        AES_KEY encryptKey;
        AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(encryptionKey.c_str()), 128, &encryptKey);
        AES_encrypt(reinterpret_cast<const unsigned char*>(data.c_str()), encrypted, &encryptKey);

        return std::string(reinterpret_cast<char*>(encrypted), sizeof(encrypted));
    }

    static std::string decrypt(const std::string& encryptedData) {
        unsigned char decrypted[AES_BLOCK_SIZE * ((encryptedData.size() / AES_BLOCK_SIZE) + 1)];
        AES_KEY decryptKey;
        AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(encryptionKey.c_str()), 128, &decryptKey);
        AES_decrypt(reinterpret_cast<const unsigned char*>(encryptedData.c_str()), decrypted, &decryptKey);

        return std::string(reinterpret_cast<char*>(decrypted), sizeof(decrypted));
    }
};

const std::string CookieManager::encryptionKey = "AUniqueEncryptionKey";

int main() {
    CookieManager::saveCookie("user_session=abcd1234");

    std::string cookie = CookieManager::loadCookie();
    std::cout << "Loaded cookie: " << cookie << "\n";

    return 0;
}