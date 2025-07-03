#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
public:
    // 加载配置文件
    static bool load(const std::string& filePath);
    
    // 获取配置值
    static std::string getString(const std::string& key, const std::string& defaultValue = "");
    static int getInt(const std::string& key, int defaultValue = 0);
    static bool getBool(const std::string& key, bool defaultValue = false);
    
    // 设置配置值 (运行时修改)
    static void setString(const std::string& key, const std::string& value);
    static void setInt(const std::string& key, int value);
    static void setBool(const std::string& key, bool value);
    
    // 保存配置到文件
    static bool save(const std::string& filePath);

private:
    static std::map<std::string, std::string> configMap;
    
    // 防止实例化
    Config() = delete;
    ~Config() = delete;
};

#endif // CONFIG_H