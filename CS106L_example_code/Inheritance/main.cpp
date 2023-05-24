#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include "Employee.h"
#include "Lawyer.h"
#include "HeadTa.h"

using std::cin; using std::cout;
using std::endl; using std::string;
using std::vector;

int main() {
    // Lawyer a("jr", 10, "mit");
    // Employee b("ss", 10);
    // Employee* law = new Lawyer("jr", 10, "mit");
    // cout << law->getHoursWorkedPerWeek() << endl;

    vector<Employee*> vec;
    // Lawyer* a = new Lawyer("jr", 10, "mit");
    // HeadTa* b = new HeadTa("zj", 3, "econ");
    // Employee* c = new HeadTa("c", 2, "cs");
    //
    // cout << static_cast<HeadTa*>(c) ->getCourseName() << endl;
    //
    // vec = {a, b};
    //
    // for (const auto& i : vec) {
    //     i->speak();
    // }
    //
    std::unique_ptr<Lawyer> a = std::make_unique<Lawyer>("jr", 10, "mit");
    std::shared_ptr<Employee> b = std::make_shared<HeadTa>("zj", 2, "sh");
    b ->speak();
    std::unique_ptr<HeadTa> c = std::make_unique<HeadTa>("jj", 3, "sk");
    return 0;
}
