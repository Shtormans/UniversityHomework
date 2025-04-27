#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include <windows.h>

const std::string InputFile = "file_in.txt";
const std::string OutputFile = "file_out.txt";
const std::string vowels = "aeiouAEIOU";

std::string read() {
	std::ifstream file(InputFile, std::ios::binary);

	if (!file.is_open())
	{
		return "";
	}

	std::ostringstream buffer;
	buffer << file.rdbuf();
	std::string text = buffer.str();

	return text;
}

void write(const std::string& data) {
	std::ofstream file(OutputFile, std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	file.write(data.c_str(), data.size());
}

bool is_vowel(const char character) {
	return vowels.find(character) != std::string::npos;
}

std::vector<std::string> split_words(const std::string& text)
{
	std::vector<std::string> words;
	std::string current;

	for (const char character : text)
	{
		if (std::isalpha(character))
		{
			current += character;
		}
		else if (!current.empty())
		{
			words.push_back(current);
			current.clear();
		}
	}

	if (!current.empty())
	{
		words.push_back(current);
	}

	return words;
}

int max_consonant_sequence(const std::string& word)
{
	int max_length = 0;
	int current_length = 0;

	for (const char character : word)
	{
		if (!is_vowel(character))
		{
			current_length++;
			max_length = max(max_length, current_length);
		}
		else
		{
			current_length = 0;
		}
	}

	return max_length;
}

int main()
{
	const std::string text = read();

	if (text.empty())
	{
		std::cout << "Can't read file.\n";
		return 1;
	}

	auto words = split_words(text);
	if (words.empty())
	{
		std::cout << "File has no words.\n";
		return 0;
	}

	std::vector<std::pair<std::string, int>> results;
	for (const auto& word : words)
	{
		int length = max_consonant_sequence(word);

		if (length > 0)
		{
			results.emplace_back(word, length);
		}
	}

	if (results.empty())
	{
		std::cout << "There are no needed words\n";
		return 0;
	}

	std::sort(results.begin(), results.end(), [](const auto& a, const auto& b)
		{
			return a.second > b.second;
		});

	std::string result = "";
	int count = 0;

	for (const auto& data : results)
	{
		count++;
		if (count > 15)
		{
			break;
		}

		result += data.first + " (length: " + std::to_string(data.second) + ")\n";
	}

	std::cout << result;
	write(result);

	return 0;
}