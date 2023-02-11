#include <iostream>
#include <vector>
#include <algorithm>
class Student {
public:
	int age;
	char name [20];
	double GPA;
	int ID;
	void set_information() {
		std::cout << "Enter student ID number: "; std::cin >> ID;
		std::cout << "Enter student name: "; std::cin >> name;
		std::cout << "Enter student age: "; std::cin >> age;
		std::cout << "Enter student GPA: "; std::cin >> GPA;
	}
	void get_information()
	{
		std::cout << "Student ID number: "; std::cout <<  ID << std::endl;
		std::cout << "Student name: "; std::cout << name << std::endl;
		std::cout << "Student age: "; std::cout << age << std::endl;
		std::cout << "Student GPA: "; std::cout << GPA << std::endl;
	}
};

std::ostream& operator << (std::ostream& os, const Student& p)
{
	return os << "ID: " << p.ID << "\tName: " << p.name << "\tAge: " << p.age << "\tGPA: " << p.GPA << std::endl;
}


void User_interface(std::vector<Student>& Students, Student &Student);


int main()
{
	std::vector<Student> Students;
	std::vector<Student>::iterator iter;
	Student St;
	User_interface(Students, St);
	return 0;
}


void User_interface(std::vector<Student> & Students, Student &St)
{
	enum User_choice { ADD = 1, DELETE = 2, VIEW = 3, FIND = 4 };
	int choice = 0;
	int ID;
	do {
		std::cin.exceptions(std::ios_base::failbit);
		try
		{
			std::cout << "Choose an action: \n";
			std::cout << "1 - Add student\n"
				<< "2 - Delete student\n"
				<< "3 - Display information about students\n"
				<< "4 - Find a student\n"
				<< "5 - Exit\n";
			std::cin >> choice;
		}
		catch (const std::exception& ex)
		{
			std::cout << "Invalid input. Re-enter\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}
		switch (choice)
		{
		case ADD:
			St.set_information();
			Students.push_back(St);
			break;
		case DELETE:
		{

			std::cout << "Enter student ID number: "; std::cin >> ID;
			auto result = Students.erase(remove_if(Students.begin(), Students.end(), [ID](Student& st) {
				return st.ID == ID;
				}), Students.end());
			if (result == Students.end())
			{
				std::cout << "Student not found\n";
			}
			else
			{
				std::cout << "Student information removed\n";
			}
			break;
		}
		case VIEW:
		{
			std::cout << "Information about students:\n";
			sort(Students.begin(), Students.end(), [](const Student& student1, const Student& student2)
				{
					return student1.ID < student2.ID;
				});
			for (auto i = Students.begin(); i != Students.end(); i++)
			{
				std::cout << *i;
			}
			break;
		}
		case FIND:
		{
			std::cout << "Enter student ID number: "; std::cin >> ID;
			auto result = find_if(Students.begin(), Students.end(), [ID](Student& st) {
				st.get_information();
				return st.ID == ID;
				});
			if (result == Students.end())
			{
				std::cout << "Student not found\n";
			}
			break;
		}
		}
	} while (choice != 5);
}