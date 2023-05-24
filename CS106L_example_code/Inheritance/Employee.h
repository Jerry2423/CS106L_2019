#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::cin;
using std::string;


class Employee {
public:
    Employee() = default;
    Employee(const string& name, int yearsWorked);
    virtual ~Employee() = default;
    // virtual ~Employee(){}

    string getName() const;
    int getYearsWored() const;
    virtual int getHoursWorkedPerWeek() const;

    virtual void speak() const;

private:
    string name;
    int yearsWorked;
};

void Employee::speak() const {
    cout << "I'm a worker!" << endl;
}

Employee::Employee(const string& name, int yearsWorked) {
    this->name = name;
    this->yearsWorked = yearsWorked;
}

string Employee::getName() const {
    return this->name;
}

int Employee::getYearsWored() const {
    return this->yearsWorked;
}

int Employee::getHoursWorkedPerWeek() const {
    return 40;
}
#endif // !DEBUG
