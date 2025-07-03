#include "AVLTree.h"
#include <algorithm>

// 高度辅助函数
template <typename T>
int AVLTree<T>::height(Node* node) const {
    return node ? node->height : 0;
}

// 平衡因子计算
template <typename T>
int AVLTree<T>::balanceFactor(Node* node) const {
    return height(node->right.get()) - height(node->left.get());
}

// 更新节点高度
template <typename T>
void AVLTree<T>::updateHeight(Node* node) {
    node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));
}

// 左旋转
template <typename T>
void AVLTree<T>::rotateLeft(std::unique_ptr<Node>& node) {
    auto newRoot = std::move(node->right);
    node->right = std::move(newRoot->left);
    updateHeight(node.get());
    newRoot->left = std::move(node);
    node = std::move(newRoot);
    updateHeight(node.get());
}

// 右旋转
template <typename T>
void AVLTree<T>::rotateRight(std::unique_ptr<Node>& node) {
    auto newRoot = std::move(node->left);
    node->left = std::move(newRoot->right);
    updateHeight(node.get());
    newRoot->right = std::move(node);
    node = std::move(newRoot);
    updateHeight(node.get());
}

// 平衡节点
template <typename T>
void AVLTree<T>::balance(std::unique_ptr<Node>& node) {
    updateHeight(node.get());
    int bf = balanceFactor(node.get());
    
    if (bf > 1) {
        if (balanceFactor(node->right.get()) < 0) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    } else if (bf < -1) {
        if (balanceFactor(node->left.get()) > 0) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
}

// 插入数据
template <typename T>
void AVLTree<T>::insert(const T& data) {
    auto insertHelper = [](const auto& self, std::unique_ptr<Node>& node, const T& data) -> void {
        if (!node) {
            node = std::make_unique<Node>(data);
            return;
        }
        
        if (data < node->data) {
            self(self, node->left, data);
        } else if (node->data < data) {
            self(self, node->right, data);
        } else {
            // 数据已存在，更新值
            node->data = data;
            return;
        }
        
        balance(node);
    };
    
    insertHelper(insertHelper, root, data);
}

// 查找数据
template <typename T>
T* AVLTree<T>::find(const std::string& key) const {
    Node* current = root.get();
    while (current) {
        if (key < current->data.getTrackingNumber()) {
            current = current->left.get();
        } else if (current->data.getTrackingNumber() < key) {
            current = current->right.get();
        } else {
            return &current->data;
        }
    }
    return nullptr;
}

// 显式实例化模板
template class AVLTree<Package>;