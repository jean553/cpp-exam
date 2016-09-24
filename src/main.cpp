#include "json.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>

int main()
{
    std::ifstream file("../data.json");

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

    return EXIT_SUCCESS;
}
