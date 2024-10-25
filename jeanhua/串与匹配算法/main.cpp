#include<iostream>
#include "String.h"
using namespace std;
int main() {
	String str1 = "ÄãºÃ";
	cout << str1<<endl;
	String str2 = str1;
	cout << str2<<endl;
	String str3 = "ABABDABACDABABCABAB";
	String str4 = "ABABCABAB";
	cout << str3.find(str4);
 }