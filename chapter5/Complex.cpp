//
//  Complex.cpp
//  cppStudy
//
//  Created by 이가현 on 2023-11-28.
//

#include <iostream>

//복소수 클래스
class Complex {
    double real, img;
    
    double get_number(const char *str, int from, int to);
    
public:
    Complex(double real, double img) : real(real), img(img) {}
    Complex(const char* str);
    Complex(const Complex& c) {
        real = c.real;
        img = c.img;
    }
    
    Complex operator+(const Complex& c) const;
    Complex operator+(const char* str) const;
    
    Complex operator-(const Complex& c) const;
    Complex operator-(const char* str) const;
    
    Complex operator*(const Complex& c) const;
    Complex operator*(const char* str) const;
    
    Complex operator/(const Complex& c) const;
    Complex operator/(const char* str) const;
    
    Complex& operator=(const Complex& c);
    
    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);
    
    void println() {
        std::cout << "( " << real << " , " << img << " ) " << std::endl;
    }
};

Complex::Complex(const char* str) {
    //str 형태 : [부호](실수부)(부호)i(허수부)
    //실수부의 부호는 생략 가능, 생략 시 +
    
    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;
    
    int pos_i=-1;
    
    for(int i=0; i<strlen(str); i++) {
        if(str[i] == 'i') {
            pos_i = i;
            break;
        }
    }
    if(pos_i == -1) { //허수부가 없을때
        real = get_number(str, begin, end-1);
    }
    
    real = get_number(str, begin, pos_i-1);
    img = get_number(str, pos_i+1, end-1);
    
    if(pos_i >= 1 && str[pos_i-1] == '-')
        img *= -1.0;
}

Complex Complex::operator+(const Complex& c) const {
    Complex temp(real+c.real, img+c.img);
    return temp;
}

Complex Complex::operator-(const Complex& c) const {
    Complex temp(real-c.real, img-c.img);
    return temp;
}

Complex Complex::operator*(const Complex& c) const {
    Complex temp(real*c.real - img*c.img, real*c.img+img*c.real);
    return temp;
}

Complex Complex::operator/(const Complex& c) const {
    Complex temp((real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
                 (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
    return temp;
}

Complex Complex::operator+(const char* str) const{
    Complex temp(str);
    return (*this) + temp;
}

Complex Complex::operator-(const char* str) const{
    Complex temp(str);
    return (*this) - temp;
}

Complex Complex::operator*(const char* str) const{
    Complex temp(str);
    return (*this) * temp;
}

Complex Complex::operator/(const char* str) const{
    Complex temp(str);
    return (*this) / temp;
}


double Complex::get_number(const char *str, int from, int to) {
    bool minus = false;
    if(from > to) return 0;
    
    if(str[from] == '-') minus = true;
    if(str[from] == '-' || str[from] == '+') from++;
    
    double num=0.0, decimal=1.0;
    bool integer_part = true;
    
    for(int i=from; i<=to; i++) {
        if(isdigit(str[i]) && integer_part) { //정수부분
            num *= 10;
            num += str[i] - '0';
        }
        else if(str[i] == '.') //소수점
            integer_part = false;
        else if(isdigit(str[i]) && !integer_part) { //소수부분
            decimal /= 10.0;
            num += ((str[i]-'0') * decimal);
        }
        else
            break;
    }
    
    if(minus)
        num *= -1;
    
    return num;
}

Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

Complex& Complex::operator+=(const Complex& c) {
    *this = (*this) + c;
    return *this;
}

Complex& Complex::operator-=(const Complex& c) {
    *this = (*this) - c;
    return *this;
}

Complex& Complex::operator*=(const Complex& c) {
    *this = (*this) * c;
    return *this;
}

Complex& Complex::operator/=(const Complex& c) {
    *this = (*this) / c;
    return *this;
}

int main() {
}
