#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>

int** createMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, int size) {
    std::cout << "\nMatrix:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void solveProblem1() {
    int size;
    std::cout << "Enter the size of the square matrix: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Error: Matrix size must be positive." << std::endl;
        return;
    }

    int** matrix = createMatrix(size);

    int choice;
    std::cout << "Choose filling method (1 - Keyboard, 2 - Random): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter matrix elements:\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cin >> matrix[i][j];
            }
        }
    } else {
        int min_val, max_val;
        std::cout << "Enter the range for random numbers (min max): ";
        std::cin >> min_val >> max_val;
        srand(time(0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = min_val + rand() % (max_val - min_val + 1);
            }
        }
    }

    printMatrix(matrix, size);

    int max_in_non_positive_cols = INT_MIN;
    bool found_valid_column = false;

    for (int j = 0; j < size; ++j) {
        bool has_positive = false;
        for (int i = 0; i < size; ++i) {
            if (matrix[i][j] > 0) {
                has_positive = true;
                break;
            }
        }

        if (!has_positive) {
            found_valid_column = true;
            int current_col_max = matrix[0][j];
            for (int i = 1; i < size; ++i) {
                if (matrix[i][j] > current_col_max) {
                    current_col_max = matrix[i][j];
                }
            }
            if (current_col_max > max_in_non_positive_cols) {
                max_in_non_positive_cols = current_col_max;
            }
        }
    }

    std::cout << "\n--- Results for Problem 1 ---" << std::endl;
    if (found_valid_column) {
        std::cout << "Max element in columns with no positive elements: " << max_in_non_positive_cols << std::endl;
    } else {
        std::cout << "Couldn't find max element: No columns without positive elements found." << std::endl;
    }

    int negative_count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i + j >= size - 1) {
                if (matrix[i][j] < 0) {
                    negative_count++;
                }
            }
        }
    }
    std::cout << "Number of negative elements in the lower-right triangle: " << negative_count << std::endl;

    deleteMatrix(matrix, size);
}

void solveProblem2() {
    int size;
    std::cout << "Enter the size of the square matrix: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Error: Matrix size must be positive." << std::endl;
        return;
    }

    int** matrix = createMatrix(size);

    int choice;
    std::cout << "Choose filling method (1 - Keyboard, 2 - Random): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter matrix elements:\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cin >> matrix[i][j];
            }
        }
    } else {
        int min_val, max_val;
        std::cout << "Enter the range for random numbers (min max): ";
        std::cin >> min_val >> max_val;
        srand(time(0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = min_val + rand() % (max_val - min_val + 1);
            }
        }
    }

    printMatrix(matrix, size);

    std::cout << "\n--- Results for Problem 2 ---" << std::endl;
    std::cout << "Sums of elements on diagonals parallel to the main one:" << std::endl;

    for (int k = size - 1; k >= 0; --k) {
        long long current_sum = 0;
        for (int i = 0; i < size - k; ++i) {
            current_sum += matrix[i][i + k];
        }
        std::cout << "Diagonal (offset " << k << "): " << current_sum << std::endl;
    }

    for (int k = 1; k < size; ++k) {
        long long current_sum = 0;
        for (int i = 0; i < size - k; ++i) {
            current_sum += matrix[i + k][i];
        }
        std::cout << "Diagonal (offset -" << k << "): " << current_sum << std::endl;
    }

    int first_non_negative_row = -1;
    for (int i = 0; i < size; ++i) {
        bool has_negative = false;
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] < 0) {
                has_negative = true;
                break;
            }
        }
        if (!has_negative) {
            first_non_negative_row = i + 1;
            break;
        }
    }

    if (first_non_negative_row != -1) {
        std::cout << "Number of the first row with no negative elements: " << first_non_negative_row << std::endl;
    } else {
        std::cout << "Couldn't find such row: All rows contain negative elements." << std::endl;
    }

    deleteMatrix(matrix, size);
}

int main() {
    int problem_choice;
    std::cout << "Which problem to solve (1 or 2)? ";
    std::cin >> problem_choice;

    if (problem_choice == 1) {
        solveProblem1();
    } else if (problem_choice == 2) {
        solveProblem2();
    } else {
        std::cout << "Invalid choice." << std::endl;
    }
    
    return 0;
}