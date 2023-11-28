#include <iostream>
#include <string.h>

class string {
    char *str;
    int len;
public:
    string(char c, int n); // 문자c가 n개 있는 문자열로 정의
    string(const char *s);
    string(const string &s);
    ~string();
    
    void add_string(const string &s);   // str 뒤에 s 를 붙인다.
    void copy_string(const string &s);  // str 에 s 를 복사한다.
    int strlen();                       // 문자열 길이 리턴
    void show();
};

string::string(char c, int n) {
    std::cout<<"생성자 : "<<c<<" -> "<<n<<"개"<<"\n";
    len = n;
    str = new char[n+1];
    std::fill_n(str, n, c);
}

string::string(const char *s) {
    std::cout<<"생성자 : "<<s<<"\n";
    len = std::strlen(s) + 1;
    str = new char[len];
    strcpy(str, s);
}

string::string(const string &s) {
    std::cout<<"복사 생성자 : "<<s.str<<"\n";
    len = s.len;
    str = new char[len+1];
    for(int i=0; i<len; i++)
        str[i] = s.str[i];
}

string::~string() {
    std::cout<<"소멸 생성자 : "<<str<<"\n";
    delete[] str;
}

void string::add_string(const string &s) { // str 뒤에 s 를 붙인다.
    char* add_s = new char[len+s.len+1];
    strcpy(add_s, str);
    strcat(add_s, s.str);
    len += s.len;
    delete[] str;
    str = add_s;
}
void string::copy_string(const string &s) { // str 에 s 를 복사한다.
    delete[] str;
    str = new char[s.len + 1];
    strcpy(str, s.str);
    len = s.len + 1;
}
int string::strlen() { // 문자열 길이 리턴
    return len;
}

void string::show() {
    std::cout<<"객체 : "<<str<<"\n";
}

int main() {
    string a('a', 10);
    int len = a.strlen();
    a.show();
    std::cout<<"문자열 길이 : "<<len<<"\n";
    std::cout<<"========================\n";
    char *sb;
    sb = "abcde";
    string b(sb);
    b.show();
    len = b.strlen();
    std::cout<<"문자열 길이 : "<<len<<"\n";
    std::cout<<"========================\n";
    string *c = new string(b);
    c->show();
    c->add_string(a);
    c->show();
    c->copy_string(a);
    c->show();
    std::cout<<"========================\n";
}
