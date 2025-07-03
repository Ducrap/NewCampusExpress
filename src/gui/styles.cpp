#include "styles.h"

QString Styles::mainWindowStyle() {
    return R"(
        QMainWindow {
            background-color: #f5f5f5;
        }
    )";
}

QString Styles::buttonStyle() {
    return R"(
        QPushButton {
            background-color: #4CAF50;
            border: none;
            color: white;
            padding: 8px 16px;
            text-align: center;
            text-decoration: none;
            font-size: 14px;
            margin: 4px 2px;
            border-radius: 4px;
        }
        
        QPushButton:hover {
            background-color: #45a049;
        }
        
        QPushButton:pressed {
            background-color: #3e8e41;
        }
    )";
}

QString Styles::urgentButtonStyle() {
    return R"(
        QPushButton {
            background-color: #f44336;
            border: none;
            color: white;
            padding: 8px 16px;
            text-align: center;
            text-decoration: none;
            font-size: 14px;
            margin: 4px 2px;
            border-radius: 4px;
        }
        
        QPushButton:hover {
            background-color: #d32f2f;
        }
        
        QPushButton:pressed {
            background-color: #b71c1c;
        }
    )";
}

QString Styles::lineEditStyle() {
    return R"(
        QLineEdit {
            padding: 6px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
    )";
}

QString Styles::tableStyle() {
    return R"(
        QTableWidget {
            border: 1px solid #ddd;
            gridline-color: #ddd;
            font-size: 14px;
        }
        
        QHeaderView::section {
            background-color: #f2f2f2;
            padding: 8px;
            border: none;
        }
        
        QTableWidget::item {
            padding: 8px;
        }
        
        QTableWidget::item:selected {
            background-color: #e6f7ff;
            color: black;
        }
    )";
}

QString Styles::labelStyle() {
    return R"(
        QLabel {
            font-size: 14px;
        }
    )";
}

QString Styles::statusSuccessStyle() {
    return R"(
        QLabel {
            color: #4CAF50;
            font-weight: bold;
        }
    )";
}

QString Styles::statusErrorStyle() {
    return R"(
        QLabel {
            color: #f44336;
            font-weight: bold;
        }
    )";
}

QString Styles::tabWidgetStyle() {
    return R"(
        QTabWidget::pane {
            border-top: 1px solid #ddd;
        }
        
        QTabBar::tab {
            background: #f1f1f1;
            border: 1px solid #ddd;
            border-bottom: none;
            padding: 8px 16px;
        }
        
        QTabBar::tab:selected {
            background: white;
            border-bottom: 1px solid white;
            margin-bottom: -1px;
        }
    )";
}

QString Styles::loginPageStyle() {
    return R"(
        QGroupBox {
            border: 1px solid #ddd;
            border-radius: 4px;
            margin-top: 10px;
            padding-top: 15px;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
        }
    )";
}