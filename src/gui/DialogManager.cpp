#include "DialogManager.h"
#include <QApplication>
#include <QInputDialog>

DialogManager::DialogManager(QObject* parent) : QObject(parent) {}

void DialogManager::showInformation(const QString& title, const QString& message) {
    QMessageBox::information(findActiveWindow(), title, message);
}

void DialogManager::showWarning(const QString& title, const QString& message) {
    QMessageBox::warning(findActiveWindow(), title, message);
}

void DialogManager::showError(const QString& title, const QString& message) {
    QMessageBox::critical(findActiveWindow(), title, message);
}

bool DialogManager::showQuestion(const QString& title, const QString& message) {
    return QMessageBox::question(findActiveWindow(), title, message) == QMessageBox::Yes;
}

QString DialogManager::getTextInput(const QString& title, const QString& label, const QString& defaultText) {
    bool ok;
    QString text = QInputDialog::getText(findActiveWindow(), title, label, 
                                       QLineEdit::Normal, defaultText, &ok);
    return ok ? text : QString();
}

void DialogManager::showDetails(const QString& title, const QString& message, const QString& detailedText) {
    QMessageBox msgBox(findActiveWindow());
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setDetailedText(detailedText);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

QWidget* DialogManager::findActiveWindow() const {
    foreach (QWidget *w, QApplication::topLevelWidgets()) {
        if (w->isWindow() && w->isActiveWindow()) {
            return w;
        }
    }
    return nullptr;
}