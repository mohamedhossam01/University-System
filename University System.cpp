#include <bits/stdc++.h>
#define Go ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
#define all(x) x.begin(),x.end()
#define file ifstream cin ("input.txt");ofstream cout("output.txt")
#define vi vector<int>
using namespace std;
typedef long long ll;
string getstring(string& curr);
void Main_Menu();
void Student_Menu();
void Professor_Menu();
string num(string& curr);
struct student;
struct professor;
map<string, student> students;
map<string, professor> professors;
int main()
{
	Go;
	Main_Menu();
	cout << "Thanks for using our software.\n";
	system("pause");
}
struct student
{
	string name;
	string major;
	string year;
	map<string, double> grades;
	void display(student x)
	{
		cout << "\t\t\t****************\n";
		cout << "Student   Name: " << x.name << endl;
		cout << "Student   Year: " << x.year << endl;
		cout << "Student  Major: " << x.major << endl;
		cout << "Student Grades: " << endl;
		for (auto y : x.grades)
		{
			if (y.second == -1)
				cout << y.first << " : " << "Student has not taken the exam yet.\n";
			else cout << y.first << " : " << y.second << endl;
		}
		cout << "\t\t\t****************\n";
	}
	void add()
	{
		string curr;
		student temp;
		string id;
		while (1)
		{
			cout << "Enter ID: ";
			cin >> curr;
			num(curr);
			id = curr;
			if (students.count(id))
			{
				cout << "ID already exists.\n";
				display(students[id]);
				cout << "Would you like to overwrite current data ?(Y/N)\n";
				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y')
					break;
				else
					continue;
			}
			else break;
		}

		curr.clear();
		cout << "Enter Full Name: ";
		temp.name = getstring(curr);
		cout << "Enter Major: ";
		temp.major = getstring(curr);
		cout << "Enter Year: ";
		temp.year = getstring(curr);
		cout << "Enter Course Name (enter -1 to stop entering courses): ";
		string course;
		course = getstring(course);
		while (course != "-1")
		{
			cout << "Has the student taken an exam for this course? (Y/N):";
			char choice;
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				cout << "Enter grade as a floating number from 0 to 100:";
				string num;
				cin >> num;
				bool good = 0;
				while (!good)
				{
					good = 1;
					for (auto x : num)
					{
						if (x - '0' > 9 || x - '0' < 0)
						{
							if (x == '.')continue;
							good = 0;
							break;
						}
					}
					if (good)
					{
						double test = stod(num);
						if (!(test >= 0.0 && test <= 100.0))
						{
							cout << "Grade should be in range from 0 to 100\nEnter a valid Grade:";
							getstring(num);
							continue;
						}
					}
					if (!good)
					{
						cout << "Grade must consist of numbers only.\nPlease enter a valid Grade (ex: 88.7 and 93 are accepted while 91.3% and 84,5 are not): ";
						getstring(num);
					}
				}
				temp.grades[course] = stod(num);
			}
			else if (choice == 'N' || choice == 'n')
				temp.grades[course] = -1;
			else
			{
				cout << "Enter a valid character Y or N\n";
				continue;
			}
			cout << "Enter Course Name (enter -1 to stop entering courses): ";
			getstring(course);
		}
		students[id] = temp;
	}
	string find()
	{
		string id;
		while (1)
		{
			cout << "Enter Student ID: ";
			cin >> id;
			num(id);
			if (students.count(id))
			{
				while (1)
				{
					cout << "Student found. Would you like to display data? (Y/N): ";
					char choice;
					cin >> choice;
					if (choice == 'Y' || choice == 'y')display(students[id]);
					else if (choice == 'N' || choice == 'n');
					else continue;
					break;
				}
			}
			else
			{
				cout << "Student not found.\n";
				id.clear();
			}
			cout << "Make another search? (Y/N): ";
			char choice;
			cin >> choice;
			if (choice == 'Y' || choice == 'y')continue;
			else break;
		}
		return id;
	}
	void modify()
	{
		string id = find();
		if (!id.empty())
		{
			int i = 0;
			bool done = 0;
			while (!done)
			{
				cout << "Which data would you like to modify?\n";
				cout << "1.    ID\n";
				cout << "2.  Name\n";
				cout << "3.  Year\n";
				cout << "4.  Major\n";
				cout << "5. Grades\n";
				cout << "6. Go Back\n";
				cout << "Enter a choice: ";
				int choice;
				cin >> choice;
				if (choice > 6 || choice < 1)
				{
					cout << "Invalid Input.";
					continue;
				}
				string change, temp;
				double newgrade;
				switch (choice)
				{
				case 1:
					cout << "Enter New ID\n";
					getstring(change);
					num(change);
					students[change] = students[id];
					students.erase(id);
					break;
				case 2:
					cout << "Enter New Name\n";
					getstring(change);
					students[id].name = change;
					break;
				case 3:
					cout << "Enter New Year\n";
					getstring(change);
					students[id].year = change;
					break;
				case 4:
					cout << "Enter New Major\n";
					getstring(change);
					students[id].major = change;
					break;
				case 5:
					cout << "Which grade would you like to change?\n";
					cout << "Student Courses: \n\n";
					for (auto x : students[id].grades)
					{
						cout << x.first << endl;
					}
					cout << endl;
					while (1)
					{
						cout << "Enter Course Name: ";
						getstring(change);
						if (!students[id].grades.count(change))
						{
							cout << "Student doesn't have this course. Would you like to add it instead? (Y/N): ";
							char c;
							cin >> c;
							if (c == 'Y' || c == 'y')
							{
								cout << "Has the student taken an exam for this course? (Y/N):";
								char choice;
								cin >> choice;
								if (choice == 'Y' || choice == 'y')
								{
									cout << "Enter grade as a floating number from 0 to 100:";
									string num;
									cin >> num;
									bool good = 0;
									while (!good)
									{
										good = 1;
										for (auto x : num)
										{
											if (x - '0' > 9 || x - '0' < 0)
											{
												if (x == '.')continue;
												good = 0;
												break;
											}
										}
										if (good)
										{
											double test = stod(num);
											if (!(test >= 0.0 && test <= 100.0))
											{
												cout << "Grade should be in range from 0 to 100\nEnter a valid Grade:";
												getstring(num);
												continue;
											}
										}
										if (!good)
										{
											cout << "Grade must consist of numbers only.\nPlease enter a valid Grade (ex: 88.7 and 93 are accepted while 91.3% and 84,5 are not): ";
											getstring(num);
										}
									}
									students[id].grades[change] = stod(num);
									return;
								}
								else if (choice == 'N' || choice == 'n')
								{
									students[id].grades[change] = -1;
									return;
								}

								else
								{
									cout << "Enter a valid character Y or N\n";
									continue;
								}

							}
							else return;
						}
						else break;
					}
					cout << "Enter New Grade: ";
					getstring(temp);
					num(temp);
					newgrade = stod(temp);
					students[id].grades[change] = newgrade;
					break;
				case 6:
					done = 1;
					break;
				}
			}
		}
	}
	void list()
	{
		cout << "Number of Recorded Students: " << students.size() << endl << endl;
		for (auto x : students)
		{
			cout << "\t\t\tStudent ID: " << x.first << endl;
			display(x.second);
			cout << endl << endl;
		}
	}
};
struct professor
{
	string name;
	set<string> courses;
	void display(professor x)
	{
		cout << "\t\t\t********\n";
		cout << "Professor   Name: " << x.name << endl;
		cout << "Professor Course: " << endl;
		for (auto y : x.courses)
			cout << y << endl;
		cout << "\t\t\t********\n";
	}
	void add()
	{
		string curr;
		professor temp;
		string id;
		while (1)
		{
			cout << "Enter ID: ";
			cin >> curr;
			num(curr);
			id = curr;
			if (professors.count(id))
			{
				cout << "ID already exists.\n";
				display(professors[id]);
				cout << "Would you like to overwrite current data ?(Y/N)\n";
				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y')
					break;
				else
					continue;
			}
			else break;
		}
		curr.clear();
		cout << "Enter Full Name: ";
		temp.name = getstring(curr);
		cout << "Enter Course Name (enter -1 to stop entering courses): ";
		string course;
		course = getstring(course);
		if (course != "-1")temp.courses.insert(course);
		while (course != "-1")
		{
			cout << "Enter Course Name (enter -1 to stop entering courses): ";
			getstring(course);
			if (course == "-1")break;
			temp.courses.insert(course);
		}
		professors[id] = temp;
	}
	string find()
	{
		string id;
		while (1)
		{
			cout << "Enter Professor ID: ";
			cin >> id;
			num(id);
			if (professors.count(id))
			{
				while (1)
				{
					cout << "Professor found. Would you like to display data? (Y/N): ";
					char choice;
					cin >> choice;
					if (choice == 'Y' || choice == 'y')display(professors[id]);
					else if (choice == 'N' || choice == 'n');
					else continue;
					break;
				}
			}
			else
			{
				cout << "Professor not found.\n";
				id.clear();
			}
			cout << "Make another search? (Y/N): ";
			char choice;
			cin >> choice;
			if (choice == 'Y' || choice == 'y')continue;
			else break;
		}
		return id;
	}
	void modify()
	{
		string id = find();
		if (!id.empty())
		{
			bool done = 0;
			while (!done)
			{
				char c;
				cout << "Which data would you like to modify?\n";
				cout << "1.      ID\n";
				cout << "2.    Name\n";
				cout << "3. Courses\n";
				cout << "4. Go Back\n";
				cout << "Enter a choice: ";
				int choice;
				cin >> choice;
				if (choice > 4 || choice < 1)
				{
					cout << "Invalid Input.";
					continue;
				}
				string change, temp;
				switch (choice)
				{
				case 1:
					cout << "Enter New ID\n";
					getstring(change);
					num(change);
					professors[change] = professors[id];
					professors.erase(id);
					break;
				case 2:
					cout << "Enter New Name\n";
					getstring(change);
					professors[id].name = change;
					break;
				case 3:
					cout << "Which course would you like to change?\n\n";
					for (auto x : professors[id].courses)
						cout << x << endl;
					cout << endl;
					while (1)
					{
						cout << "Enter Course Name :";
						getstring(change);
						if (professors[id].courses.find(change) != professors[id].courses.end())
							break;
						cout << "Professor does not teach this course.\nWould you like to add it? (Y/N): ";
						cin >> c;
						if (c == 'Y' || c == 'y')
						{
							professors[id].courses.insert(change);
							return;
						}
						else break;
					}
					cout << "Enter New Course: ";
					getstring(temp);
					professors[id].courses.erase(change);
					professors[id].courses.insert(temp);
					break;
				case 4:
					done = 1;
					break;
				}
			}
		}
	}
	void list()
	{
		cout << "Number of Recorded Professors" << professors.size() << endl;
		for (auto x : professors)
		{
			cout << "\t\t\tProfessor ID" << x.first << endl;
			display(x.second);
			cout << endl;
		}
	}
};
void Main_Menu()
{
	cout << "\t\t\t***** UNIVERSITY DATABASE MANAGEMENT SYSTEM *****\n\n";
	cout << "\t\t1. Manage   Students\n";
	cout << "\t\t2. Manage Professors\n";
	cout << "\t\t3. Exit\n";
	cout << "\t\tEnter a choice: ";
	int choice;
	cin >> choice;
	while (choice > 3 || choice < 1)
	{
		cout << "\t\tInvalid choice. Please select a valid number.\n";
		cout << "\t\tEnter a choice: ";
		cin >> choice;
	}
	system("cls");
	if (choice == 1) Student_Menu();
	else if (choice == 2)Professor_Menu();
	else
	{
		system("cls");
		return;
	}
}
void Student_Menu()
{
	while (1)
	{
		cout << "\t\t\t***** STUDENT DATABASE MANAGEMENT SYSTEM *****\n\n";
		cout << "\t\t1. Add    Student\n";
		cout << "\t\t2. Find   Student\n";
		cout << "\t\t3. Modify Student\n";
		cout << "\t\t4. List   Students\n";
		cout << "\t\t5. Back\n";
		cout << "\t\tEnter a choice: ";
		int choice;
		cin >> choice;
		while (choice > 6 || choice < 1)
		{
			cout << "\t\tInvalid choice. Please select a valid number.\n";
			cout << "Enter a choice: ";
			cin >> choice;
		}
		system("cls");
		student temp;//made to access the add function inside student struct
		switch (choice)
		{
		case 1:
			temp.add();
			system("pause");
			system("cls");
			break;
		case 2:
			temp.find();
			system("pause");
			system("cls");
			break;
		case 3:
			temp.modify();
			system("pause");
			system("cls");
			break;
		case 4:
			temp.list();
			system("pause");
			system("cls");
			break;
		case 5:
			Main_Menu();
			return;
			break;
		default:
			break;
		}
	}
}
string getstring(string& curr)
{
	getline(cin, curr);
	while (curr.size() == 0)
		getline(cin, curr);
	return curr;
}
string num(string& curr)
{
	bool good = 0;
	while (!good)
	{
		good = 1;
		for (auto x : curr)
		{
			if (x - '0' > 9 || x - '0' < 0)
			{
				good = 0;
				break;
			}
		}
		if (!good)
		{
			cout << "ID must consist of numbers only. Please enter a valid ID: ";
			getstring(curr);
		}
	}
	return curr;
}
void Professor_Menu()
{
	while (1)
	{
		cout << "\t\t\t***** PROFESSOR DATABASE MANAGEMENT SYSTEM *****\n\n";
		cout << "\t\t1. Add    Professor\n";
		cout << "\t\t2. Find   Professor\n";
		cout << "\t\t3. Modify Professor\n";
		cout << "\t\t4. List   Professors\n";
		cout << "\t\t5. Back\n";
		cout << "\t\tEnter a choice: ";
		int choice;
		cin >> choice;
		while (choice > 6 || choice < 1)
		{
			cout << "\t\tInvalid choice. Please select a valid number.\n";
			cout << "Enter a choice: ";
			cin >> choice;
		}
		system("cls");
		professor temp;//made to access the add function inside student struct
		switch (choice)
		{
		case 1:
			temp.add();
			system("pause");
			system("cls");
			break;
		case 2:
			temp.find();
			system("pause");
			system("cls");
			break;
		case 3:
			temp.modify();
			system("pause");
			system("cls");
			break;
		case 4:
			temp.list();
			system("pause");
			system("cls");
			break;
		case 5:
			Main_Menu();
			return;
			break;
		default:
			break;
		}
	}
}