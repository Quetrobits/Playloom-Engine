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
#include <map>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>

class User {
public:
    std::string username;
    std::string password;
    bool authenticated;
    std::string sessionToken;
    time_t tokenExpiration;

    User(std::string user, std::string pass) : username(user), password(pass), authenticated(false) {}
};

class AuthenticationSystem {
private:
    std::map<std::string, User> users;

public:
    void addUser(std::string username, std::string password) {
        users[username] = User(username, hashPassword(password));
    }

    static std::string hashPassword(const std::string& password) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256_ctx;
        SHA256_Init(&sha256_ctx);
        SHA256_Update(&sha256_ctx, password.c_str(), password.length());
        SHA256_Final(hash, &sha256_ctx);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << (int)hash[i];
        }
        return ss.str();
    }

    bool validateCredentials(std::string username, std::string password) {
        if (users.find(username) != users.end() && users[username].password == hashPassword(password)) {
            std::string token = generateSessionToken(username);
            users[username].sessionToken = token;
            users[username].tokenExpiration = time(0) + 3600;  // 1 hour expiration time
            users[username].authenticated = true;
            return true;
        }
        return false;
    }

    bool validateToken(std::string username, std::string token) {
        if (users.find(username) != users.end()) {
            User& user = users[username];
            if (user.sessionToken == token && user.tokenExpiration > time(0)) {
                return true;
            }
        }
        return false;
    }

private:
    std::string generateSessionToken(const std::string& username) {
        std::string token = username + std::to_string(time(0)) + std::to_string(rand());
        return hashPassword(token);  // Simple token generation based on user info and timestamp
    }
};

int main() {
    AuthenticationSystem auth;
    auth.addUser("player1", "securepassword");

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (auth.validateCredentials(username, password)) {
        std::cout << "Login successful. Session token generated.\n";
    } else {
        std::cout << "Invalid credentials.\n";
    }

    return 0;
}