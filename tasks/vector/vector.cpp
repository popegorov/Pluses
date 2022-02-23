#include "vector.h"

#include <algorithm>

Vector::Vector() {
    capacity_ = 0;
    size_ = capacity_;
    ptr_ = new ValueType[capacity_];
}

Vector::Vector(SizeType size) {
    capacity_ = size;
    size_ = capacity_;
    ptr_ = new ValueType[size];

    for (SizeType i = 0; i < size; ++i) {
        ptr_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    capacity_ = list.size();
    size_ = capacity_;
    ptr_ = new ValueType[capacity_];

    SizeType i = 0;
    for (const auto& elem : list) {
        ptr_[i] = elem;
        ++i;
    }
}

Vector::Vector(const Vector& other) {
    capacity_ = other.capacity_;
    size_ = capacity_;
    ptr_ = new ValueType[capacity_];

    for (SizeType i = 0; i < size_; ++i) {
        ptr_[i] = other.ptr_[i];
    }
}

Vector::~Vector() {
    delete[] ptr_;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    auto tmp = new ValueType[capacity_];

    delete[] ptr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    ptr_ = tmp;
    std::copy(other.ptr_, other.ptr_ + size_, ptr_);

    return *this;
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }

    for (SizeType i = 0; i < size_; ++i) {
        if (ptr_[i] != other.ptr_[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    SizeType min_size = size_;
    if (min_size > other.size_) {
        min_size = other.size_;
    }

    for (SizeType i = 0; i < min_size; ++i) {
        if (ptr_[i] != other.ptr_[i]) {
            return ptr_[i] <=> other.ptr_[i];
        }
    }

    if (size_ != other.size_) {
        return size_ <=> other.size_;
    }

    return std::strong_ordering::equal;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return ptr_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return ptr_[position];
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

void Vector::Reserve(Vector::SizeType new_capacity) {
    if (new_capacity > capacity_) {
        ValueType* new_ptr = new ValueType[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_ptr[i] = ptr_[i];
        }
        delete[] ptr_;

        ptr_ = new_ptr;
        capacity_ = new_capacity;
    }
}

void Vector::PushBack(const Vector::ValueType& new_element) {
    if (!capacity_) {
        Reserve(1);
    } else if (capacity_ == size_) {
        Reserve(capacity_ * 2);
    }
    ptr_[size_] = new_element;
    ++size_;
}

void Vector::PopBack() {
    --size_;
}

const Vector::ValueType* Vector::Data() const {
    return ptr_;
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::Swap(Vector& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
}

Vector::Iterator Vector::Begin() {
    return Iterator(ptr_);
}

Vector::Iterator Vector::End() {
    return Iterator(ptr_ + size_);
}

Vector::Iterator Vector::begin() {
    return Begin();
}

Vector::Iterator Vector::end() {
    return End();
}

Vector::Iterator::Iterator(Vector::ValueType* pointer) {
    pointer_ = pointer;
}

Vector::Iterator::Iterator() {
    pointer_ = nullptr;
}

Vector::ValueType& Vector::Iterator::operator*() const {
    return *pointer_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
    return pointer_;
}

Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    pointer_ = other.pointer_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ++pointer_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    auto copy = *this;
    pointer_++;
    return copy;
}

Vector::Iterator& Vector::Iterator::operator--() {
    --pointer_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    auto copy = *this;
    pointer_--;
    return copy;
}

Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    Iterator result = *this;
    result += shift;
    return result;
}

Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return (pointer_ - other.pointer_);
}

Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    pointer_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    pointer_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return (pointer_ == other.pointer_);
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    return (pointer_ <=> other.pointer_);
}
