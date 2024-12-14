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
#include <unordered_map>

class Asset {
public:
    std::string name;
    bool isPublic;

    Asset(std::string assetName, bool publicAccess) : name(assetName), isPublic(publicAccess) {}
};

class AssetManager {
private:
    std::unordered_map<std::string, Asset> assets;

public:
    void addAsset(std::string assetName, bool isPublic) {
        assets[assetName] = Asset(assetName, isPublic);
    }

    bool loadAsset(std::string assetName) {
        if (assets.find(assetName) != assets.end()) {
            Asset& asset = assets[assetName];
            if (asset.isPublic) {
                std::cout << "Loading public asset: " << assetName << "\n";
                return true;
            } else {
                std::cerr << "Error: Asset " << assetName << " is private and cannot be accessed.\n";
                return false;
            }
        }
        std::cerr << "Error: Asset not found.\n";
        return false;
    }
};

int main() {
    AssetManager manager;
    manager.addAsset("public_model", true);
    manager.addAsset("private_model", false);

    manager.loadAsset("public_model");   // Allowed
    manager.loadAsset("private_model");  // Blocked

    return 0;
}