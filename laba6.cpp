#include <iostream>
#include <cstring>

#define MAX_LEN 300
#define BUFFER_SIZE (MAX_LEN + 1)

bool is_delimiter(char c, const char* delimiters) {
    return strchr(delimiters, c) != NULL;
}

bool is_strictly_increasing(const char* word_start, int len) {
    if (len <= 1) {
        return true;
    }
    for (int i = 1; i < len; ++i) {
        if (*(word_start + i) <= *(word_start + i - 1)) {
            return false;
        }
    }
    return true;
}

int main() {
    char text[BUFFER_SIZE];
    char delimiters[BUFFER_SIZE];
    char result[BUFFER_SIZE] = "";

    int max_found_len = 0;

    std::cout << "Enter a string (max " << MAX_LEN << " chars):" << std::endl;
    std::cin.getline(text, BUFFER_SIZE);

    std::cout << "Enter delimiter characters:" << std::endl;
    std::cin.getline(delimiters, BUFFER_SIZE);

    char* current_pos = text;

    while (*current_pos != '\0') {
        while (*current_pos != '\0' && is_delimiter(*current_pos, delimiters)) {
            current_pos++;
        }

        if (*current_pos == '\0') {
            break;
        }

        char* word_start = current_pos;
        while (*current_pos != '\0' && !is_delimiter(*current_pos, delimiters)) {
            current_pos++;
        }
        
        int word_len = current_pos - word_start;

        if (is_strictly_increasing(word_start, word_len)) {
            if (word_len > max_found_len) {
                max_found_len = word_len;
                strncpy(result, word_start, word_len);
                result[word_len] = '\0';
            } else if (word_len == max_found_len && max_found_len > 0) {
                strcat(result, " ");
                strncat(result, word_start, word_len);
            }
        }
    }

    if (max_found_len > 0) {
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cout << "It is impossible to solve the task." << std::endl;
    }

    return 0;
}