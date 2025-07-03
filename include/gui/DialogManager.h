#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QObject>
#include <QMessageBox>

class DialogManager : public QObject {
    Q_OBJECT

public:
    explicit DialogManager(QObject* parent = nullptr);
    
    // 信息对话框
    void showInformation(const QString& title, const QString& message);
    
    // 警告对话框
    void showWarning(const QString& title, const QString& message);
    
    // 错误对话框
    void showError(const QString& title, const QString& message);
    
    // 确认对话框
    bool showQuestion(const QString& title, const QString& message);
    
    // 输入对话框
    QString getTextInput(const QString& title, 
                        const QString& label, 
                        const QString& defaultText = "");
    
    // 详情对话框
    void showDetails(const QString& title, 
                    const QString& message, 
                    const QString& detailedText);

private:
    QWidget* findActiveWindow() const;
};

#endif // DIALOGMANAGER_H