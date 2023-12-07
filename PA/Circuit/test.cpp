#include <iostream>

using namespace std;

class Base {
    int c;
};
class derive : public Base{
    int a;
};

int main(){
    Base * a;
    derive b[2];
    a = b;
    if(a == nullptr) cout <<  1 << endl;
    cout << a << endl;
    cout << b << endl;
    cout << b+1 << endl;
    cout << a+1 << endl;
}