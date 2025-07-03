#include "Config.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::map<std::string, std::string> Config::configMap;

bool Config::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        // 跳过注释和空行
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
        if (line.empty() || line[0] == '#') continue;
        
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            configMap[key] = value;
        }
    }
    
    file.close();
    return true;
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) {
    auto it = configMap.find(key);
    return it != configMap.end() ? it->second : defaultValue;
}

int Config::getInt(const std::string& key, int defaultValue) {
    auto it = configMap.find(key);
    if (it == configMap.end()) return defaultValue;
    
    try {
        return std::stoi(it->second);
    } catch (...) {
        return defaultValue;
    }
}

bool Config::getBool(const std::string& key, bool defaultValue) {
    auto it = configMap.find(key);
    if (it == configMap.end()) return defaultValue;
    
    std::string value = it->second;
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    return value == "true" || value == "1" || value == "yes";
}

void Config::setString(const std::string& key, const std::string& value) {
    configMap[key] = value;
}

void Config::setInt(const std::string& key, int value) {
    configMap[key] = std::to_string(value);
}

void Config::setBool(const std::string& key, bool value) {
    configMap[key] = value ? "true" : "false";
}

bool Config::save(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) return false;
    
    for (const auto& pair : configMap) {
        file << pair.first << "=" << pair.second << "\n";
    }
    
    file.close();
    return true;
}