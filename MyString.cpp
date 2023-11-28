#include <iostream>

// string.h 는 strlen 때문에 include 했는데, 사실 여러분이 직접 strlen 
// 과같은함수를만들어서써도됩니다.
#include <string.h>

class MyString {
    char* string_content; // 문자열 데이터를 가리키는 포인터
    int string_length; // 문자열 길이
    int memory_capacity; // 현재 할당된 용량
    
public:
    // 문자하나로생성
    MyString(char c);
    
    // 문자열로 부터 생성
    MyString(const char* str);
    
    // 복사 생성자
    MyString(const MyString& str);
    
    ~MyString();
    
    int length() const;
    int capacity() const;
    void reserve(int size);
    
    void print() const;
    void println() const;
    
    MyString& assign(const MyString& str);
    MyString& assign(const char* str);
    
    char at(int i) const;
    
    MyString& insert(int loc, const MyString& str);
    MyString& insert(int loc, const char* str);
    MyString& insert(int loc, char c);
    
    MyString& erase(int loc, int num);
    
    int find(int find_from, const MyString& str) const;
    int find(int find_from, const char* str) const;
    int find(int find_from, char c) const;
    
    int compare(const MyString& str) const;
};

MyString::MyString(char c) { 
    string_content = new char[1];
    string_content[0] = c;
    memory_capacity = 1;
    string_length = 1;
}

MyString::MyString(const char* str) {
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];
    for (int i = 0; i != string_length; i++) {
        string_content[i] = str[i];
    }
}

MyString::MyString(const MyString& str) {
    string_length = str.string_length;
    memory_capacity = str.string_length;
    string_content = new char[string_length];
    for (int i = 0; i != string_length; i++) {
        string_content[i] = str.string_content[i];
    }
}

MyString::~MyString() {
    delete[] string_content;
}

int MyString::length() const {
    return string_length;
}

void MyString::print() const {
    for (int i = 0; i != string_length; i++) {
        std::cout << string_content[i];
    }
}

void MyString::println() const {
    for (int i = 0; i != string_length; i++) { 
        std::cout << string_content[i];
    }
   std::cout << std::endl;
 }

MyString& MyString::assign(const MyString& str) { 
    if (str.string_length > memory_capacity) {
        // 그러면 다시 할당을 해줘야만 한다.
        delete[] string_content;
        string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }
    
    for (int i = 0; i != str.string_length; i++) {
        string_content[i] = str.string_content[i];
    }
    
    // 그리고 굳이 str.string_length + 1 ~ string_length 부분은 초기화
    // 시킬 필요는 없다. 왜냐하면 거기 까지는 읽어들이지 않기 때문이다.
    
    string_length = str.string_length; 
    
    return *this;
}

MyString& MyString::assign(const char* str) {
    int str_length = strlen(str);
    if (str_length > memory_capacity) {
        // 그러면 다시 할당을 해줘야만 한다.
        delete[] string_content;
        string_content = new char[str_length];
        memory_capacity = str_length;
    }
    
    for (int i = 0; i != str_length; i++) {
        string_content[i] = str[i];
    }
    
    string_length = str_length;
    return *this;
}

int MyString::capacity() const { return memory_capacity; } 

void MyString::reserve(int size) {
    if (size > memory_capacity) {
        char* prev_string_content = string_content;
        string_content = new char[size]; memory_capacity = size;
        
        for (int i = 0; i != string_length; i++)
            string_content[i] = prev_string_content[i];
        
        delete[] prev_string_content;
    }
    
    // 만일 예약하려는 size 가 현재 capacity 보다 작다면
    // 아무것도 안해도 된다.
}
char MyString::at(int i) const {
    if (i >= string_length || i < 0) {
        return 0;
    } else {
        return string_content[i];
    }
}

MyString& MyString::insert(int loc, const MyString& str) {
    // 이는i 의위치바로앞에문자를삽입하게된다. 예를들어서
    // abc 라는 문자열에 insert(1, "d") 를 하게 된다면 adbc 가 된다.
    // 범위를 벗어나는 입력에 대해서는 삽입을 수행하지 않는다.
    if (loc < 0 || loc > string_length) return *this;
    
    if (string_length + str.string_length > memory_capacity) { // 이제 새롭게 동적으로 할당을 해야 한다.
        if (memory_capacity * 2 > string_length + str.string_length)
            memory_capacity *= 2;
        else
            memory_capacity = string_length + str.string_length;
        
        char* prev_string_content = string_content;
        string_content = new char[memory_capacity];
        
        // 일단 insert 되는 부분 직전까지의 내용을 복사한다.
        int i;
        for (i = 0; i < loc; i++) {
            string_content[i] = prev_string_content[i];
        }
        // 그리고 새롭에 insert 되는 문자열을 넣는다.
        for (int j = 0; j != str.string_length; j++) {
            string_content[i + j] = str.string_content[j];
        }
        // 이제 다시 원 문자열의 나머지 뒷부분을 복사한다.
        for (; i < string_length; i++) {
            string_content[str.string_length + i] = prev_string_content[i];
        }
        
        delete[] prev_string_content;
        string_length = string_length + str.string_length;
    }
    // 만일초과하지않는경우굳이동적할당을할필요가없게된다.
    // 효율적으로 insert 하기 위해, 밀리는 부분을 먼저 뒤로 밀어버린다.
    for (int i = string_length - 1; i >= loc; i--) {
        // 뒤로밀기. 이때원래의문자열데이터가사라지지않게함
        string_content[i + str.string_length] = string_content[i];
    }
    
    // 그리고 insert 되는 문자 다시 집어넣기
    for (int i = 0; i < str.string_length; i++)
        string_content[i + loc] = str.string_content[i];
    string_length = string_length + str.string_length;
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
    // loc 의앞부터시작해서num 문자를지운다.
    if (num < 0 || loc < 0 || loc > string_length) return *this;
    
    // 지운다는 것은 단순히 뒤의 문자들을 앞으로 끌고 온다고 // 생각하면 됩니다.
    for (int i = loc + num; i < string_length; i++) { 
        string_content[i - num] = string_content[i];
    }
    
    string_length -= num;
    return *this;
}

int MyString::find(int find_from, const MyString& str) const {
    int i, j;
    if (str.string_length == 0) return -1;
    for (i = find_from; i <= string_length - str.string_length; i++) {
        for (j = 0; j < str.string_length; j++) {
            if (string_content[i + j] != str.string_content[j])
                break;
        }
        if (j == str.string_length) 
            return i;
    }
    return -1; // 찾지 못했음
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
// (*this) - (str) 을수행해서그1, 0, -1 로그결과를리턴한다 
    // 1 은(*this) 가사전식으로더뒤에온다는의미. 0 은두문자열
// 이같다는의미, -1 은(*this) 가사전식으로더앞에온다는의미이다.
    for (int i = 0; i < std::min(string_length, str.string_length); i++) { 
        if (string_content[i] > str.string_content[i])
            return 1;
        else if (string_content[i] < str.string_content[i]) 
            return -1;
    }
    // 여기까지했는데끝나지않았다면앞부분까지모두똑같은것이된다. 
    // 만일문자열길이가같다면두문자열은아예같은문자열이된다.
    if (string_length == str.string_length) 
        return 0;
    
    // 참고로abc 와abcd 의크기비교는abcd 가더뒤에오게된다. 
    else if (string_length > str.string_length)
        return 1; 
    return -1;
}

int main() {
    MyString str1("abcdef");
    MyString str2("abcde");
    std::cout << "str1 and str2 compare : " << str1.compare(str2) << std::endl;
}
