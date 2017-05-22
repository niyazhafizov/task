#include <iostream>
#include <vector>

void test(size_t t, size_t n, std::vector<size_t>& array) {
    std::vector<size_t> solver(t + 1); // массив, в котором я храню последнее слагаемое в разложении числа
    for (size_t i = 0; i != n && array[i] <= t; ++i) {
        solver[array[i]] = array[i]; // инициализирую подходящие элементы
    }
    for (size_t i = 0; i != n; ++i) {
        size_t sum = array[i]; // sum - число, которое является слагаемым в разложении
        for (size_t k = t; k != sum; --k) {
            if (solver[k] == 0 && solver[k - sum] != 0) // если k-ое число 0, значит пока мы это число не получили суммой
                // и если k - sum не 0, значит k можно получить прибавлением sum, тогда оно последнее число в разложении k
                solver[k] = sum;
        }
    }
    if (solver[t])
        std::cout << "YES\n";
    else
        std::cout << "NO\n";
}

int main() {
//    size_t t = 0; // число, которое необходимо представить в виде суммы
//    std::cin >> t;
//    size_t n = 0;
//    std::cin >> n; // количество вводимых положительных чисел
//    std::vector<size_t> array(n); // массив, в котором хранятся введенные числа
//    for (size_t i = 0; i != n; ++i)
//        std::cin >> array[i];
    size_t t = 7;
    size_t n = 3;
    std::vector<size_t> array = {1, 2, 4};
    std::cout << "ANSWER: YES\n";
    test(t, n, array);
    t = 7;
    n = 4;
    array.clear();
    array = {1, 1, 1, 1};
    std::cout << "ANSWER: NO\n";
    test(t, n, array);
    t = 7;
    n = 7;
    array.clear();
    array = {1, 1, 1, 1, 1, 1, 1};
    std::cout << "ANSWER: YES\n";
    test(t, n, array);
    t = 7;
    n = 3;
    array.clear();
    array = {0, 0, 0};
    std::cout << "ANSWER: NO\n";
    test(t, n, array);
}
