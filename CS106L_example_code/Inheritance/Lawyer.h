#ifndef LAWYER_H
#define LAWYER_H
#include "Employee.h"
#include <ostream>
#include <string>
using std::ostream;

class Lawyer : public Employee {
public:
    Lawyer(const string& name, int yearsWorked, const string& lawSchool);
    
    int getHoursWorkedPerWeek() const;
    
    string getLawSchool() const;
    
    void speak() const;

private:
    string lawSchool;
};

void Lawyer::speak() const {
    cout << "I'm a lawer!" << endl;
}

Lawyer::Lawyer(const string& name, int yearsWorked, const string& lawSchool) : Employee(name, yearsWorked) {
    this->lawSchool = lawSchool;    
}

string Lawyer::getLawSchool() const {
    return this->lawSchool;
}

int Lawyer::getHoursWorkedPerWeek() const {
    return 2 * Employee::getHoursWorkedPerWeek();
}
ostream& operator<<(ostream& os, const Lawyer& l) {
   os  << l.getName() << " graduate from " <<  l.getLawSchool();
   return os;
}


#endif // !LAWYER_H
