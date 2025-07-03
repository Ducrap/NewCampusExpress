#ifndef AVLTREE_H
#define AVLTREE_H

#include "Package.h"
#include <memory>
#include <vector>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height;
        
        Node(const T& data) : data(data), left(nullptr), right(nullptr), height(1) {}
    };
    
    std::unique_ptr<Node> root;
    
    // 辅助函数
    int height(Node* node) const;
    int balanceFactor(Node* node) const;
    void updateHeight(Node* node);
    void rotateLeft(std::unique_ptr<Node>& node);
    void rotateRight(std::unique_ptr<Node>& node);
    void balance(std::unique_ptr<Node>& node);
    
public:
    AVLTree() : root(nullptr) {}
    
    // 插入数据
    void insert(const T& data);
    
    // 删除数据
    bool remove(const std::string& key); // 假设T有getKey()方法
    
    // 查找数据
    T* find(const std::string& key) const;
    
    // 更新数据
    bool update(const T& data);
    
    // 获取所有数据
    std::vector<T> getAll() const;
    
    // 清空树
    void clear();
    
    // 检查是否为空
    bool isEmpty() const;
};

// 为Package特化
template class AVLTree<Package>;

extern template class AVLTree<Package>;

#endif // AVLTREE_H