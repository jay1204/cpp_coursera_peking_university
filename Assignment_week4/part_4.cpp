#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

bool check(vector<int> num1, vector<int> num2){
    int left = num1.size();
    int right = num2.size();
    if(left > right){
        num2.push_back(0);
    }
    
    for(int i=left-1;i>=0;i--){
        if(num1[i]>num2[i]){
            return true;
        }else if(num1[i] == num2[i]){
            continue;
        }else{
            return false;
        }
    }
    
    return true;
}

class bigNum{
    bool positive;
    vector<int> num;
public:
    bigNum():positive(true){}
    
    bigNum(vector<int>& num,bool pos):num(num),positive(pos){}
    
    bigNum(string& s){
        for(int i=s.size()-1;i>=0;i--){
            num.push_back((int)(s[i]-'0'));
        }
        for(int i=num.size()-1;i>=0;i--){
            if(num[i]==0)
                num.pop_back();
            else
                break;
        }
        positive = true;
    }
    
    void print(){
        if(!positive)
            cout << "-"; 
        for(int i=num.size()-1;i>=0;i--){
            cout << num[i] ;
        }
        cout<< endl;
    }
    friend bigNum operator+(const bigNum& n1,const bigNum& n2);
    friend bigNum operator-(const bigNum& n1,const bigNum& n2);
    friend bigNum operator*(const bigNum& n1, const bigNum& n2);
    friend bigNum operator/(const bigNum& n1, const bigNum& n2);
    
};

bigNum operator+(const bigNum& n1,const bigNum& n2){
    int left  = n1.num.size();
    int right = n2.num.size();
    vector<int> sum;
    int one = 0;
    int length = left<=right?right:left;
    for(int i=0;i<length;i++){
        int first = i>=left?0:n1.num[i];
        int second = i>=right?0:n2.num[i];
        int digit = first+second+one;
        if(digit>=10){
            digit %=10;
            one= 1;
        }else{
            one = 0;
        }
        sum.push_back(digit);
    }
    
    if(one==1)
        sum.push_back(1);
    
    return bigNum(sum,true);
    
}


bigNum operator-(const bigNum& n1,const bigNum& n2){
    int left = n1.num.size();
    int right = n2.num.size();
    bool pos = true;
    
    vector<int> sub;
    int one = 0;
    int length = left<=right?right:left;
    for(int i=0;i<length;i++){
        int first = i>=left?0:n1.num[i];
        int second = i>=right?0:n2.num[i];   
        int digit = first - second + one;
        if(digit<0){
            digit += 10;
            one = -1;
        }else{
            one = 0;
        }
        sub.push_back(digit);
    }
    
    if(one == -1){
        pos = false;
        sub[0] = 10 - sub[0];
        for(int i=1;i<length;i++){
            sub[i] = 9 -sub[i];
        }
    }
    
    for(int i=sub.size()-1;i>0;i--){
        if(sub[i]==0)
            sub.pop_back();
        else
            break;
    }
        
    return bigNum(sub,pos);
}

bigNum operator*(const bigNum& n1, const bigNum& n2){
    int left = n1.num.size();
    int right = n2.num.size();
    vector<int> mul(left+right,0);
    int one = 0;
    for(int i=0;i<left;i++){
        for(int j=0;j<right;j++){
            int pos = i+j;
            int digit = n1.num[i]*n2.num[j]+mul[pos];
            // from the num[pos] to add the digit
            while(digit>=10){
                mul[pos] = digit%10;
                pos++;
                digit /= 10;
                digit += mul[pos];
            }
            mul[pos] = digit;
        }
    }
    if(mul[left+right-1]==0){
        mul.pop_back();
    }
    
    return bigNum(mul,true);
}

bigNum operator/(const bigNum& n1, const bigNum& n2){
    int left = n1.num.size();
    int right = n2.num.size();
    vector<int> division;
    vector<int> temp(right,0);
    
    if(left < right){
        division.push_back(0);
        return bigNum(division,true);
    }
    
    for(int i=0;i<right;i++){
        temp[right-1-i] = n1.num[left-1-i]; 
    }
    
    if(left == right && !check(temp,n2.num) ){
        division.push_back(0);
        return bigNum(division,true);
    }
        
        
    temp.erase(temp.begin());

    for(int i=left-right;i>=0;i--){
        int count = 0;
        temp.insert(temp.begin(),n1.num[i]);
        while(check(temp,n2.num)){
            count++;
            int length = temp.size();
            int one = 0;
            for(int i=0;i<right;i++){
                int digit = temp[i] - n2.num[i]+one;
                if(digit<0){
                    digit +=10;
                    one  = -1;
                }else{
                    one = 0;
                }
                temp[i] = digit;
            }
            if(length>right){
                temp[length-1] += one;
                if(temp[length-1]==0)
                    temp.pop_back();
            }
        }
        if(count==0 && temp[temp.size()-1]==0)
            temp.pop_back();
        division.insert(division.begin(),count);
    }
    
    if(division[division.size()-1]==0)
        division.pop_back();
    
    return bigNum(division,true);
    
    
}

int main(){
    string s1;
    string op;
    string s2;
    getline(cin,s1,'\n');
    getline(cin,op,'\n');
    getline(cin,s2,'\n');
    bigNum num1(s1);
    bigNum num2(s2);
    bigNum num3;
    
    if(op=="+"){
        num3 = num1+num2;
    }else if(op =="-" ){
        num3 = num1-num2;
    }else if(op == "*"){
        num3 = num1*num2;
    }else if(op == "/"){
        num3 = num1/num2;
    }else{
        cout << "The operator is wrong!"<< endl;
    }
    
    num3.print();
    /*
    num1.print();
    if(op=="+")
        cout << "Good" << endl;
    num2.print();
    
    bigNum num3 = num1+num2;
    num3.print();
    bigNum num4 = num1-num2;
    num4.print();
    bigNum num5 = num1*num2;
    num5.print();
    bigNum num6 = num1/num2;
    num6.print();
    */
    return 0;
}