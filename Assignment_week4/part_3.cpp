#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码
class Array2{
private:
    int one;
    int two;
    int **array;
    
    int& get(int x,int y){
        return array[x][y];
    }
    friend class Column;
public:
    Array2(int a=0, int b=0):one(a),two(b){
        if(a<=0 || b <=0)
            array = NULL;
        
        array = new int*[a];
        for(int i=0;i<a;i++){
            array[i] = new int[b];
        }
    }
    
    ~Array2(){
        if(array){
            for(int i=0;i<one;i++){
                if(array[i])
                    delete [] array[i];
            }
            delete [] array;
        }
    }
    
    class Column{
    private:
        Array2& parent;
        int x;
    public:
        Column(Array2& pa,int x):parent(pa),x(x){}
        int& operator[](int y){
            parent.get(x,y);
        }
    };
    
    Column operator[](int x){
        return Column(*this,x);
    }
    
    int& operator()(int x,int y){
        return array[x][y];
    }
    
    Array2& operator=(const Array2& a){
        if(array == a.array)
            return *this;
        
        if(!a.array){
            if(array){
                for(int i=0;i<one;i++){
                    if(array[i])
                        delete [] array[i];
                }
                delete [] array;
            }
            array = NULL;
        }else{
            if(one<a.one || two < a.two){
                if(array){
                    for(int i=0;i<one;i++){
                        if(array[i])
                            delete [] array[i];
                    }
                    delete [] array;
                }   
            }
            array = new int*[a.one];
            for(int i=0;i<a.one;i++){
                array[i] = new int[a.two];
            }
            for(int i=0;i<a.one;i++){
                for(int j=0;j<a.two;j++){
                    array[i][j] = a.array[i][j];
                }
            }

        }
            one = a.one;
            two  = a.two;
            return *this;
    }
    
};


int main() {
    Array2 a(3,4);
    int i,j;
    
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    
    return 0;
}

/**
class My2D
{
    public:
       class My2DRow
       {
           My2D& parent;
           int   x;
           public:
               My2DRow(My2D& p, int theX) : parent(p), x(theX) {}     // Just init the temp object
               int& operator[](int y)  const { return parent.pget(x,y);}   // Here we get the value.
       };

       // Return an object that defines its own operator[] that will access the data.
       // The temp object is very trivial and just allows access to the data via operator[]
       My2DRow operator[](int x)        { return My2DRow(*this, x);}
    private:
       friend class My2DRow;
       int&   pget(int x,int y) { /* retrieve data from 2D storage */ //}
//};

/*
int main()
{
    My2D   data;
    int&   val = data[1][2]; // works fine.

    // This is the same as
    My2D::My2DRow row  = data[1];
    int&          val2 = row[2]; 
}
*/