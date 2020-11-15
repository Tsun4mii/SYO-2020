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
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
		return 0;
	}
}