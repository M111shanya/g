#include <iostream>

void f(int* x) // Передача по указателю.
{
    *x *= 2;
}

void arrayFunc(int* arr, int len)
{
    for (int* ptr = arr; ptr < arr + len; ptr++) { // Вот такая вот реализация
        std::cout << *ptr << " ";
    }
}

int main()
{
    int i{};
    std::cout << &i; // Операция взятия адреса

    int* ptri = &i; // Указатель - хранит адрес другой переменной.

    char c = 'a';
    char* ptrchar = &c;
    *ptrchar = 'b'; // Операция разыменования
    std::cout << c;

    void* ptrvoid = &i; // Универсальный указатель - хранит адреса памяти с неизв. типом unuse

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < std::size(arr); i++) {
        std::cout << *(arr + i) << " ";
    }

    int* const hui = nullptr; // Константный указатель на int
    const int* huy = nullptr; // Указатель на const int;

    // arr++ записать нельзя так как arr - константный указатель.

    const char* str = "HUI"; // Массив символов через указатель. Просто массив так нельзя

    //Статическое выделение памяти
    int i;

    // Динамическое 
    int* ptr = new int; // int* ptr = new int; - выделяется динамическая память для одного целого числа
                        // (типа int) с помощью оператора new. Оператор new возвращает
                        // указатель на выделенную память, который сохраняется в переменной ptr.
    *ptr = 10;
    std::cout << *ptr;

    // Динамический массив
    int i;
    std::cin >> i;
    int* arr = new int[i];

    // Очиста памяти
    delete ptri;
    delete[] arr;

    int** ar = new int*[5]; // new int*[5] выделяет память под массив из 5 указателей на int.
                            // Каждый элемент этого массива (ar[0], ..., ar[4]) имеет тип int* (указатель на int).
                            //Возвращается указатель на первый элемент этого массива, который имеет тип int**
                            // (указатель на указатель на int).
    ar[0] = new int[10];
    ar[1] = new int[10];
    ar[2] = new int[10];
    ar[3] = new int[10];
    ar[4] = new int[10];

    return 0;
}