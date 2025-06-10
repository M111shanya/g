#include <iostream>
#include <string>
#include <stdexcept>

std::string findLongestWords(const std::string& text, const std::string& delimiters) {
    std::string longest_words;
    size_t max_length = 0;
    
    std::string::size_type current_pos = 0;

    while ((current_pos = text.find_first_not_of(delimiters, current_pos)) != std::string::npos) {
        std::string::size_type end_pos = text.find_first_of(delimiters, current_pos);

        std::string current_word = (end_pos == std::string::npos)
                                  ? text.substr(current_pos)
                                  : text.substr(current_pos, end_pos - current_pos);
        
        if (current_word.length() > max_length) {
            max_length = current_word.length();
            longest_words = current_word;
        } else if (current_word.length() == max_length) {
            longest_words += " " + current_word;
        }

        if (end_pos == std::string::npos) {
            break;
        }
        current_pos = end_pos;
    }

    if (longest_words.empty()) {
        throw std::runtime_error("Task cannot be completed: no words found in the string.");
    }

    return longest_words;
}

int main() {
    std::string text;
    std::string delimiters;

    std::cout << "Enter a string to analyze:" << std::endl;
    getline(std::cin, text);

    std::cout << "Enter delimiter characters (e.g., .,!?):" << std::endl;
    getline(std::cin, delimiters);
    
    delimiters += " "; 

    try {
        std::string result = findLongestWords(text, delimiters);
        std::cout << "The longest word(s): " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}