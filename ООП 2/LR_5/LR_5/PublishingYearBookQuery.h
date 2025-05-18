#pragma once
#include "BaseBookQuery.h"

class PublishingYearBookQuery : public BaseBookQuery
{
	int year_;

public:
	PublishingYearBookQuery(const int year)
	{
		year_ = year;
	}

	bool matches(const Book book) override
	{
		return book.publish_year == year_;
	}
};

