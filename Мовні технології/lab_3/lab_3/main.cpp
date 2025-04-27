#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "FiniteStateMachine.h"

const std::string InputFile = "file_in.txt";
const std::string OutputFile = "file_out.txt";

std::vector<std::string> readFromStream(std::stringstream& ss)
{
    std::string word;
    std::vector<std::string> words;
    while (ss >> word)
    {
        words.push_back(word);
    }

    return words;
	
}

std::vector<std::string> readFromFile()
{
    std::ifstream file(InputFile, std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "Can't read file.\n";
        return {};
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    return readFromStream(ss);
}

std::vector<std::string> readFromConsole()
{
    std::cin.ignore();

    std::cout << "Input words separated by spaces: ";
    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss;
    ss << input;

    return readFromStream(ss);
}

void output(const std::string& result)
{
    std::cout << result << '\n';

    std::ofstream outputFile(OutputFile);
    if (!outputFile.is_open())
    {
        std::cerr << "Couldn't create the output file" << '\n';
        return;
    }

    outputFile << result;
    outputFile.close();
}

int main()
{
    std::cout << "Select input mode:\n1. Keyboard\n2. File" << '\n';

    std::vector<std::string> words;

    int path;
    std::cin >> path;

    if (path == 1)
    {
        words = readFromConsole();
    }
    else
    {
        words = readFromFile();
    }

    FiniteStateMachine stateMachine;
    std::string result;

    for (const std::string& word : words)
    {
        result += word + ": " + (stateMachine.CheckTransitions(word) ? "MATCHES" : "DOESN'T MATCH") + "\n";
    }

    output(result);
    return 0;
}
