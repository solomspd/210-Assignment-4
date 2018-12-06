#pragma once
#include <string>

class suggestion
{
public:
	std::string word;
	int differ;
	bool compare(suggestion const & a, suggestion const & b)
	{
		return a.differ < b.differ;
	}
	suggestion();
	~suggestion();
};

