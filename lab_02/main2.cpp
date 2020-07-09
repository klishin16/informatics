#include <iostream>

class safe_c_array_t {
public:
    int* adrr = nullptr;
    int length = 0;

    long long get_length() {
        return length;
    };

    explicit safe_c_array_t(int len) {
        length = len;
        adrr = new int[length];
        for (int i = 0; i < length; i++) {
            adrr[i] = 0;
        }
    };

    void remove() {
        delete [] adrr;
    }

    safe_c_array_t(safe_c_array_t& other_arr) {
        if (adrr != nullptr) {
            delete [] adrr;
        }
        adrr = new int[other_arr.get_length()];
        length = other_arr.get_length();
        for (int i = 0; i < other_arr.get_length(); i++) {
            adrr[i] = other_arr[i];
        };
    };
    int& operator[] (int index) const;
    safe_c_array_t& operator=(safe_c_array_t &other);
    friend std::ostream &operator<< (std::ostream &out, safe_c_array_t array);
};

int& safe_c_array_t::operator[] (const int index) const {
    return adrr[index];
}

safe_c_array_t &safe_c_array_t::operator=(safe_c_array_t &other) {
    delete [] adrr;
    adrr = new int[other.length];
    for(int i = 0; i < other.length; i++) {
        adrr[i] = other[i];
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, safe_c_array_t array) {
    for (int i = 0; i < array.length; i++) {
        out << array[i] << ' ';
    }
    out << std::endl;
    return out;
}

int main() {
    safe_c_array_t arr_0(3);
    std::cout << "Array arr_0 length: " << arr_0.get_length() << std::endl;
    std::cout << arr_0;
    arr_0[2] = 1;
    std::cout << arr_0;

    safe_c_array_t arr_1 = arr_0;
    std::cout << arr_1;

    safe_c_array_t arr_2(3);
    arr_2 = arr_1;
    std::cout << arr_2;

    return 0;
}
