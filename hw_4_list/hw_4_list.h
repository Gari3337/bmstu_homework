#pragma once

#include <iostream>

namespace bmstu {
    template<typename T>
    class list{
        struct node {
            node() = default;
            node(node *prev, const T &value, node *next)
                    : value(value), prev_node_(prev), next_node_(next) { }
            T value;
            node *next_node_ = nullptr;
            node *prev_node_ = nullptr;
        };

    public:
        template<typename value_t>
        struct list_iterator {
            friend class node;
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = value_t;
            using difference_type = ptrdiff_t;
            using pointer = value_t *;
            using reference = value_t &;
            using const_reference = const value_t &;

            list_iterator() = default;

            explicit list_iterator(node *node) : node_(node) { }

            list_iterator(const list_iterator &other) = default;

            reference operator*() const {
                assert(node_ != nullptr);
                return node_->value;
            }

            list_iterator &operator++(int) {
                assert(node_ != nullptr);
                node_ = node_->next_node_;
                return *this;
            }

            pointer operator->() {
                assert(node_ != nullptr);
                return &(node_->value);
            }

            list_iterator &operator--(int) {
                assert(node_ != nullptr);
                node_ = node_->prev_node_;
                return *this;
            }

            list_iterator operator++() {
                list_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            list_iterator operator--() {
                list_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            template<typename Integer>
            list_iterator operator+(Integer n) const {
                list_iterator copy(*this);
                for (auto i = 1; i <= n; ++i) {
                    ++(copy);
                }
                return copy;
            }
            list_iterator operator-(const difference_type n) const {
                list_iterator copy(*this);
                for (auto i = 1; i <= n; ++i) {
                    --(copy);
                }
                return copy;
            }

            friend difference_type operator-(const list_iterator &end,
                                             const list_iterator &begin) {
                difference_type count = 0;
                list_iterator copy(begin);
                for (; copy != end; ++copy, ++count) { }
                return count;
            }

            list_iterator &operator=(const list_iterator &other) = default;

            bool operator==(const list_iterator<const T> &other) const {
                return node_ == other.node_;
            }

            bool operator==(const list_iterator<T> &other) const {
                return node_ == other.node_;
            }

            explicit operator bool() {
                return node_ != nullptr;
            }

            bool operator!=(const list_iterator &other) const {
                return node_ != other.node_;
            }

        private:
            list::node *node_ = nullptr;
        };
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = list_iterator<T>;
        using const_iterator = list_iterator<T>;
        list() : size_(0), tail_(new node()), head_(new node()) {
            tail_->prev_node_ = head_;
            head_->next_node_ = tail_;
        }
        template<typename it>
        list(it begin, it end) : size_(0), tail_(new node()), head_(new node()) {
            tail_->prev_node_ = head_;
            head_->next_node_ = tail_;
            for (auto i = begin; i != end; ++i) {
                push_back(*i);
            }
        }
        list(std::initializer_list<T> values)
                : size_(0), tail_(new node()), head_(new node()) {
            tail_->prev_node_ = head_;
            head_->next_node_ = tail_;
            for (auto &i : values) {
                push_back(i);
            }
        }
        list(const list &other) : size_(0), tail_(new node()), head_(new node()) {
            tail_->prev_node_ = head_;
            head_->next_node_ = tail_;
            for (auto i : other) {
                push_back(i);
            }
        }
        list(list &&other) noexcept { swap(other); }
        template<typename Type>
        void push_back(const Type &value) {
            node *last = tail_->prev_node_;
            node *new_last = new node(last, value, tail_);
            last->next_node_ = new_last;
            tail_->prev_node_ = new_last;
            ++size_;
        }
        template<typename Type>
        void push_front(const Type &value) {
            node *first = head_->next_node_;
            node *new_first = new node(head_, value, first);
            first->prev_node_ = new_first;
            head_->next_node_ = new_first;
            ++size_;
        }
        [[nodiscard]] bool empty() const noexcept {
            return size_ == 0;
        }
        ~list() {
            clear();
            delete head_;
            delete tail_;
        }
        void clear() {
            if (!empty()) {
                while (head_->next_node_ != tail_) {
                    node *tmp = head_->next_node_;
                    head_->next_node_ = tmp->next_node_;
                    delete tmp;
                }
                size_ = 0;
            }
        }
        size_t size() const {
            return size_;
        }
        void swap(list &other) noexcept {
            std::swap(head_, other.head_);
            std::swap(tail_, other.tail_);
            std::swap(size_, other.size_);
        }
        friend void swap(list &l, list &r) {
            std::swap(l.head_, r.head_);
            std::swap(l.tail_, r.tail_);
            std::swap(l.size_, r.size_);
        }
        iterator begin() {
            return iterator(this->head_->next_node_);
        }
        iterator end() {
            return iterator(this->tail_);
        }
        const_iterator begin() const noexcept {
            return const_iterator(this->head_->next_node_);
        }
        const_iterator end() const noexcept {
            return const_iterator(this->tail_);
        }
        const_iterator cbegin() const noexcept {
            return const_iterator(this->head_->next_node_);
        }
        const_iterator cend() const noexcept {
            return const_iterator(this->tail_);
        }
        T operator[](size_t pos) const {
            node *current = head_->next_node_;
            for (size_t i = 0; i < pos; ++i) {
                current = current->next_node_;
            }
            return current->value;
        }
        T &operator[](size_t pos) {
            node *current = head_->next_node_;
            for (size_t i = 0; i < pos; ++i) {
                current = current->next_node_;
            }
            return current->value;
        }
        list &operator=(const list<T> &other) {
            if (this != &other) {
                clear();
                for (const auto &value : other) {
                    push_back(value);
                }
            }
            return *this;
        }

        list &operator=(list<T> &&other) noexcept {
            this->swap(other);
            return *this;
        }

        friend bool operator==(const list &l, const list &r) {
            if (l.size() != r.size()) return false;
            for (auto l_it = l.begin(), r_it = r.begin(); l_it != l.end();
                 ++l_it, ++r_it) {
                if (*l_it != *r_it) {
                    return false;
                }
            }
            return true;
        }
        friend bool operator!=(const list &l, const list &r) {
            return !(l == r);
        }
        friend bool operator<(const list &l, const list &r) {
            return lexicographical_compare_(l, r);
        }
        friend bool operator>(const list &l, const list &r) {
            return !(l <= r);
        }
        friend bool operator<=(const list &l, const list &r) {
            return (l < r || l == r);
        }
        friend bool operator>=(const list &l, const list &r) {
            return !(l < r);
        }
        friend std::ostream &operator<<(std::ostream &os, const list &other) {
            os << "[ ";
            for (size_t i = 0; i < other.size(); ++i) {
                os << other[i];
                if (i < other.size() - 1) {
                    os << ", ";
                }
            }
            os << " ]";
            return os;
        }
        iterator insert(const_iterator pos, const T &value) {
            node *current = head_->next_node_;
            for (size_t i = 0; i < (pos - begin()); ++i) {
                current = current->next_node_;
            }
            node *new_node = new node(current->prev_node_, value, current);
            current->prev_node_->next_node_ = new_node;
            current->prev_node_ = new_node;
            ++size_;
            return pos;
        }

    private:
        static bool lexicographical_compare_(const list<T> &l, const list<T> &r) {
            auto lb = l.begin();
            auto rb = r.begin();
            auto le = l.end();
            auto re = r.end();
            for (; (lb != le) && (rb != re); ++lb, ++rb) {
                if (*lb < *rb) {
                    return true;
                }
                if (*lb > *rb) {
                    return false;
                }
            }
            return (lb == le) && (rb != re);
        }
        size_t size_ = 0;
        node *tail_ = nullptr;
        node *head_ = nullptr;
    };
}  // namespace bmstu
