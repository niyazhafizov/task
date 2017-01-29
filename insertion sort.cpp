#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>

void insSort(std::vector<int>& vector) {
    for (size_t i = 1; i != vector.size(); ++i) {
        // Смотрим на элемент исходного массива
        int ensElem = vector[i];
        // Берем индекс, на 1 меньший, чтобы сравнить с предыдущим
        size_t j = i - 1;
        // Проверяем для самого первого элемента
        if (vector[0] < vector[1]) {
            int c = vector[0];
            vector[0] = vector[1];
            vector[1] = c;
        }
        // Проверяем с каждым предыдущим.
        while (j != 0 && vector[j] < ensElem) {
            // Если оказалось больше, то меняем местами с соседним
            vector[j + 1] = vector[j];
            j -= 1;
        }
        vector[j+1] = ensElem;
    }
}


int main() {
    std::vector<int> vector = {3,3,1,2,3,4,3,3};
    insSort(vector);
    for (auto elem : vector) {
        std::cout << elem;
    }
    return 0;
}
