#include <iostream>
#include <algorithm>
using namespace std;

int a[4];
int main() {
	// your code goes here;
	for (int i=0; i<4; i++)
	cin >> a[i];
	sort(a, a+4);
	cout << a[0]*a[2] << endl;
	
	return 0;
}