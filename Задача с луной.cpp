#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;


streampos find_date(ifstream& file, const string& target_date) {
    string line;
    streampos left = 0, right, mid, last_valid_pos = -1;

    file.seekg(0, ios::end); //Переходим в конец файла
    right = file.tellg();  //Запоминаем размер файла
    file.clear();

    while (left < right) {
        mid = left + (right - left) / 2; //Находим середину
        file.seekg(mid, ios::beg); //перемещаемся в середину (но можем переместиться в середину строки)


        if (mid != 0) {
            getline(file, line); //Считываем строку, чтобы не оказаться в середине
        }

        streampos current_pos = file.tellg(); //запоминаем позицию начала строки
        if (!getline(file, line)) {
            break;  // Ошибка чтения
        }

        string date = line.substr(0, 8);  // дата в первых 8 символах

        if (date == target_date) {
            last_valid_pos = current_pos;  // Нашли дату - сохраняем
            right = mid;  // Ищем раньше, чтобы найти первую строку с нужной датой
        }
        else if (date < target_date) {
            left = file.tellg();  // Двигаем левую границу, нужно искать правее
        }
        else {
            right = mid;  // Двигаем правую границу, нужно искать левее
        }
    }

    return last_valid_pos;  // Возвращаем позицию первой строки с датой
}

//Функция для перевода из HMS в сеунды
void HMS_to_seconds(int& HMS, int& HMS1) {
    HMS = HMS % 100 + ((HMS / 100) % 100) * 60 + (HMS / 10000) * 3600;
    HMS1 = HMS1 % 100 + ((HMS1 / 100) % 100) * 60 + (HMS1 / 10000) * 3600;
}

//Функция для перевода в привычный формат HMS
void time_from_seconds(const int& time_in_seconds, int& hour, int& minuts, int& seconds){
    hour = time_in_seconds / 3600;
    minuts = (time_in_seconds%3600) / 60;
    seconds = time_in_seconds % 60;
}



