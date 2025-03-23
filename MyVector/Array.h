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
	void Print(); //������� ������ ���� ���������

	// �������� ������ �������
	friend ostream& operator<<(ostream& out, const Array& arr) {
		out << "[";
		for (int i = 0; i < arr.size; i++) {
			out << arr.ptr[i];
			if (i < arr.size - 1) out << ", ";
		}
		out << "]";
		return out;
	}

	//�������� ����� (������� ������ ������ �������, ����� ��� ��� ��������)
	friend istream& operator>>(istream& in, Array& arr)
	{
		delete[] arr.ptr;

		// ��������� ������ �������
		int newSize;
		cout << "������� ������ �������: ";
		in >> newSize;
		if (newSize < 0) {
			throw std::invalid_argument("Size cannot be negative");
		}

		// ������������� ����� capacity � size
		arr.size = newSize;
		arr.capacity = newSize * 2; // ��������� ��� ������
		arr.ptr = new T[arr.capacity];

		// ��������� ��������
		cout << "������� ��������: ";
		for (int i = 0; i < arr.size; i++) {
			in >> arr.ptr[i];
		}

		return in;
	}

};

//����������� ��� ���������
template <class T>
Array<T>::Array()
{
	size = 0;
	capacity = DEFAULT_CAPACITY;
	ptr = new T[capacity];
}

//����������� � ����������
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

//����������
template <class T>
Array<T>::~Array()
{
	delete[] ptr;
}

//�������� �����������
template <class T>
Array<T>::Array(const Array& arr)
{
	size = arr.size;
	capacity = arr.capacity;
	ptr = new T[capacity];
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];
}

//�������� ������������
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

//�������, ������������ ���� ������� ������� �� �������
template <class T>
T& Array<T>::get(int index) const
{
	if (index < 0 or index > size) {
		throw out_of_range("Invalid insertion index");
	}

	return ptr[index];
}

//������� ���������� �������� � ������ �� �������
template <class T>
void Array<T>::insert(int index, const T& elem)
{
	if (index < 0 || index > size) {
		throw out_of_range("Invalid insertion index");
	}
	if (size == capacity) {
		// ����������� �����������
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

//������� ���������� �������� � ����� �������
template <class T>
void Array<T>::insert(const T& elem)
{
	insert(size, elem);
}

//�������� ����������
template <class T>
T& Array<T>::operator[](int index)
{
	if (index < 0 or index >= size)
		throw out_of_range("Index out of range");

	return ptr[index];
}


//������� �������� �������� �� �������
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

//�������, ������������� size
template <class T>
int Array<T>::getSize() const 
{
	return size;
}

//������� ������ ���� ���������
template <class T>
void Array<T>::Print()
{
	for (int i = 0; i < size; i++)
		cout << ptr[i] << " ";
	cout << endl;
}

#endif