#include <iostream>

class safe_c_array_t {
public:
    int* adrr;
    int length = 0;

    long long get_length() {
        return length;
    };

    safe_c_array_t(int len) {
        length = len;
        adrr = new int[length];
    };

    void remove() {
        delete [] adrr;
    }

    int& operator[] (const int index);

    safe_c_array_t(safe_c_array_t& other_arr) {
        delete [] adrr;
        adrr = new int[other_arr.get_length()];
        length = other_arr.get_length();
        for (int i = 0; i < other_arr.get_length(); i++) {
            adrr[i] = other_arr[i];
        };
    };

};

int& safe_c_array_t::operator[] (const int index) {
    return adrr[index];
}

void show_array(safe_c_array_t& arr) {
    for (int i = 0; i < arr.get_length(); i++) {
        std::cout << arr[i] << ' ';
    };
}



int main() {
    safe_c_array_t arr_0(3);
    std::cout << arr_0.get_length() << std::endl;
    show_array(arr_0);
    std::cout << std::endl;
    arr_0[2] = 1;
    show_array(arr_0);
    std::cout << std::endl;

    safe_c_array_t arr_1 = arr_0;
    show_array(arr_1);

    return 0;
}