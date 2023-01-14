#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;


template <typename T>
void push(T*& arr, T element, int* size);

template <typename T> 
void arr_cpy(T* from_arr, T* to_arr, int size);


template <typename T>
void push(List<T>^% arr, T element, int size);

String^ char_to_string(char* buf);

String^ char_to_string(const char* buf);

char* string_to_char(String^ str);