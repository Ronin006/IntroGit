#include <cstddef>
#include <utility>
#include <stdexcept>


template <typename T>
class Quack {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;   //front
    Node* tail = nullptr;   //back
    std::size_t m_size = 0;

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        m_size = 0;
    }

    void copy_from(const Quack& other) {
        for (Node* cur = other.head; cur != nullptr; cur = cur->next)
            push_back(cur->value);
    }

public:
    Quack() = default;
    ~Quack() { clear(); }

    Quack(const Quack& other) { copy_from(other); }

    Quack(Quack&& other) noexcept
        : head(other.head), tail(other.tail), m_size(other.m_size) {
        other.head = other.tail = nullptr;
        other.m_size = 0;
    }

    Quack& operator=(Quack other) {
        swap(other);
        return *this;
    }

    void swap(Quack& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(m_size, other.m_size);
    }

    bool empty() const { return m_size == 0; }
    std::size_t size() const { return m_size; }

    void push_front(const T& value) {
        Node* n = new Node(value);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = head;
        ++m_size;
    }

    void push_front(T&& value) {
        Node* n = new Node(std::move(value));
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = head;
        ++m_size;
    }

    void push_back(const T& value) {
        Node* n = new Node(value);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = tail;
        ++m_size;
    }

    void push_back(T&& value) {
        Node* n = new Node(std::move(value));
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = tail;
        ++m_size;
    }

    T& front() {
        if (empty()) throw std::out_of_range("front on empty Quack");
        return head->value;
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("front on empty Quack");
        return head->value;
    }

    T& back() {
        if (empty()) throw std::out_of_range("back on empty Quack");
        return tail->value;
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("back on empty Quack");
        return tail->value;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("pop_front on empty Quack");
        Node* n = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete n;
        --m_size;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("pop_back on empty Quack");
        Node* n = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete n;
        --m_size;
    }
};


template <typename T>
class Queue {
private:
    Quack<T> data;

public:
    Queue() = default;

    bool empty() const { return data.empty(); }
    std::size_t size() const { return data.size(); }

    void push(const T& value) { data.push_back(value); }
    void push(T&& value) { data.push_back(std::move(value)); }

    T& front() { return data.front(); }
    const T& front() const { return data.front(); }

    void pop() { data.pop_front(); }
};