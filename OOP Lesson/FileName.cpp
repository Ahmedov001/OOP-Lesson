#include<iostream>
#include<string>
using namespace std;

class Employee {
	string fin;
	string fullname;
	double salary;
	string position;

public:
	static int employee_counter;
	Employee(string fin, string fullname, double salary, string position) {
		employee_counter++;
		this->fin = fin;
		this->fullname = fullname;
		this->salary = salary;
		this->position = position;
	}
	void Show();

	string Get_Fin() {
		return fin;
	}

	void Change_Salary(double salary) {
		this->salary = salary;
	}

	void Change_position(string position) {
		this->position = position;
	}


	~Employee() {
		employee_counter--;
		cout << fin << " Destructor" << endl;
	}
};

int Employee::employee_counter = 0;

void Employee::Show() {
	cout << "Fin: " << fin << endl;
	cout << "Fullname: " << fullname << endl;
	cout << "Salary: " << salary << " azn" << endl;
	cout << "Position: " << position << endl;
}


Employee*& Create_employee() {
	cin.clear();
	cin.ignore();
	string fin;
	cout << "Enter fin: ";
	getline(cin, fin);
	string fullname;
	cout << "Enter fullname: ";
	getline(cin, fullname);

	double salary;
	cout << "Enter salary: ";
	cin >> salary;

	cin.ignore();
	cin.clear();

	string position;
	cout << "Enter position: ";
	getline(cin, position);

	Employee* employee = new Employee(fin, fullname, salary, position);
	return employee;
}
Employee**& AddEmployee(Employee**& employees, int& size) {
	Employee** new_employees = new Employee * [Employee::employee_counter+1];
	for (size_t i = 0; i < size; i++)
	{
		new_employees[i] = employees[i];
	}
	new_employees[size] = Create_employee();
	size++;
	delete employees;
	employees = nullptr;
	return new_employees;
}
int SearchEmployee(Employee** employees, int& size ,string fin) {
	for (size_t i = 0; i < size; i++)
	{
		if (employees[i]->Get_Fin() == fin) {
			return i;
		}
	}
	return -1;
}
void ShowEmployees(Employee**& employees, int& size) {
	for (size_t i = 0; i < size; i++)
	{
		employees[i]->Show();
	}
}
Employee**& DeleteEmployee(Employee**& employees, int& size,string fin) {
	Employee** new_employees = new Employee * [size-1];
	for (size_t i = 0; i < size; i++)
	{
		if (employees[i]->Get_Fin() != fin) {
			new_employees[i] = employees[i];
		}	
		else {
			delete employees[i];
		}
	}
	size--;
	delete employees;
	employees = nullptr;
	return new_employees;
}

Employee**& UpdateEmployee(Employee**& employees, int& size, string fin) {
	int index = SearchEmployee(employees, size,fin);
	if (index == -1) {
		cout << "Don't found!" << endl;
	}
	else {
		int choise;
		cout << "1. Update salary" << endl;
		cout << "2. Update position" << endl;
		cin >> choise;
		if (choise == 1) {
			double salary;
			cout << "Enter new salary: ";
			cin >> salary;
			employees[index]->Change_Salary(salary);
		}
		else if (choise == 2) {
			string position;
			cout << "Enter new position: ";
			getline(cin, position);
			employees[index]->Change_position(position);
		}
	}
	return employees;
}


void main() {

	Employee* employee1 = new Employee("45DFG9B", "Hesen Hesenov", 890, "Teacher");
	employee1->Show();

	Employee* employee2 = new Employee("57AY78H", "Orxan Hesenov", 1800, "Designer");
	employee2->Show();


	int size = Employee::employee_counter;
	Employee** employees = new Employee * [size] {employee1, employee2};


	while (true) {
		int choise;
		cout << endl<<endl<<"1. Show Employees" << endl << "2. Add Employee" << endl;
		cout << "3. Update Employee" << endl << "4. Delete Employee"<<endl;
		cout << "Enter: ";
		cin >> choise;
		if (choise == 1) {
			ShowEmployees(employees, size);
		}
		else if (choise == 2) {
			employees = AddEmployee(employees, size);
		}
		else if (choise == 3) {
			string fin;
			cin.clear();
			cin.ignore();
			cout << "Enter fin: ";
			getline(cin, fin);
			employees = UpdateEmployee(employees, size, fin);
		}
		else if (choise == 4) {
			string fin;
			employees = DeleteEmployee(employees, size, fin);
		}
		else cout << "Wrong choise!";
	}

}