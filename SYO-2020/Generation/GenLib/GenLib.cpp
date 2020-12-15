#include<iostream>

extern "C"
{
	int __stdcall outnum(int value)
	{
		std::cout << value;
		return 0;
	}

	int __stdcall outstr(char* ptr)
	{
		setlocale(LC_ALL, "RUSSIAN");
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
		return 0;
	}

	int _stdcall sqroot(int i)
	{
		return (int)std::sqrt(i);
	}

	int _stdcall module(int i)
	{
		return (int)std::fabs(i);
	}

	int _stdcall input(int i)
	{
		std::cin >> i;
		return i;
	}
}