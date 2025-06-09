#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using std::cin;
using std::cout;
using std::string;

struct Book {
    string title;
    string author;
    int year;

};

bool isThereAWordInTheTitle(const string& word, const Book& book) {
    return book.title.find(word) != std::string::npos;

}

void getBookInfoByKeyboard(Book& book) {
    cout << "Enter title: ";
    std::getline(cin, book.title);

    cout << "Enter author: ";
    std::getline(cin, book.author);

    while (true) {
        cout << "Enter year: ";
        cin >> book.year;

        if (cin.fail()) {
            std::cout << "Invalid input. Please enter a valid integer for the year." << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
}

void writeBookToArray(Book* books, size_t size) {
    for (int i = 0; i < size; i++) {
        cout << "Enter info for book" << i + 1 << std::endl;
        getBookInfoByKeyboard(books[i]);
    }

}

void printArrayOfBooks(Book* books, size_t size) {
    for (int i = 0; i < size; i++) {
        cout << books[i].title << " " << books[i].author << " " << books[i].year << std::endl;
    }
}

int main() {
    Book book;
    size_t size{3};

    Book* books = new Book[size];

    writeBookToArray(books, size);
    printArrayOfBooks(books, size);

    delete[] books;

    return 0;

}