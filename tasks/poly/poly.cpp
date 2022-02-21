#include "poly.h"

void Poly::NewPoly(const std::vector<std::pair<size_t, int>>& coef) {
    for (const auto& elem : coef) {
        if (elem.second != 0) {
            coefficients_[elem.first] = elem.second;
        }
    }
}

Poly::Poly() {
}

Poly::Poly(const std::vector<int>& coefficients) {
    std::vector<std::pair<size_t, int>> coef;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        coef.push_back({i, coefficients[i]});
    }
    NewPoly(coef);
}

Poly::Poly(const std::vector<std::pair<size_t, int>>& coefficients) {
    NewPoly(coefficients);
}

Poly::Poly(const Poly& other) {
    NewPoly({other.coefficients_.begin(), other.coefficients_.end()});
}

Poly& Poly::operator=(const Poly& other) {
    if (this == &other) {
        return *this;
    }
    coefficients_ = other.coefficients_;
    return *this;
}

int64_t pow(int x, size_t deg) {
    if (!deg) {
        return 1;
    } else if (deg % 2 == 1) {
        return x * pow(x, deg - 1);
    } else {
        return pow(x, deg / 2) * pow(x, deg / 2);
    }
}

int64_t Poly::operator()(int x) const {
    int64_t res = 0;

    for (const auto& [deg, coef] : coefficients_) {
        res += static_cast<int64_t>(coef) * pow(x, deg);
    }

    return res;
}

bool Poly::operator==(const Poly& other) const {
    return coefficients_ == other.coefficients_;
}

bool Poly::operator!=(const Poly& other) const {
    return coefficients_ != other.coefficients_;
}

Poly Poly::operator-() const {
    Poly result;
    for (const auto& [deg, coef] : coefficients_) {
        result.coefficients_[deg] = -coef;
    }

    return result;
}

Poly& Poly::operator+=(const Poly& other) {
    for (const auto& [deg, coef] : other.coefficients_) {
        coefficients_[deg] += coef;
        if (!coefficients_[deg]) {
            coefficients_.erase(deg);
        }
    }

    return *this;
}

Poly& Poly::operator-=(const Poly& other) {
    return (*this += -other);
}

Poly Poly::operator+(const Poly& other) const {
    Poly result = *this;
    result += other;

    return result;
}

Poly Poly::operator-(const Poly& other) const {
    Poly result = *this;
    result -= other;

    return result;
}

Poly Poly::operator*(const Poly& other) const {
    Poly result;
    for (const auto& [deg1, coef1] : coefficients_) {
        for (const auto& [deg2, coef2] : other.coefficients_) {
            result.coefficients_[deg1 + deg2] += coef1 * coef2;
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const Poly& p) {
    out << "y = ";
    if (p.coefficients_.empty()) {
        out << 0;
        return out;
    }
    for (auto it = p.coefficients_.rbegin(); it != p.coefficients_.rend(); ++it) {
        if (it->second < 0) {
            out << "- ";
        } else if (it != p.coefficients_.rbegin()) {
            out << "+ ";
        }

        if ((it->first) > 1) {
            if (it->second != 1 && it->second != -1) {
                out << abs(it->second) << "x^" << it->first << " ";
            } else {
                out << "x^" << it->first << " ";
            }
        } else if (it->first) {
            if (it->second != 1 && it->second != -1) {
                out << abs(it->second) << "x ";
            } else {
                out << "x ";
            }
        } else {
            out << abs(it->second);
        }
    }

    return out;
}
