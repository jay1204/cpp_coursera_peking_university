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
    void input(){
        getline(cin,name,',');
        cin >> age ;
        cin.ignore();
        getline(cin,student_id,',');
        for(int i=0;i<4;i++){
            cin >> grade[i];
            cin.ignore();
        }
    }
    
    void output(){
        cout << name << "," << age << "," << student_id << ",";
        cout << getAverageGrade() << endl;
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


int main(){ 
    Student s1;
    s1.input();
    s1.output();
    
}