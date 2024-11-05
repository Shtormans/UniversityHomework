#include <iostream>
#include "Student.h";
#include "List.h";

List<Student*>* _students;

void PrepaireData();
void Run();

int ChooseAction();
void Add();
void Remove();
void Clear();
void ShowAll();
void ShowByGroupName();
void Show(List<Student*>* students);


int main()
{
    PrepaireData();
    Run();

    delete _students;
}

void PrepaireData()
{
    _students = new List<Student*>(true);
}

void Run()
{
    while (true)
    {
        int choice = ChooseAction();

        std::cout << "\n\n";

        switch (choice)
        {
        case 1:
            Add();
            break;
        case 2:
            Remove();
            break;
        case 3:
            Clear();
            break;
        case 4:
            ShowAll();
            break;
        case 5:
            ShowByGroupName();
            break;
        }

        std::cout << "\n\n";
    }
}

int ChooseAction()
{
    std::cout << "Make an action:" << std::endl;
    std::cout << " 1 - Add" << std::endl;
    std::cout << " 2 - Remove" << std::endl;
    std::cout << " 3 - Clear" << std::endl;
    std::cout << " 4 - Show all" << std::endl;
    std::cout << " 5 - Show by group name" << std::endl;

    int choice;
    std::cin >> choice;

    return choice;
}

void Add()
{
    std::string firstName;
    std::cout << "First name: ";
    std::cin >> firstName;

    std::string lastName;
    std::cout << "Last name: ";
    std::cin >> lastName;

    std::string groupName;
    std::cout << "Group: ";
    std::cin >> groupName;

    float averageMark;
    std::cout << "Average mark: ";
    std::cin >> averageMark;

    Student* student = new Student(firstName, lastName, groupName, averageMark);
    _students->Add(student);
}

void Remove()
{
    std::string firstName;
    std::cout << "First name: ";
    std::cin >> firstName;

    std::string lastName;
    std::cout << "Last name: ";
    std::cin >> lastName;
    
    Student* studentToDelete = new Student(firstName, lastName);
    _students->TryRemove(studentToDelete, [](Student* first, Student* second)
        {
            return first->CompareTo(second);
        });
}

void Clear()
{
    _students->Clear();
}

void ShowAll()
{
    Show(_students);
}

bool CheckStudentByGroup(Student* student, std::string groupName)
{
    return student->GetGroupName() == groupName;
}

void ShowByGroupName()
{
    std::string groupName;
    std::cout << "Group: ";
    std::cin >> groupName;

    std::cout << std::endl;

    List<Student*>* filteredStudents = _students->SelectWhere([groupName](Student* student)
        {
            return CheckStudentByGroup(student, groupName);
        });

    Show(filteredStudents);
}

void Show(List<Student*>* students)
{
    for (int i = 0; i < students->GetLength(); i++)
    {
        std::cout << students->operator[](i)->Serialize();
        std::cout << "\n";
    }
}