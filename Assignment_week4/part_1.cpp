#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
    Complex& operator=(const char* s){
        if(!s){
            return *this;
        }
        
        int len = strlen(s)+1;
        int pos = 0;
        char real[len];
        char imag[len];
        while(s[pos] !='+')
            pos++;
            
        strncpy(real,s,pos);
        strncpy(imag,s+pos+1,len-3-pos);
        r = atof(real);
        i = atof(imag);
        
        return *this;
        
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}