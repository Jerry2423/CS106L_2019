#ifndef HEAD_TA_H
#define HEAD_TA_H
#include "Employee.h"


class HeadTa : public Employee {
public:
    HeadTa(const string& name, int yearsWorked, const string& teaching_course);
    
    string getCourseName() const;
    void speak() const;
private:
    string teaching_course;
};

HeadTa::HeadTa(const string& name, int yearsWorked, const string& teaching_course) : Employee(name, yearsWorked), teaching_course(teaching_course) {}

void HeadTa::speak() const {
    cout << "I'm a TA" <<endl;
}

string HeadTa::getCourseName() const {
    return teaching_course;
}



#endif // !DEBUG
