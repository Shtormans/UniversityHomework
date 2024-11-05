#pragma once

#include <iostream>
#include <string>

class Student
{
private:
	std::string _firstName;
	std::string _lastName;
	std::string _groupName;
	float _averageMark;

public:
	Student(std::string firstName, std::string lastName) : Student(firstName, lastName, "", 0)
	{

	}

	Student(std::string firstName, std::string lastName, std::string groupName, float averageMark)
	{
		_firstName = firstName;
		_lastName = lastName;
		_groupName = groupName;
		_averageMark = averageMark;
	}

	~Student()
	{
	}

	std::string GetFirstName()
	{
		return _firstName;
	}

	std::string GetLastName()
	{
		return _lastName;
	}

	std::string GetGroupName()
	{
		return _groupName;
	}

	float GetAverageMark()
	{
		return _averageMark;
	}

	std::string Serialize()
	{
		std::string firstNameOutput = "First name: " + _firstName;
		std::string lastNameOutput = "Last name: " + _lastName;
		std::string groupNameOutput = "Group: " + _groupName;
		std::string averageMarkOutput = "Average mark: " + std::to_string(_averageMark);

		std::string resultString;
		resultString.reserve(50);

		resultString += firstNameOutput;
		resultString += "\n";
		resultString += lastNameOutput;
		resultString += "\n";
		resultString += groupNameOutput;
		resultString += "\n";
		resultString += averageMarkOutput;
		resultString += "\n";

		return resultString;
	}

	bool CompareTo(Student* other)
	{
		return _firstName == other->_firstName
			&& _lastName == other->_lastName;
	}

	bool operator==(Student* other)
	{
		return CompareTo(other);
	}
};

