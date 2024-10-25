#include<cstring>
#include<iostream>
#include <vector>
using namespace std;

class String {
    friend ostream& operator<<(ostream& os, const String& str);
private:
    char* _chars; //字符数组指针
    size_t _size; //长度
    void computeLPSArray(const String& pat, int M, vector<int>& lps);
public:
    String(const char* str = "");
    ~String();
    String(const String& other); // 拷贝构造函数
    String& operator=(const String& str);
    String& operator=(const char* str);
    int find(const String& pat);
};

inline String::String(const char* str) {
    if (str) {
        _size = strlen(str);
        _chars = new char[_size + 1];
        strcpy(_chars, str);
    }
    else {
        _size = 0;
        _chars = new char[1];
        *_chars = '\0';
    }
}

inline String::~String() {
    delete[] _chars;
}

inline String::String(const String& other) {
    _size = other._size;
    _chars = new char[_size + 1];
    strcpy(_chars, other._chars);
}

inline String& String::operator=(const String& str) {
    if (this != &str) {
        char* new_chars = new char[str._size + 1];
        strcpy(new_chars, str._chars);
        delete[] _chars;
        _chars = new_chars;
        _size = str._size;
    }
    return *this;
}

inline String& String::operator=(const char* str) {
    if (str) {
        size_t new_size = strlen(str);
        char* new_chars = new char[new_size + 1];
        strcpy(new_chars, str);
        delete[] _chars;
        _chars = new_chars;
        _size = new_size;
    }
    else {
        delete[] _chars;
        _size = 0;
        _chars = new char[1];
        *_chars = '\0';
    }
    return *this;
}

ostream& operator<<(ostream& os, const String& str) {
    os << str._chars;
    return os;
}

int String::find(const String& pat) {
    int M = pat._size; 
    int N = _size; 
    if (M == 0 || N < M) return -1;
    vector<int> lps(M);
    computeLPSArray(pat, M, lps);
    int i = 0;
    int j = 0;
    while (i < N) {
        if (pat._chars[j] == _chars[i]) {
            j++;
            i++;
        }
        if (j == M) {
            return i - j;
        }
        else if (i < N && pat._chars[j] != _chars[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1; 
}
void String::computeLPSArray(const String& pat, int M, vector<int>& lps) {
    int len = 0; 
    lps[0] = 0; 
    int i = 1;
    while (i < M) {
        if (pat._chars[i] == pat._chars[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}