#pragma once
#include "Book.h"

class BaseBookQuery
{
public:
	virtual bool matches(Book book) = 0;
};

