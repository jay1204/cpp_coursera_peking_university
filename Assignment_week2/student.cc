#include <iostream>
#include <string>

using namespace std;

class Student{
private:
    string name;
    int age;
    string student_id;
    int grade[4];
public:
    Student(string name, int age, string studentid, int *grade){
        this->name = name;
        this->age = age;
        this->student_id = studentid;
        this->grade[0] = grade[0];
        this->grade[1] = grade[1];
        this->grade[2] = grade[2];
        this->grade[3] = grade[3];
    }
    
    string getName(){
        return this->name;
    }
    
    string getStudentId(){
        return this->student_id;
    }
    
    int getAge(){
        return this->age;
    }
    
    int getAverageGrade(){
        int sum=0;
        int len = sizeof(grade)/sizeof(grade[0]);
        for(int i=0;i<len;i++){
            sum+=grade[i];
        }
        return sum/len;
    }
};