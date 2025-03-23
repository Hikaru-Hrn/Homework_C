#include "Array.h"


int main(void)
{
	setlocale(LC_ALL, "Russian");
	Array<int> arr(4);
	for (int i = 0; i < 4; i++)
		arr.insert(i + 1);
	cout << arr << endl;
	for (int i = 0; i < 8; i += 2)
		arr.insert(i, i+10); //� insert 1 �������� - ������, 2 - ��������
	cout << arr << endl;
	for (int i = 1; i < 8; i += 2)
		arr[i] = 20 + i;
	cout << arr << endl;
	for (int i = 6; i >= 0; i -= 3)
		arr.remove(i);
	cout << arr << endl;

	//���������� ��� �� ���� ������� ��������������
	Array<int> arr2;
	cin >> arr2;
	cout << arr2 << endl;

	return 0;
}