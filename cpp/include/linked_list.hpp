#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <cstddef>
#include <iterator>

template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& v) : value(v), next(nullptr) {}
    };
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

public:
    LinkedList() = default;
    ~LinkedList() { clear(); }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const { return size_; }

    // Inserción O(1)
    void push_back(const T& v) {
        Node* n = new Node(v);
        if (!head_) head_ = tail_ = n;
        else { tail_->next = n; tail_ = n; }
        ++size_;
    }

    void clear() {
        Node* cur = head_;
        while (cur) { Node* nx = cur->next; delete cur; cur = nx; }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    class iterator {
        Node* ptr_;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        explicit iterator(Node* p=nullptr) : ptr_(p) {}
        reference operator*() const { return ptr_->value; }
        pointer operator->() const { return &(ptr_->value); }
        iterator& operator++() { ptr_ = ptr_->next; return *this; }
        iterator operator++(int){ iterator tmp(*this); ++(*this); return tmp; }
        bool operator==(const iterator& o) const { return ptr_ == o.ptr_; }
        bool operator!=(const iterator& o) const { return ptr_ != o.ptr_; }
    };

    iterator begin() { return iterator(head_); }
    iterator end()   { return iterator(nullptr); }
};

#endif

