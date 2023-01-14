#include "help_funcs.h"

template <typename T>
void push(T*& arr, T element, int* size)
{
	T* buf_arr = arr;

	arr = new T[*size + 1];
	for (int i = 0; i < *size; i++)
	{
		arr[i] = buf_arr[i];
	}
	arr[*size] = element;
	(*size)++;

	delete[] buf_arr;
}


template <typename T>
void arr_cpy(T* from_arr, T* to_arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		to_arr[i] = from_arr[i];
	}
}



template <typename T>
void push(List<T>^% arr, T element, int size)
{
	List<T>^ buf = arr;

	arr = gcnew List<T>(size + 1);
	for (int i = 0; i < size; i++)
	{
		arr->Add(buf[i]);
	}
	arr->Add(element);
}

String^ char_to_string(char* buf)
{
	String^ str;
	for (int i = 0; buf[i] != '\0'; i++)
	{
		str += wchar_t(buf[i]);
	}
	return str;
}

String^ char_to_string(const char* buf)
{
	String^ str;
	for (int i = 0; buf[i] != '\0'; i++)
	{
		str += wchar_t(buf[i]);
	}
	return str;
}


char* string_to_char(String^ str)
{
	return (char*)(void*)Marshal::StringToHGlobalAnsi(str);
}