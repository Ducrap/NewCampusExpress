#ifndef STYLES_H
#define STYLES_H

#include <QString>

class Styles {
public:
    // 获取主窗口样式表
    static QString mainWindowStyle();
    
    // 获取按钮样式表
    static QString buttonStyle();
    
    // 获取紧急按钮样式表
    static QString urgentButtonStyle();
    
    // 获取输入框样式表
    static QString lineEditStyle();
    
    // 获取表格样式表
    static QString tableStyle();
    
    // 获取标签样式表
    static QString labelStyle();
    
    // 获取状态标签样式表 (成功)
    static QString statusSuccessStyle();
    
    // 获取状态标签样式表 (错误)
    static QString statusErrorStyle();
    
    // 获取选项卡样式表
    static QString tabWidgetStyle();
    
    // 获取登录页面特定样式
    static QString loginPageStyle();
};

#endif // STYLES_H