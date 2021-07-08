
#include <iostream>
#include <string>

using namespace std;

int main() {

	string str[100];
    
	for (int i = 0; i < 100; i++){
		getline(cin, str[i]);
		cout << str[i] << endl;
    }
}