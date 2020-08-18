#include <iostream>

class MyString{
	char *string_content;
	int string_length;
	int memory_capacity;
	
	public:
		//문자 하나 생성
		MyString(char c);
	
		//문자열 생성
		MyString(const char *str);
	
		//문자열 복사 생성자
		MyString(const MyString &str);
	
		//문자열 길이 반환
		int length() const;
	
		//할당된 메모리 크기 반환
		int capacity() const;
	
		//개행없는 문자열 출력
		void print() const;
	
		//개행있는 문자열 출력
		void println() const;
	
		
	
		//임의의 문자열 치환
		MyString &assign(const char *str);
	
		//객체로 존재하는 문자열 치환
		MyString &assign(const MyString &str);
	
		//원하는 크기의 메모리 공간 할당 
		void reserve(int size);
		
		//해당 위치의 문자 반환
		char at(int i) const;
		
	
		//해당 위치에 문자열 삽입
		MyString &insert(int loc, const MyString& str);
		MyString &insert(int loc, const char* str);
		MyString &insert(int loc, char c);
		
		//해당 위치에서부터 num만큼 삭제
		MyString &erase(int loc, int num);
		
		//문자열 검색하고 일치하면 위치 반환
		int find(int find_from, const MyString &str) const;
		int find(int find_from, const char *str) const;
		int find(int find_from, char c) const;
	
		//사전식 문자열 비교
		int compare(const MyString &str) const;
		
		// == 재정의
		bool operator==(const MyString &str);

		//~소멸자
		~MyString();
	
};

MyString::MyString(char c){
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
	memory_capacity = 1;
}


MyString::MyString(const char *str){
	while(str[string_length])
		string_length++; // null 문자 만날때까지 카운트
	
	memory_capacity = string_length; // 할당된 메모리의 크기는 문자열의 길이와 같다
	string_content = new char[string_length];
	
	for(int i = 0; i < string_length; i++){
		string_content[i] = str[i];

	}
	
}


MyString::MyString(const MyString &str){
	string_length = str.string_length; //복사할 문자열의 길이 복사
	
	memory_capacity = string_length;
	string_content = new char[string_length];
	
	for(int i = 0; i < string_length; i++){
		string_content[i] = str.string_content[i];
	}
	
}


int MyString::length() const {
	return string_length;
}


int MyString::capacity() const {
	return memory_capacity;
}


void MyString::print() const {
	for(int i = 0; i < string_length; i++){
		std::cout << string_content[i];
	}
		
}


void MyString::println() const {
	for(int i = 0; i < string_length; i++){
		std::cout << string_content[i];
	}
		
	std::cout << std::endl;
}


MyString &MyString::assign(const MyString &str){
	if(str.string_length > memory_capacity){
		delete[] string_content;
		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}
	string_length = str.string_length;
	
	for(int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
	
	return *this;
}


MyString &MyString::assign(const char *str){
	MyString temp(str);
	return assign(temp);
}


void MyString::reserve(int size){
	if(size > memory_capacity){ // 할당할 메모리의 크기가 기존 크기보다 크지 않다면 동작하지 않는다.
		char *prev_string_content = string_content;
		
		string_content = new char[size];
		
		for(int i = 0; i < string_length; i++) string_content[i] = prev_string_content[i];
		
		delete[] prev_string_content;
	}
}


char MyString::at(int i) const {
	if(i < 0 || i >= string_length) return 0;
	return string_content[i];
}


MyString &MyString::insert(int loc, const MyString &str){
	
	if(loc < 0 || loc > string_length) return *this;
	
	if(memory_capacity < string_length + str.string_length){
		if(memory_capacity * 2 > string_length + str.string_length) memory_capacity *= 2;
		else{
			memory_capacity = string_length + str.string_length;
		}

		char *prev_string_content = string_content;
		string_content = new char[memory_capacity];

		int i;
		for(i = 0; i < loc; i++)
			string_content[i] = prev_string_content[i];

		for(int j = 0; j < str.string_length; j++)
			string_content[i + j] = str.string_content[j];

		for(; i < string_length; i++)
			string_content[str.string_length + i] = prev_string_content[i];

		delete[] prev_string_content;
	}
	else{
		char *prev_string_content = string_content;
		string_content = new char[memory_capacity];
		int i;
		for(i = string_length; i >= loc; i--)
			string_content[i + str.string_length] = str.string_content[i];
		for(int j = 0; j < loc + i; j++ )
			string_content[j + loc + i] = str.string_content[j];
		for(i = 0; i < loc; i++ )
			string_content[i] = str.string_content[i];
		
		delete[] prev_string_content;
	}
	
	
	string_length = string_length + str.string_length;
	
	return *this;
}


MyString &MyString::insert(int loc, const char *str){
	MyString temp(str);
	return insert(loc, temp);
}


MyString &MyString::insert(int loc, char c){
	MyString temp(c);
	return insert(loc, temp);
}


MyString &MyString::erase(int loc, int num){
	if(loc < 0 || loc > string_length) return *this;
	
	if(num < 0) return *this;
	
	if(loc + num > string_length) num = string_length - loc;
	
	for(int i = 0; i <= num; i++){
		string_content[loc + i] = string_content[loc + num + i];
	}
		
	string_length -= num;
	return *this;
}


int MyString::find(int find_from, const MyString &str) const {
	if(find_from < 0 || find_from > string_length) return -1;
	if(string_length < str.string_length) return -1;
	if(str.string_length == 0) return -1;
	
	int i,j;
	for(i = find_from; i <= string_length - str.string_length; i++){
		for(j = 0; j < str.string_length ; j++){
			if(string_content[i + j] != str.string_content[j]) break;
		}
		if(j == str.string_length) return i;
	}
	return -1;
}


int MyString::find(int find_from, const char *str) const {
	MyString temp(str);
	return find(find_from, temp);
}


int MyString::find(int find_from, char c) const {
	MyString temp(c);
	return find(find_from, temp);
}


int MyString::compare(const MyString &str) const {
	for(int i = 0; i < std::min(string_length, str.string_length); i++){
		if(string_content[i] > str.string_content[i]) return 1; // this가 더 크다
		else if(string_content[i] < str.string_content[i]) return -1; // this가 더 작다
	}
	
	if(string_length == str.string_length) return 0; //this와 같다
	else if(string_length > str.string_length) return 1; //문자가 일치했지만 this의 길이가 크면 this가 더 크다
	return -1; //문자가 일치하지만 this의 길이가 작으면 this가 더 작다
		
}


bool MyString::operator==(const MyString &str){
	return !compare(str); //같으면 1 다르면 0
}


MyString::~MyString(){
	delete[] string_content;
}
