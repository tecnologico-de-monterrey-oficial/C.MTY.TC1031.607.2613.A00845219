#pragma once

template <typename T>
struct Node2 {
    T data;
    Node2<T>* next;
    Node2<T>* prev;

    Node2(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    Node2(const T& value, Node2<T>* nextNode, Node2<T>* prevNode) : data(value), next(nextNode), prev(prevNode) {} 
};