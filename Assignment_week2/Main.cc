#include <iostream>
#include <string>
#include "student.cc"

using namespace std;

int main(){
    string name;
    int age;
    string student_id;
    int grade[4];
    getline(std::cin,name,',');
    cin >> age;
    cin.ignore();
    getline(cin,student_id,',');
    for(int i=0;i<4;i++){
        cin >> grade[i];
        cin.ignore();
    }

    Student s1(name,age,student_id,grade);
    cout << s1.getName() << "," << s1.getAge() << "," << s1.getStudentId() << ",";
    cout << s1.getAverageGrade() << endl;
        
    
}