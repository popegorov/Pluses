#include "zip.h"

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    auto zipped = Zipped(a_begin, a_end, b_begin, b_end);

    return zipped;
}

Zipped::Zipped(Iterator first_begin, Iterator first_end, Iterator second_begin, Iterator second_end) {
    first_begin_ = first_begin;
    first_end_ = first_end;
    second_begin_ = second_begin;
    second_end_ = second_end;
}

Zipped::Iter::Iter(Iterator first, Iterator second) {
    ptr_ = {first, second};
}

Zipped::Iter Zipped::begin() const {
    return Iter(first_begin_, second_begin_);
}

Zipped::Iter Zipped::end() const {
    auto cur_first = first_begin_;
    auto cur_second = second_begin_;
    while (cur_first != first_end_ && cur_second != second_end_) {
        cur_first++;
        cur_second++;
    }
    return (Iter(cur_first, cur_second));
}

Zipped::Iter Zipped::Iter::operator++() {
    return Iter(ptr_.first++, ptr_.second++);
}

bool Zipped::Iter::operator!=(const Iter& other) {
    return (ptr_.first != other.ptr_.first || ptr_.second != other.ptr_.second);
}

ZippedPair Zipped::Iter::operator*() const {
    return {*ptr_.first, *ptr_.second};
}
