#include <iostream>
 
using namespace std;
 
int binary(int);
 
int main(void) {
    int number;
 
    cout << "Please enter a positive integer: ";
    cin >> number;
    if (number < 0)
        cout << "That is not a positive integer.\n";
    else {
        cout << number << " converted to binary is: ";
        int b =binary(number);
        cout << endl<<b<<endl;
    }
}
 
	int binary(int number) {
		static int a;
	    int remainder;
	 
	    if(number <= 1) {
	        cout << number;
	        a = a*10 + number;
	        return number;
	    }
	 
	 
	    remainder = number%2;
	    binary(number >> 1);
	    a = a*10 + remainder;
	    cout << a<<endl;
	    return a;
	}