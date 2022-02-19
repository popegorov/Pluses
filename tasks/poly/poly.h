#pragma once

#include <ostream>
#include <map>
#include <vector>

class Poly {
public:
    Poly();
    Poly(const std::vector<int>& coefficients);
    Poly(const std::vector<std::pair<size_t, int>>& coefficients);
    Poly(const Poly& other);
    Poly& operator=(const Poly& other);

    int64_t operator()(int x) const;

    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;

    Poly operator-() const;

    Poly& operator+=(const Poly& other);
    Poly& operator-=(const Poly& other);

    Poly operator+(const Poly& other) const;
    Poly operator-(const Poly& other) const;
    Poly operator*(const Poly& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Poly& p);

private:
    std::map<size_t, int> coefficients_;
    void NewPoly(std::vector<std::pair<size_t, int>>& coef);
};
