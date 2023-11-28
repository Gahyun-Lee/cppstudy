//
//  MyString.cpp
//  cppStudy
//
//  Created by 이가현 on 2023-11-28.
//

#include <iostream>

class MyString {
    char* string_content;
    int string_length;
    int memory_capacity;

public:
    MyString(char c); //문자 하나로
    MyString(const char* str); //문자열로부터
    MyString(const MyString& str); //복사 생성자
    ~MyString();
    
    int length(); //문자열 길이 반환
    int capacity(); //할당된 용량 반환
    void reserve(int size); //할당된 용량의 크기 예약
    
    void print();
    void println();
    
    //문자열 지정(기존 문자열 삭제 후 새로운 문자열 대입
    MyString& assign(const MyString& str);
    MyString& assign(const char* str);
    
    //문자열 삽입
    MyString& insert(int loc, const MyString& str);
    MyString& insert(int loc, const char* str);
    MyString& insert(int loc, char c);
    
    //문자열 일부 삭제
    MyString& erase(int loc, int num);
    
    //문자열 검색
    int find(int find_from, MyString& str) const; //찾기시작하는위치, 찾는문자열
    int find(int find_from, const char* str) const;
    int find(int find_from, char c) const;
    
    //크기 비교(가다다 순으로 뭐가 더 빠른지)
    int compare(const MyString& str) const;
    
};

MyString::MyString(char c) {
    string_content = new char[1];
    string_content[0] = c;
    string_length = 1;
    memory_capacity = 1;
}

MyString::MyString(const char* str) {
    string_length = strlen(str);
    string_content = new char[string_length];
    memory_capacity = string_length;
    
    for(int i=0; i<string_length; i++)
        string_content[i] = str[i];
}

MyString::MyString(const MyString& str) {
    string_length = str.string_length;
    string_content = new char[string_length];
    memory_capacity = string_length;
    for(int i=0; i<string_length; i++)
        string_content[i] = str.string_content[i];
}

MyString::~MyString() {
    delete[] string_content;
}

int MyString::length() {
    return string_length;
}

int MyString::capacity() {
    return memory_capacity;
}

void MyString::reserve(int size) {
    if(size > memory_capacity) {
        char* prev_string_content = string_content;
        
        string_content = new char[size];
        memory_capacity = size;
        
        for(int i=0; i<string_length; i++)
            string_content[i] = prev_string_content[i];
        
        delete[] prev_string_content;
    }
}

void MyString::print() {
    for(int i=0; i<string_length; i++)
        std::cout<<string_content[i];
}

void MyString::println() {
    for(int i=0; i<string_length; i++)
        std::cout<<string_content[i];
    std::cout<<"\n";
}

MyString& MyString::assign(const MyString& str) {
    if(string_length < str.string_length) {
        delete[] string_content;
        string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }
    
    string_length = str.string_length;
    for(int i=0; i<string_length; i++)
        string_content[i] = str.string_content[i];
    
    return *this;
}

MyString& MyString::assign(const char* str) {
    if(string_length < strlen(str)) {
        delete[] string_content;
        string_content = new char[strlen(str)];
        memory_capacity = strlen(str);
    }
    string_length = strlen(str);
    string_content = new char[string_length];
    for(int i=0; i<string_length; i++)
        string_content[i] = str[i];
    return *this;
}

MyString& MyString::insert(int loc, const MyString& str) {
    int size = str.string_length + string_length;
    
    if (loc < 0 || loc > string_length)
        return *this;
    
    if(memory_capacity < size) {
        char* prev_string_content = string_content;
        
        if(memory_capacity * 2 > size) //잦은 메모리 할당/해제를 피하기 위해 but 많은 자원은 낭비하면 안됨
            memory_capacity *= 2; //미리 할당할 경우 현재 메모리 크기의 두 배정도만 더 할당한다
        else
            memory_capacity = size;
        
        string_content = new char[memory_capacity];
        
        int i;
        for(i=0; i<loc; i++)
            string_content[i] = prev_string_content[i];
        for(int j=0; j<str.string_length; j++)
            string_content[i+j] = str.string_content[j];
        for(; i<string_length; i++)
            string_content[i+str.string_length] = prev_string_content[i];
        
        delete[] prev_string_content;
        string_length = size;
        return *this;
    }
    for(int i=string_length-1; i>=loc; i--)
        string_content[i+str.string_length] = string_content[i];
    for(int i=0; i<str.string_length; i++)
        string_content[loc+i] = str.string_content[i];
    string_length = size;
    return *this;
}

MyString& MyString::insert(int loc, const char* str) {
    MyString temp(str);
    return insert(loc, temp);
}

MyString& MyString::insert(int loc, char c) {
    MyString temp(c);
    return insert(loc, temp);
}

MyString& MyString::erase(int loc, int num) {
    if(loc < 0 || loc > string_length || num < 0 || string_length < num+loc)
        return *this;
    
    for(int i=loc+num; i<string_length; i++)
        string_content[i-num] = string_content[i];
    string_length -= num;
    return *this;
}

int MyString::find(int find_from, MyString& str) const {
    for(int i=find_from; i<string_length; i++) {
        for(int j=0; j<str.string_length; j++) {
            if(string_content[i+j] != str.string_content[j])
                break;
            if(j == str.string_length-1)
                return i;
        }
    }
    return -1;
}

int MyString::find(int find_from, const char* str) const {
    MyString temp(str);
    return find(find_from, temp);
}

int MyString::find(int find_from, char c) const {
    MyString temp(c);
    return find(find_from, temp);
}

int MyString::compare(const MyString& str) const {
    //반환
    // 1 : 더 뒤에 온다
    // 0 : 같은 문자열
    // -1 : 더 앞에 온다
    
    for(int i=0; i<string_length; i++) {
        if(string_content[i] > str.string_content[i])
            return 1;
        else if(string_content[i] < str.string_content[i])
            return -1;
    }
    
    if(string_length == str.string_length)
        return 0;
    else if(string_length > str.string_length)
        return 1;
    return -1;
}

int main() {
    MyString str1("abcdef");
    MyString str2("abcde");
    
    std::cout << "str1 and str2 compare : " << str1.compare(str2) << std::endl;
}
