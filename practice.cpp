#include <iostream>

//예시
class Int {
    int data;
public:
    Int(int data) : data(data) {}
    Int(const Int& i) : data(i.data) {}
    operator int() {
        return data;
    }
};

int main() {
    Int x = 3; //Int Wrapper 클래스
    int a = x + 4; //기본 int 자료형
    std::cout<<a<<"\n";
}
