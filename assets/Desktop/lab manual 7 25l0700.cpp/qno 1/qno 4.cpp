#include <iostream>
using namespace std;
void drawsquare(int rows)
{
	cout << "Square " << endl;
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= rows; j++)
		{
			cout << "* ";
		}
		cout << endl;
	}
}
void drawRightTriangle(int rows)
{
	cout << "Right Triangle: " << endl;
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
int main()
{
	int x, c;
	char a;
	cout << "Enter the number of rows: ";
	cin >> x;
	do
	{

		cout << "Choose shape to draw:\n1.Square\n2.Right Triangel\n3.Exit " << endl;
		cin >> c;
		if (c == 1)
		{
			drawsquare(x);
		}
		else if (c == 2)
		{
			drawRightTriangle(x);
		}

		else if (c == 3)
		{
			cout << "Program Ended!";
			return 0;
		}
		cout << "Do Yoy want to draw shape again : Y/N: ";
		cin >> a;
		if (a == 'Y')
		{
			cout << "Enter Rows again:";
			cin >> x;
		}
	} while (a != 'N');
	if (a == 'N')
	{
		cout << "Program Ended";
	}
}