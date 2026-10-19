#pragma once
#include <memory>

template <typename T>
struct Node {
    T data;
    // asi es compatible con unique_ptr
    std::unique_ptr<Node<T>> next; 

    Node(const T& value) : data(value), next(nullptr) {}
    Node(const T& value, std::unique_ptr<Node<T>> nextNode) : data(value), next(std::move(nextNode)) {} 
};