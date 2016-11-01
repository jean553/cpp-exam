#include "json.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>

/**
 * @brief remove the quotes (") from given string
 *
 * @param str reference to the concerned string
 *
 * @throw std::bad_alloc memory error
 * @throw std::terminate error occured in the called sub-functions
 * algorithms
 * @throw std::out_of_range error concerning the given positions
 *
 * str reference is not 'const', because we modify
 * the referred string
 */
void removeDoubleQuotes(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
}

/**
 * @brief read a list of files and record their content inside a given
 * referenced string
 *
 * @param files list of files
 * @param json non constant reference of string to update
 *
 * @throw std::invalid_argument a file couldn't be opened
 *
 * we use a function template walk-around as the array size might change; this
 * method is the well-known way to deduce an std::array size using templates
 */
template<std::size_t S>
void loadAllFiles(
    const std::array<std::string, S>& files,
    std::string& json
)
{
    json = "[";

    for(auto& path : files)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::invalid_argument("Cannot open file");
        }

        /* store the whole file content into a string, call the std::string
           constructor: string(InputIterator first, InputIterator last);
           std::istreambuf_iterator<char>(file) reads each character one by one
           from the input stream until it reaches the value indicated by the
           second parameter (std::istreambuf_iterator<char>()), which is equal
           to an iterator using the default constructor; istreambuf_iterator is
           in this states when reading a file and reaching the end of this file
        */
        std::string data(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        json += data;

        /* normally optional but I prefer add it here as we are in a loop */
        file.close();
    }

    json += "]";
}

int main()
{
    std::string data;

    /* TODO: use the experimental method std::experimental::make_array() ? */
    const std::array<std::string, 5> files = {
        "template_types_deduction_references.json",
        "template_types_deduction_constant_references.json",
        "template_types_deduction_pointers.json",
        "template_types_deduction_constant_pointers.json",
        "template_types_deduction_universal_references.json"
    };

    loadAllFiles(
        files,
        data
    );

    nlohmann::json jsonData = nlohmann::json::parse(data);

    std::string answer;
    unsigned short mark {0}, total {0};

    constexpr char BOLD_WHITE[] {"\033[1m\033[37m"};
    constexpr char GREEN[] {"\033[32m"};
    constexpr char RED[] {"\033[31m"};
    constexpr char RESET[] {"\033[0m"};

    for (auto& question : jsonData)
    {
        std::string strQuestion = question["question"];
        std::string strCode = question["code"];
        std::string strA = question["a"];
        std::string strB = question["b"];
        std::string strC = question["c"];
        std::string strD = question["d"];

        removeDoubleQuotes(strQuestion);
        removeDoubleQuotes(strCode);
        removeDoubleQuotes(strA);
        removeDoubleQuotes(strB);
        removeDoubleQuotes(strC);
        removeDoubleQuotes(strD);

        std::cout << std::endl << std::endl;
        std::cout << BOLD_WHITE << strQuestion << RESET;
        std::cout << std::endl << std::endl;
        std::cout << strCode << std::endl << std::endl;
        std::cout << BOLD_WHITE << "A: " << strA << RESET << std::endl;
        std::cout << BOLD_WHITE << "B: " << strB << RESET << std::endl;
        std::cout << BOLD_WHITE << "C: " << strC << RESET << std::endl;
        std::cout << BOLD_WHITE << "D: " << strD << RESET << std::endl;
        std::cout << "Your answer: ";
        std::cin >> answer;

        std::cout << std::endl << std::endl;

        if (answer == question["answer"])
        {
            std::cout << GREEN << "Correct !" << RESET;

            mark++;
        }
        else
        {
            std::cout << RED << "Wrong !" << RESET;
        }

        total++;
    }

    std::cout << std::endl << std::endl << "Mark: " << mark << " / " << total;

    return EXIT_SUCCESS;
}
