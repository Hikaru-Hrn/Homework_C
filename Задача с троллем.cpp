#include <iostream>
#include <ctime>
using namespace std;



int binaryToDecimal(char*& binary) { //Функция для перевода в десятичную систему
    int decimal = 0;
    int k = 32;
    for (int i = 0; i < 6; i ++){
        decimal += (binary[i] - '0') * k;
        k /= 2;
    }

    return decimal;
}



void ShowArray(bool** arr, int rows_cols) { //Функция, выводящее доску на экран
    cout << endl;
    cout << "    1 2 3 4 5 6 7 8" << endl;
    cout << "    ———————————————" << endl;
    for (int i = 0; i < rows_cols; i++) {
        cout << i + 1 << " | ";
        for (int j = 0; j < rows_cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}



int BoardNumberFunc(bool** arr, int rows_cols) //Функция, находящее число доски
{
    int a = 0;
    char* number = new char[6];

    for (int i = 0; i < rows_cols; i++) {
        for (int j = 0; j < rows_cols; j++) {
            if (i == 4 or i == 5 or i == 6 or i == 7)
                a += arr[i][j];
        }
    }
    number[0] = (a%2) + '0';
    a = 0;

    for (int i = 0; i < rows_cols; i++) {
        for (int j = 0; j < rows_cols; j++) {
            if (i == 2 or i == 3 or i == 6 or i == 7)
                a += arr[i][j];
        }
    }
    number[1] = (a % 2) + '0';
    a = 0;

    for (int i = 0; i < rows_cols; i++) {
        for (int j = 0; j < rows_cols; j++) {
            if (i == 1 or i == 3 or i == 5 or i == 7)
                a += arr[i][j];
        }
    }
    number[2] = (a % 2) + '0';
    a = 0;

    for (int i = 0; i < rows_cols; i++) {
        for (int j = 0; j < rows_cols; j++) {
            if (j == 4 or j == 5 or j == 6 or j == 7)
                a += arr[i][j];
        }
    }
    number[3] = (a % 2) + '0';
    a = 0;

    for (int i = 0; i < rows_cols; i++) {
        for (int j = 0; j < rows_cols; j++) {
            if (j == 2 or j == 3 or j == 6 or j == 7)
                a += arr[i][j];
        }
    }
    number[4] = (a % 2) + '0';
    a = 0;

    for (int i = 0; i < rows_cols; i++) {
        for (int j = 0; j < rows_cols; j++) {
            if (j == 1 or j == 3 or j == 5 or j == 7)
                a += arr[i][j];
        }
    }
    number[5] = (a % 2) + '0';


    int boardNumber = binaryToDecimal(number);
    
    delete[] number;
    return boardNumber;
}




int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(NULL)); //делаем случайные числа по настоящему случайными

    const unsigned rows_cols = 8;// количество столбцов и строк

    bool** arr = new bool* [rows_cols];

    for (int i = 0; i < rows_cols; i++) 
        arr[i] = new bool[rows_cols]; //создаем массив
    
    for (int i = 0; i < rows_cols; i++){
        for (int j = 0; j < rows_cols; j++) 
        {
            arr[i][j] = rand() % 2; //заполняем массив
        }
    
    }

    int boardNumber = BoardNumberFunc(arr, rows_cols);

    ShowArray(arr, rows_cols);

    int col; 
    int row;

    cout << "Троль, введите номер строки: ";
    cin >> row;
    cout << "Троль, введите номер солбца: ";
    cin >> col;
    cout << endl << endl;

    int trolNumber = 8 * (row-1) + (col-1);


    int resultOfXor = trolNumber ^ boardNumber; // Используем XOR

    row = resultOfXor / 8; 
    col = resultOfXor % 8; //Находим строку и столбец ячейки, которую следует поменять.

    arr[row][col] ^= 1; //Меняем 1 на 0, или 0 на 1.

    cout << "Cтрока числа, которое следует поменять: " << row+1 << endl;
    cout << "Столбец числа, которое следует поменять: " << col+1 << endl;

    cout << endl << "Меняем на доске..." << endl;

    int result = BoardNumberFunc(arr, rows_cols);

    ShowArray(arr, rows_cols);
    

    row = result / 8 + 1;
    col = result % 8 + 1;

    cout << "Ответ: строка: " << row << " столбец: " << col << endl;


    for (int i = 0; i < rows_cols; i++)
        delete[] arr[i]; //удаляем массив
    delete[] arr;

    return 0;

}

