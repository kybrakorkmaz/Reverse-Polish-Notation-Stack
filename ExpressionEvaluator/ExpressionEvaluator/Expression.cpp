#include <string>
#include<stack>
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
/*
* @author Kubra Korkmaz
* @date 11.08.2022
* Data Structor Lab - HW 3 - ADT-STACK
*/
///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {;
	stack<char> exp; //expression
	string result;
	vector<char> v;
	char t = ' ';
	char c = ' ';
	for (int i = 0; i < s.size(); i++) { //skip wspaces
		char c = s[i];
		if (c != ' ') { v.push_back(c); }
	}//end-for
	for (int i = 0; i < v.size(); i++) {
		c = v[i];                                 //get char
		if (!exp.empty()) { t = exp.top(); }      //if stack is not empty, insert top value to t variable
		if (c == '*' || c == '/') {		          //if char is multiplier or divider symbol
			result += ' ';                        //insert wspace
			if (t == '*' || t == '/') {           //if top of stack is multiplier or divider symbol
				result += t;                       //insert top of stack into result string
				exp.pop();                        //pop it
			}//end-if
			else {//not if top of stack is multiplier or divider symbol
				exp.push(c); //insert c character into stack
			}//end-else
		}//end-if
		else if (c == '+' || c == '-') {          //if char is addition or subtraction symbol
			result += ' ';                         //insert wspace
			while (!exp.empty()) {                //continue until stack will be empty
				if (t == '(') break;               //if top of stack is open parenthesis then break
				result += t;                      //insert top of stack into string
				result += ' ';                     //insert wspace
				exp.pop();                         //pop top of stack to change next value
				if (!exp.empty()) { t = exp.top(); }  //if stack is  not empty change with next value
			}//end-while
			exp.push(c);                            //insert new char to stack
		}//end-else-if
		else if (c == '(') { exp.push(c); }         //insert open parenthesis into stack
		else if (c == ')') {  
			result += ' ';                           //inser wspace into string for next value
			while (true) {
				if (t == '(') {                      //if top of stack is open parenthesis then pop it and break loop
				exp.pop();
				break;
				}//end-if
				result += t;                         //insert top of stack to string
				result += ' ';                       //insert wspace
				exp.pop();                           //pop top of stack
				t = exp.top();                        //next top value of stack
			}//end-while
		}//end-else-if
		else {
			result += c;
		}//end-else
	}
	result += ' ';//insert wspace 
	while (true) { //get last operators from stack
		if (!exp.empty()) {
			t = exp.top(); 
			result += t;
			result += ' ';
			exp.pop();
		}//end-if
		else {//if stack is empty then break the loop
			break;
		}//end-else
	}//end-while
	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	stack<int>exp;
	char c = ' ';
	int val = 0; //value
	int f = 0; //first number
	int sec = 0; //second number
	string str = "";
	stringstream ss;
	float result = 0;
	
	for (int i = 0; i < s.size(); i++) {
		c = s[i]; //get char
		//get first and second numbers from stack and operate them
		if(c == '/'){	
			//20/5 first=5 second= 20 cz of stack so second/first
			f = exp.top();
			exp.pop();
			sec = exp.top();
			exp.pop();
			result = sec / f;
			exp.push(result);
		}//end-if
		else if (c == '*') {
			f = exp.top();
			exp.pop();
			sec = exp.top();
			exp.pop();
			result = f * sec; //order does not change the result
			exp.push(result);

		}//end-else-if
		else if(c == '-'){
			//20-5 first=5 second= 20 cz of stack so second-first
			f = exp.top();
			exp.pop();
			sec = exp.top();
			exp.pop();
			result = sec - f;
			exp.push(result);

		}//end-else-if
		else if(c=='+'){
			f = exp.top();
			exp.pop();
			sec = exp.top();
			exp.pop();
			result = f + sec;//order does not change the result
			exp.push(result);

		}//end-else-if
		else {
			if (c != ' ') {
				str += c; //collect numbers as string
			}//end-if
			else { //if char is wspace
				if (!str.empty()) { //prevent duplication of last number
					ss << str;  //insert string to stream
					ss >> val;  //convert string numbers to float
					ss.clear(); //clear stream to reuse
					str.clear(); //clear string to reuse
					exp.push(val);  //insert value to stack
				}//end-if				
			}//end-else			
		}//end-else
	}//end-for
	result = exp.top();  //get result
	exp.pop();  //delete last value of stack

	//if (exp.empty()) cout << "stack is empty!\n";

	cout << "result: " << result << endl;
	return result;
} // end-EvaluatePostfixExpression
