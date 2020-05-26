#include <iostream>

class safe_long_long_t {
public:
    long long value;

    long long get_value() {
        return value;
    };

public: void set_value(long long number) {
        this->value = number;
    };

public: safe_long_long_t() {
        value = 0;
    };

public: safe_long_long_t(long long number) {
        value = number;
    };

public: void operator= (long long number) {
        this->value = number;
    };

public: safe_long_long_t operator+ (safe_long_long_t number) {
        return safe_long_long_t(value + number.get_value());
    };

public: safe_long_long_t operator- (safe_long_long_t number) {
        return safe_long_long_t(value - number.get_value());
    };

public: safe_long_long_t operator* (safe_long_long_t number) {
        return safe_long_long_t(value * number.get_value());
    };

public:
    bool operator== (safe_long_long_t number) {
        return (this->value == number.get_value());
    };
    bool operator>= (safe_long_long_t number) {
        return (this->value >= number.get_value());
    };
    bool operator<= (safe_long_long_t number) {
        return (this->value <= number.get_value());
    };
    bool operator> (safe_long_long_t number) {
        return (this->value > number.get_value());
    };
    bool operator< (safe_long_long_t number) {
        return (this->value < number.get_value());
    };
    bool operator!= (safe_long_long_t number) {
        return (this->value != number.get_value());
    };


public: friend std::ostream &operator<< (std::ostream &out, safe_long_long_t number);
public: friend std::istream &operator>> (std::istream &in, safe_long_long_t &number);
public: friend safe_long_long_t operator+(int l, safe_long_long_t& r);
public: friend safe_long_long_t operator-(int l, safe_long_long_t& r);
public: friend safe_long_long_t operator*(int l, safe_long_long_t& r);
};

std::ostream& operator<< (std::ostream &out, safe_long_long_t number) {
    out << number.get_value();
    return out;
};

std::istream& operator>> (std::istream& in, safe_long_long_t& number) {
    in >> number.value;
    return in;
};

static safe_long_long_t operator+ (int l, safe_long_long_t& r) {
    return l + r.get_value();
};

static safe_long_long_t operator- (int l, safe_long_long_t &r) {
    return l - r.get_value();
};

static safe_long_long_t operator* (int l, safe_long_long_t &number) {
    return safe_long_long_t(l*number.get_value());
};

int main() {
    safe_long_long_t number1, number2;
    number1 = 10;
    number2 = 12;
    std::cout << "Enter first number: ";
    std::cin >> number1;
    std::cout << "Enter second number: ";
    std::cin >> number2;
    std::cout << "Number1 + Number2: " << (number1 + number2) << std::endl;
    std::cout << "Number1 - Number2: " << (number1 - number2) << std::endl;
    std::cout << "Number1 * Number2: " << (number1 * number2) << std::endl;
    std::cout << "Number1: " << number1 << std::endl << "Number2: " << number2 << std::endl;
    std::cout << "Number1 == Number2: " << (number1 == number2) << std::endl;
    std::cout << "Number1 >= Number2: " << (number1 >= number2) << std::endl;
    std::cout << "Number1 <= Number2: " << (number1 <= number2) << std::endl;
    std::cout << "Number1 > Number2: " << (number1 > number2) << std::endl;
    std::cout << "Number1 < Number2: " << (number1 < number2) << std::endl;
    std::cout << "Number1 != Number2: " << (number1 != number2) << std::endl;
    std::cout << "Int(5) + Number1: " << (int(5) + number1) << std::endl;
    std::cout << "Int(5) - Number1: " << (int(5) - number1) << std::endl;
    std::cout << "Int(5) * Number1: " << (int(5) * number1) << std::endl;
    return 0;
}
