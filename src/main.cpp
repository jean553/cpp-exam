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

    /* store the whole file content into a string */
    std::string data(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    nlohmann::json jsonData = nlohmann::json::parse(data);

    return EXIT_SUCCESS;
}
