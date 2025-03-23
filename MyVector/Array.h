#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <stdexcept>
using namespace std;


template <class T>
class Array
{
private:
	T* ptr;
	int size, capacity;
	static const int DEFAULT_CAPACITY = 10;
public:
	Array();
	Array(int size);
	~Array();
	Array(const Array& arr);

	Array& operator =(const Array& arr);
	T& operator [](int index);

	T& get(int index) const;
	void insert(int index, const T& elem);
	void insert(const T& elem);
	void remove(int index);
	int getSize() const;
	void Print(); //Функция вывода всех элементов

	// Оператор вывода массива
	friend ostream& operator<<(ostream& out, const Array& arr) {
		out << "[";
		for (int i = 0; i < arr.size; i++) {
			out << arr.ptr[i];
			if (i < arr.size - 1) out << ", ";
		}
		out << "]";
		return out;
	}

	//Оператор ввода (сначала вводим размер массива, затем все его элементы)
	friend istream& operator>>(istream& in, Array& arr)
	{
		delete[] arr.ptr;

		// Считываем размер массива
		int newSize;
		cout << "Введите размер массива: ";
		in >> newSize;
		if (newSize < 0) {
			throw std::invalid_argument("Size cannot be negative");
		}

		// Устанавливаем новые capacity и size
		arr.size = newSize;
		arr.capacity = newSize * 2; // Удваиваем для запаса
		arr.ptr = new T[arr.capacity];

		// Считываем элементы
		cout << "Введите элементы: ";
		for (int i = 0; i < arr.size; i++) {
			in >> arr.ptr[i];
		}

		return in;
	}

};

//Конструктор без аргумента
template <class T>
Array<T>::Array()
{
	size = 0;
	capacity = DEFAULT_CAPACITY;
	ptr = new T[capacity];
}

//Конструктор с аргументом
template <class T>
Array<T>::Array(int capacity)
{
	size = 0;
	if (capacity <= 0)
		this->capacity = DEFAULT_CAPACITY;
	else
		this->capacity = capacity;
	ptr = new T[capacity];

}

//Деструктор
template <class T>
Array<T>::~Array()
{
	delete[] ptr;
}

//Оператор копирования
template <class T>
Array<T>::Array(const Array& arr)
{
	size = arr.size;
	capacity = arr.capacity;
	ptr = new T[capacity];
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];
}

//Оператор присваивания
template <class T>
Array<T>& Array<T>::operator=(const Array& arr)
{
	if (this == &arr)
		return *this;

	delete[] ptr;
	capacity = arr.capacity;
	ptr = new T[capacity];
	size = arr.size;
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];

	return *this;
}

//Функция, возвращающая один элемент массива по индексу
template <class T>
T& Array<T>::get(int index) const
{
	if (index < 0 or index > size) {
		throw out_of_range("Invalid insertion index");
	}

	return ptr[index];
}

//Функция добавления элемента в массив по индексу
template <class T>
void Array<T>::insert(int index, const T& elem)
{
	if (index < 0 || index > size) {
		throw out_of_range("Invalid insertion index");
	}
	if (size == capacity) {
		// Увеличиваем вместимость
		capacity *= 2;
	}

	T* newPtr = new T[capacity];
	for (int i = 0; i < size; i++)
		newPtr[i] = ptr[i];

	delete[] ptr;
	ptr = newPtr;

	ptr[index] = elem;
	size++;
}

//Функция добавления элемента в конец массива
template <class T>
void Array<T>::insert(const T& elem)
{
	insert(size, elem);
}

//Оператор индексации
template <class T>
T& Array<T>::operator[](int index)
{
	if (index < 0 or index >= size)
		throw out_of_range("Index out of range");

	return ptr[index];
}


//Функция удаления элемента из массива
template <class T>
void Array<T>::remove(int index)
{
	if (index < 0 or index >= size) {
		throw out_of_range("Invalid removal index");
	}
	for (int i = index; i < size - 1; i++) {
		ptr[i] = ptr[i + 1];
	}
	size--;
}

//Функция, возвращающаяя size
template <class T>
int Array<T>::getSize() const 
{
	return size;
}

//Функция вывода всех элементов
template <class T>
void Array<T>::Print()
{
	for (int i = 0; i < size; i++)
		cout << ptr[i] << " ";
	cout << endl;
}

#endif