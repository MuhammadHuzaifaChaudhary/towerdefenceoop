#include<iostream>
using namespace std;
int square(int num)
{
	num = num * num;
	return num;
}
int main()
{
	int num;

	cout << "enter a number" << endl;
	cin >> num;
	cout << "square of num is " << square(num);
}