#pragma once

#include <iterator>

template <typename Iterator1, typename Iterator2>
class Zipped {
public:
    Zipped(Iterator1 first_begin, Iterator1 first_end, Iterator2 second_begin, Iterator2 second_end) {
        first_begin_ = first_begin;
        first_end_ = first_end;
        second_begin_ = second_begin;
        second_end_ = second_end;
    }

    struct Iter {
        Iter(Iterator1 first, Iterator2 second) {
            ptr_first_ = first;
            ptr_second_ = second;
        }

        bool operator!=(const Iter& other) {
            return ptr_first_ != other.ptr_first_ && ptr_second_ != other.ptr_second_;
        }

        Iter& operator++() {
            ++ptr_first_;
            ++ptr_second_;
            return *this;
        }

        auto operator*() const {
            return std::make_pair(*ptr_first_, *ptr_second_);
        }

    private:
        Iterator1 ptr_first_;
        Iterator2 ptr_second_;
    };

    Iter begin() const {
        return Iter(first_begin_, second_begin_);
    }

    Iter end() const {
        return Iter(first_end_, second_end_);
    }

private:
    Iterator1 first_begin_;
    Iterator1 first_end_;
    Iterator2 second_begin_;
    Iterator2 second_end_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}