int main()
{
    setlocale(LC_ALL, "ru");

    int choice;

    string date; //Здесь храним введенную дату
    string file_path; //Здесь храним путь к файлу


    //Есть 2 варианта открытия файла!
    cout << "Введите 1, если cpp файл находиться в одной дирректории с папкой moon, или 2, если хотите ввести путь к файлу самостоятельно: ";
    cin >> choice;
    if (choice == 1) {
        cout << "Введите дату в формате (DD.MM.YYYY): ";
        cin >> date;
        date = date.substr(6, 4) + date.substr(3, 2) + date.substr(0, 2);
        file_path = ".\\moon\\moon" + date.substr(0, 4) + ".dat";
    }
    else if (choice == 2) {
        cout << "Введите путь к файлу:" << endl;
        cin.ignore();
        getline(cin, file_path);

        cout << "Введите дату в формате (DD.MM.YYYY): "; 
        cin >> date;
        date = date.substr(6, 4) + date.substr(3, 2) + date.substr(0, 2);
    }
    else {
        cout << "Вы ввели что-то не так..." << endl;
        return 1;
    }

    ifstream file(file_path);

    if (file) { // Проверяем, удалось ли открыть файл
        cout << endl << "удалось открыть файл!" << endl << endl; 
    }
    else 
    {
        cout << "Неверно указан год или путь к файлу..." << endl;
        return 1;
    }


    streampos pos = find_date(file, date); //Используем функцию бинарного поиска

    if (pos == -1) {
        cerr << "Дата не найдена!" << endl; //проверяем дату
        return 1;
    }

    file.clear();
    file.seekg(pos);  // Переходим к найденной строке

    string line;

    bool check_sunrise = 0;
    bool check_climax = 0;
    bool check_sunset = 0; //Для проверки, нашли ли мы расвет, закат и кульминацию в нужный день


    int HMS1;
    double El0 = 0;
    double El1 = 0;
    double Az1 = 0; //В этих переменных будем хранить переменные с прошлых шагов


    
    while (getline(file, line)) {
        istringstream iss(line);
        int YMD;

        iss >> YMD; //iss помогает нам спокойно достать данные из файла

        if (YMD < stoi(date)) //если пока не дошли до нужной даты - пропускаем
            continue;
        else if (YMD > stoi(date)) //прошли нужную дату - break
            break;


        int HMS;
        double T, R, El, Az, FI, LG;
        iss >> HMS >> T >> R >> El >> Az >> FI >> LG; //iss помогает нам достать данные из файла

        




        if (El1 < 0 and El > 0 and El1 != 0) 
        {
            HMS_to_seconds(HMS, HMS1); //Функция описана выше

            int sunrise_time_in_seconds = HMS1 + (HMS - HMS1) * (-El1) / (El - El1); //вычисляем время рассвета через линейную интерполяцию
            double sunrise_Az = Az1 + (Az - Az1) * (sunrise_time_in_seconds - HMS1) / (HMS - HMS1); //вычисляем азимут так же через линейную интерполяцию

            int hour, minuts, seconds;
            time_from_seconds(sunrise_time_in_seconds, hour, minuts, seconds); //Функция описана выше

            cout << "Время восхода: " << setfill('0') << setw(2) << hour << ":" << setw(2) << minuts << ":" << setw(2) << seconds << endl;
            cout << "Азимут восхода: " << sunrise_Az << endl << endl;

            check_sunrise = 1;
        }
        else if (El1 > 0 and El < 0 and El1 != 0)
        {
            HMS_to_seconds(HMS, HMS1); // Функция описана выше

            int sunset_time_in_seconds = HMS1 + (HMS - HMS1) * (-El1) / (El - El1); //вычисляем время рассвета через линейную интерполяцию
            double sunset_Az = Az1 + (Az - Az1) * (sunset_time_in_seconds - HMS1) / (HMS - HMS1); //вычисляем азимут так же через линейную интерполяцию

            int hour, minuts, seconds;
            time_from_seconds(sunset_time_in_seconds, hour, minuts, seconds); // Функция описана выше

            cout << "Время заката: " << setfill('0') << setw(2) << hour << ":" << setw(2) << minuts << ":" << setw(2) << seconds << endl;
            cout << "Азимут заката: " << sunset_Az << endl << endl;

            check_sunset = 1;
        }

        else if (((El0 <= El1 and El1 > El) or (El0 < El1 and El1 >= El)) and El0 != 0 and check_climax == 0) {
            HMS_to_seconds(HMS, HMS1); //Функция описана выше
            int dHMS = HMS - HMS1;

            int climax_time = HMS1 + ((El - El0) / 2 / (El0 - 2 * El1 + El)) * dHMS; //Выведенная формула, для нахождения времени кульминации
            double climax_El = El1 - ((El - El0) * (El - El0)) / 4 / (El0 - 2 * El1 + El); //Выведенная формула, для нахождения максимального El кульминации

            int hour, minuts, seconds;
            time_from_seconds(climax_time, hour, minuts, seconds); //Функция описана выше

            cout << "Время кульминации: " << setfill('0') << setw(2) << hour << ":" << setw(2) << minuts << ":" << setw(2) << seconds << endl;
            cout << "Точная кульминация: " << climax_El << endl << endl;

            check_climax = 1;
        }
        

        HMS1 = HMS;
        El0 = El1;
        El1 = El;
        Az1 = Az; //Сохраняем переменные с прошлого шага




    }


    //Проверяем, все ли мы вывели
    if (check_sunrise == 0)
        cout << "Рассвет в нужный день не найден" << endl;
    if (check_climax == 0)
        cout << "Кульминация в нужный день не найдена" << endl;
    if (check_sunset == 0)
        cout << "Закат в нужный день не найден" << endl;


    file.close();
    return 0;

}