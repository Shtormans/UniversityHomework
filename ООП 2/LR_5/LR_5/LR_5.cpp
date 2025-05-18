#include <iostream>

#include "BookRepository.h"
#include "PublishingYearBookQuery.h"

int main()
{
    BookRepository repository;
    repository.load();

    BaseBookQuery* query = new PublishingYearBookQuery(222);

    for (const auto& book : repository.find(query))
    {
        std::cout << book.title << ' ' << book.author << ' ' << book.publish_year << '\n';
    }
}
