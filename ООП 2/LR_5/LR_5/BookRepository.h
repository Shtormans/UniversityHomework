#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "BaseBookQuery.h"
#include "Book.h"

#define FileName "library.txt"

class BookRepository
{
private:
	std::vector<Book> cashed_books_;

public:
    void save() const
    {
        std::ofstream file(FileName);
        if (!file.is_open()) return;

        for (const auto& book : cashed_books_) {
            file << book.title << '\t' << book.author << '\t' << book.publish_year << '\n';
        }

        file.close();
    }

    void load() {
        std::ifstream file(FileName);
        if (!file.is_open()) return;

        cashed_books_.clear();

        std::string line;
        while (std::getline(file, line)) 
        {
            std::istringstream iss(line);
            Book book;

            if (std::getline(iss, book.title, '\t') &&
                std::getline(iss, book.author, '\t') &&
                iss >> book.publish_year) 
            {
                cashed_books_.push_back(book);
            }
        }

        file.close();
    }

    void add_book(const Book& book)
    {
        cashed_books_.push_back(book);
        save();
    }

	std::vector<Book> find(BaseBookQuery* query)
	{
		std::vector<Book> filtered;

		std::copy_if(cashed_books_.begin(), cashed_books_.end(), std::back_inserter(filtered),
			[query](const Book& book) {
				return query->matches(book);
			});

		return filtered;
	}
};

