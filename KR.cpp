#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstring>

struct Student {
    char name[30];
    int group;
    double grade;
};

Student* resizeArray(Student* original, int oldSize, int newSize) {
    Student* newArray = new Student[newSize];
    for (int i = 0; i < std::min(oldSize, newSize); ++i) {
        newArray[i] = original[i];
    }
    delete[] original;
    return newArray;
}

Student* readStudentsFromFile(const std::string& filename, int& count) {
    Student* students = nullptr;
    count = 0;
    int capacity = 10;
    students = new Student[capacity];

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        delete[] students;
        return nullptr;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (count == capacity) {
            capacity *= 2;
            students = resizeArray(students, count, capacity);
        }

        Student s;
        size_t first_semicolon = line.find(';');
        if (first_semicolon == std::string::npos) continue;

        std::string name_str = line.substr(0, first_semicolon);
        strncpy(s.name, name_str.c_str(), sizeof(s.name) - 1);
        s.name[sizeof(s.name) - 1] = '\0';

        size_t second_semicolon = line.find(';', first_semicolon + 1);
        if (second_semicolon == std::string::npos) continue;

        try {
            s.group = std::stoi(line.substr(first_semicolon + 1, second_semicolon - (first_semicolon + 1)));
            s.grade = std::stod(line.substr(second_semicolon + 1));
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " (" << e.what() << ")" << std::endl;
            continue;
        }
        students[count++] = s;
    }
    file.close();

    if (count < capacity) {
        students = resizeArray(students, capacity, count);
    }
    return students;
}

void printStudents(const Student* students, int count) {
    if (count == 0 || students == nullptr) {
        std::cout << "No students to display." << std::endl;
        return;
    }
    std::cout << std::left << std::setw(25) << "Name"
              << std::setw(10) << "Group"
              << std::setw(10) << "Grade" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << std::left << std::setw(25) << students[i].name
                  << std::setw(10) << students[i].group
                  << std::setw(10) << std::fixed << std::setprecision(1) << students[i].grade << std::endl;
    }
    std::cout << std::endl;
}

void sortAndSaveByName(const Student* original_students, int count) {
    Student* students_copy = new Student[count];
    for (int i = 0; i < count; ++i) students_copy[i] = original_students[i];

    std::sort(students_copy, students_copy + count, [](const Student& a, const Student& b) {
        return std::string(a.name) < std::string(b.name);
    });

    std::ofstream outfile("sorted_by_name.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open output file for saving sorted data." << std::endl;
        delete[] students_copy;
        return;
    }

    for (int i = 0; i < count; ++i) {
        outfile << students_copy[i].name << ";" << students_copy[i].group << ";" << students_copy[i].grade << std::endl;
    }
    outfile.close();
    std::cout << "Students sorted by name and saved to 'sorted_by_name.txt'." << std::endl;
    std::cout << "Sorted students (preview):" << std::endl;
    printStudents(students_copy, count);
    delete[] students_copy;
}

void findStudentBySurname(const Student* students, int count) {
    std::string search_surname;
    std::cout << "Enter surname to search: ";
    std::cin.ignore();
    std::getline(std::cin, search_surname);

    bool found = false;
    for (int i = 0; i < count; ++i) {
        std::string full_name = students[i].name;
        size_t space_pos = full_name.find(' ');
        std::string current_surname = (space_pos == std::string::npos) ? full_name : full_name.substr(0, space_pos);

        if (current_surname == search_surname) {
            std::cout << "Student found:" << std::endl;
            std::cout << "Name: " << students[i].name << ", Group: " << students[i].group << ", Grade: " << std::fixed << std::setprecision(1) << students[i].grade << std::endl;
            found = true;
            break;
        }
    }
    if (!found) std::cout << "Student with surname '" << search_surname << "' not found." << std::endl;
}

void sortStudentsByGroupAndName(const Student* original_students, int count) {
    Student* students_copy = new Student[count];
    for (int i = 0; i < count; ++i) students_copy[i] = original_students[i];

    std::sort(students_copy, students_copy + count, [](const Student& a, const Student& b) {
        if (a.group != b.group) return a.group < b.group;
        return std::string(a.name) < std::string(b.name);
    });
    std::cout << "Students sorted by group, then by name:" << std::endl;
    printStudents(students_copy, count);
    delete[] students_copy;
}

void displayMenu() {
    std::cout << "\n--- Student Management System ---" << std::endl;
    std::cout << "1. Sort students by name and save to file" << std::endl;
    std::cout << "2. Find student by surname" << std::endl;
    std::cout << "3. Sort students by group, then by name" << std::endl;
    std::cout << "4. Report average grades by group" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    std::string filename = "students.txt";

    std::ofstream test_file(filename, std::ios::app);
    if (test_file.tellp() == 0) {
        test_file << "Иванов А.И.;1;7.5" << std::endl;
        test_file << "Петров В.В.;2;8.0" << std::endl;
        test_file << "Сидоров С.С.;1;6.8" << std::endl;
        test_file << "Кузнецов Д.А.;3;9.2" << std::endl;
        test_file << "Федорова Е.Л.;2;7.9" << std::endl;
        test_file << "Алексеев Р.М.;3;8.5" << std::endl;
    }
    test_file.close();

    int student_count = 0;
    Student* students = readStudentsFromFile(filename, student_count);

    if (students == nullptr || student_count == 0) {
        std::cerr << "No student data loaded. Exiting." << std::endl;
        return 1;
    }

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                sortAndSaveByName(students, student_count);
                break;
            case 2:
                findStudentBySurname(students, student_count);
                break;
            case 3:
                sortStudentsByGroupAndName(students, student_count);
                break;
            case 4:
                std::cout << "I have no more time";
                break;
            case 5:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 5);

    delete[] students;
    return 0;
}
