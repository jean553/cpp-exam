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

int main()
{
    constexpr char FILE_PATH[] {"data.json"};
    constexpr char SEPARATOR[] {"-------------------------------------"};

    std::ifstream file(FILE_PATH);

    if (!file.is_open())
    {
        std::cerr << "Cannot open the data file!";
        return EXIT_FAILURE;
    }

    /* store the whole file content into a string, call the std::string
       constructor: string(InputIterator first, InputIterator last);
       std::istreambuf_iterator<char>(file) reads each character one by one
       from the input stream until it reaches the value indicated by the
       second parameter (std::istreambuf_iterator<char>()), which is equal to
       an iterator using the default constructor; istreambuf_iterator is in
       this states when reading a file and reaching the end of this file */
    std::string data(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    nlohmann::json jsonData = nlohmann::json::parse(data);

    std::string answer;
    unsigned short mark {0};

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

        std::cout << std::endl << std::endl << strQuestion << std::endl;
        std::cout << SEPARATOR << std::endl;
        std::cout << strCode << std::endl;
        std::cout << SEPARATOR << std::endl << std::endl;
        std::cout << "A: " << strA << std::endl;
        std::cout << "B: " << strB << std::endl;
        std::cout << "C: " << strC << std::endl;
        std::cout << "D: " << strD << std::endl << std::endl;
        std::cout << "Your answer: ";
        std::cin >> answer;

        if (answer == question["answer"])
        {
            mark++;
        }
    }

    std::cout << "Mark: " << mark;

    return EXIT_SUCCESS;
}
