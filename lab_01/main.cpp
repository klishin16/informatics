#include <windows.h>


#include <iostream>

float func(float n){
    return -n*std::log(n);
    //return std::sqrt(n);
    //return -(n*n) - 0.5;
};

void showPlot(char** array, int height, int columns) {
    for (int j = height; j >= 0; j--) {
        if (height - j < 9) {
            std::cout<<"0"<<height - j + 1;
        } else {
            std::cout<<height - j + 1;
        }
        for (int i = 0; i < columns; i++) {
            std::cout<< array[i][j];
        }
        std::cout<<std::endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int columns = 0;
    int height = 0;
    float x0 = 0.0;
    float x1 = 0.0;
    std::cout << "Введите количество столбиков: " << std::endl;
    std::cin >> columns;
    std::cout << "Введите высоту: " << std::endl;
    std::cin >> height;
    std::cout << "Введите x0: " << std::endl;
    std::cin >> x0;
    std::cout << "Введите x1: " << std::endl;
    std::cin >> x1;

    char **map = new char *[columns];

    float incremX = (x1 - x0) / columns;

    float n = x0;
    float maxV = -1000.0;
    float minV = 1000.0;

    for (int i = 0; i < columns; i++) {
        n += incremX;
        if (func(n) > maxV) {
            maxV = func(n);
        };
        if (func(n) < minV) {
            minV = func(n);
        };
    };
    minV = min(minV, 0);
    maxV = max(maxV, 0);
    float incremY = (maxV - minV) / (height);

    n = x0;
    int cout = 0;
    for (int i = 0; i < columns; i++) {
        float y = minV + incremY;
        bool flag = false;
        char *column = new char [height + 1];
        for (int j = 0; j < height + 1; j++) {

            if ((y >= 0) && !flag) {
                column[j] = '-';
                flag = true;
                continue;
            }
            if (y >= 0) {
                if ((func(n) > y) || fabs(func(n) - y) < 1e-6) {
                    column[j] = '#';
                }
                else {
                    column[j] = ' ';
                }
            } else {
                if ((func(n) > y) || fabs(func(n) - y) < 1e-6) {
                    column[j] = ' ';
                }
                else {
                    column[j] = '#';
                }
            }
            y += incremY;
        }
        map[i] = column;
        n += incremX;
    }
    showPlot(map, height, columns);
    return 0;
}