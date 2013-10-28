#include <iostream>

class A{
public:
    int a;
    int getA(){
        return a;
    }
    int getB(){
        return b;
    }

private:
    int b;

};

int main(){
    int *a=new int[10];
    delete a;
    A *t=new A();
    delete t;
    return 0;
}
