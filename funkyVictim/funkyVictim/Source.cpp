#include <Windows.h>
#include <iostream>

using std::cout;
using std::endl;

void FuncA()
{
	cout << "I'm function a!" << endl;
}

void FuncB(char * string)
{
	cout << string << endl;
}

int main()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			FuncA();
			FuncB("I'm function b!");
		}
	}
	return 0;
}