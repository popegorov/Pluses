#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
public:
    Zipped(Iterator first_begin, Iterator first_end, Iterator second_begin, Iterator second_end);

    struct Iter {
        Iter(Iterator first, Iterator second);
        bool operator!=(const Iter& other);
        Iter operator++();
        ZippedPair operator*() const;

    private:
        std::pair<Iterator, Iterator> ptr_;
    };

    Iter begin() const;
    Iter end() const;

private:
    Iterator first_begin_;
    Iterator first_end_;
    Iterator second_begin_;
    Iterator second_end_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
