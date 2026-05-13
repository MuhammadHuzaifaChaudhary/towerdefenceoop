#include<iostream>
using namespace std;
int add(int x, int y)
{ 
	return x + y;
}
int multiply(int x, int y)
{
	return x * y;
}
int subtract(int x, int y)
{   
	
	return x - y;
}
 float divide(int x,int y)
 {
	 if (y > 0)
	 {
		 return  (float)x / y;
	 }
	 else
	 {
		 cout << " cant perform it because second no  should not be  ";
	 }
}
 int main()
 {
	 int x;
	 int y;
	 cout << "enter two numbers ";
	 cin >> x >> y;
	 int choice;;
	 cout << "enter operation to be performed \n 1.add\n 2.subtract\n 3.multiply \n 4.divide";
	 cin >> choice;
	 if (choice < 1 || choice>4)
	 {
		 cout << "enter a valid choice ";
		 return 0;
	 }
	 if (choice == 1)
	 {
		 cout << add(x, y);
	 }
	 else if (choice== 3)
	 {
		 cout << multiply(x, y);
	 }
	 else if (choice == 2)
	 {
		 cout << subtract(x, y);
	 }
	 else if (choice == 4)
	 {
		 cout << divide(x, y);
	 }
	

 }
