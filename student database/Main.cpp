#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
class Student {
public:
	int age;
	char name[20];
	double GPA;
	int ID;
public:
	void set_information() {
		std::cout << "Enter student ID number: "; std::cin >> ID;
		std::cout << "Enter student name: "; std::cin >> name;
		std::cout << "Enter student age: "; std::cin >> age;
		std::cout << "Enter student GPA: "; std::cin >> GPA;
	}
	void get_information()
	{
		std::cout << ID << "\t" << name << "\t" << age << "\t" << GPA << std::endl;
	}
	friend void user_interface(std::vector<Student>Students, Student& St);
};

void user_interface(std::vector<Student>Students, Student& St)
{
	enum USER_CHOICE { ADD = 1, DELETE = 2, VIEW = 3, FIND = 4 };
	int user_choice = 0;
	int find_ID;
	do {
		std::cin.exceptions(std::ios_base::failbit);
		try
		{
			std::cout << "Choice an action: \n"
				<< "1 - Add student\n"
				<< "2 - Delete student\n"
				<< "3 - Display information about student\n"
				<< "4 - Find a student\n"
				<< "5 - Exit\n"; std::cin >> user_choice;
			system("cls");
			switch (user_choice)
			{
			case ADD:
			{
				std::ofstream data_base_file;
				data_base_file.open("data_base.txt", std::ofstream::app);
				St.set_information();
				data_base_file.write((char*)&St, sizeof(Student));
				data_base_file.close();
				break;
			}

			case DELETE:
			{
				Students.clear();
				std::cout << "Enter student ID number: "; std::cin >> find_ID;
				std::ifstream in_data_base_file;
				in_data_base_file.open("data_base.txt");
				while (in_data_base_file.read((char*)&St, sizeof(Student)))
				{
					if (St.ID != find_ID)
					{
						Students.push_back(St);
					}
				}
				in_data_base_file.close();
				// Перезапись файла 
				std::ofstream out_data_base_file;
				out_data_base_file.open("data_base.txt");
				for (auto i = Students.begin(); i != Students.end(); i++)
				{
					out_data_base_file.write((char*)&(*i), sizeof(Student));
				}
				out_data_base_file.close();
				break;
			}
			case VIEW:
			{
				std::ifstream in_data_base_file;
				in_data_base_file.open("data_base.txt");
				std::cout << "ID" << "\t" << "Name" << "\t" << "Age" << "\t" << "GPA" << std::endl;
				while (in_data_base_file.read((char*)&St, sizeof(Student)))
				{
					St.get_information();
				}
				in_data_base_file.close();
				break;
			}
			case FIND:
			{
				std::cout << "Enter student ID to search: "; std::cin >> find_ID;
				std::ifstream in_data_base_file;
				in_data_base_file.open("data_base.txt");
				while (in_data_base_file.read((char*)&St, sizeof(Student)))
				{
					if (St.ID == find_ID)
					{
						std::cout << "ID" << "\t" << "Name" << "\t" << "Age" << "\t" << "GPA" << std::endl;
						St.get_information();
					}
				}
				in_data_base_file.close();
				break;
			}
			default:
				break;
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "Invalid input. Re-enter\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}
	} while (user_choice != 5);
}

int main()
{
	std::vector<Student>Students;
	Student St;
	user_interface(Students, St);
	return 0;
}
