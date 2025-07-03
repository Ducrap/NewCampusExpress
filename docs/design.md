# 目录结构如下

## 根目录
/CampusExpress/
├── CMakeLists.txt                  # 主CMake配置文件
├── CampusExpress.pro              # Qt项目文件(可选)
├── README.md                      # 项目说明文档
├── LICENSE                        # 许可证文件
├── .gitignore                     # Git忽略规则
├── docs/                          # 项目文档
│   ├── requirements.md            # 需求文档
│   ├── design.md                  # 设计文档
│   └── database_schema.sql        # 数据库Schema
├── include/                       # 公共头文件
│   ├── core/                      # 核心数据结构
│   ├── gui/                       # 界面相关
│   ├── pickup/                    # 取件模块(A负责)
│   └── staff/                     # 管理模块(B负责)
├── src/                           # 源代码
│   ├── core/                      # 核心实现
│   ├── gui/                       # 界面实现
│   ├── pickup/                    # 取件模块实现
│   ├── staff/                     # 管理模块实现
│   └── main.cpp                   # 程序入口
├── libs/                          # 第三方库
│   ├── mysql/                     # MySQL连接库
│   └── qtavl/                     # AVL树可视化组件(可选)
├── tests/                         # 测试代码
│   ├── unit/                      # 单元测试
│   └── integration/               # 集成测试
├── resources/                     # 资源文件
│   ├── icons/                     # 图标资源
│   ├── styles/                    # QSS样式表
│   └── translations/              # 多语言翻译
└── scripts/                       # 实用脚本
    ├── database/                  # 数据库脚本
    └── deployment/                # 部署脚本

1. 核心模块 (core/)
include/core/
├── DatabaseConnector.h            # 数据库接口
├── AVLTree.h                      # AVL树实现
├── User.h                         # 用户数据结构
├── Package.h                      # 快递数据结构
└── Config.h                       # 配置参数

src/core/
├── DatabaseConnector.cpp          # MySQL实现
├── AVLTree.cpp                    # AVL树实现
├── User.cpp
├── Package.cpp
└── Config.cpp


2. 取件模块 (pickup/) 
include/pickup/
├── PickupQueue.h                  # 优先队列实现
├── PickupScheduler.h              # 调度系统
├── PickupService.h                # 服务接口
└── types.h                        # 数据类型定义

src/pickup/
├── PickupQueue.cpp
├── PickupScheduler.cpp
├── PickupService.cpp
└── CMakeLists.txt                 # 子模块构建配置

3. 管理模块 (staff/)
include/staff/
├── PackageManager.h               # 快递管理
├── UserManager.h                  # 用户管理
└── StaffService.h                 # 服务接口

src/staff/
├── PackageManager.cpp
├── UserManager.cpp
├── StaffService.cpp
└── CMakeLists.txt


4. 用户界面 (gui/)
include/gui/
├── LoginWindow.h                  # 登录界面
├── UserWindow.h                   # 用户界面
├── StaffWindow.h                  # 管理界面
├── DialogManager.h                # 对话框管理
└── styles.h                       # 样式定义

src/gui/
├── LoginWindow.cpp
├── UserWindow.cpp
├── StaffWindow.cpp
├── DialogManager.cpp
└── CMakeLists.txt


5. 测试目录 (tests/)
tests/
├── unit/
│   ├── core/                      # 核心模块测试
│   ├── pickup/                    # 取件模块测试
│   └── staff/                     # 管理模块测试
└── integration/
    ├── DatabaseTest/               # 数据库集成测试
    └── FullFlowTest/               # 完整流程测试