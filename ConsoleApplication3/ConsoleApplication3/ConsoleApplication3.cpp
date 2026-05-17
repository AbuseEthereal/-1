#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <locale>

using namespace std;

// Функция для вычисления выражения

double computeExpression(double x, double num) 
{
    if (x <= 0) 
    {
        throw runtime_error("Ошибка: x <= 0.");
    }
    if (num == 0) 
    {
        throw runtime_error("Ошибка: деление на ноль.");
    }

    double logPart = log(abs(num / 10)) + 4;
    double cosValue = cos(x - num);
    if (cosValue == 0) 
    {
        throw runtime_error("Ошибка: косинус равен нулю.");
    }
    double firstComponent = logPart + 4 * (1 - num / cosValue);

    double sinPart = sin(log(x));
    double secondComponent = sinPart / num;

    double result = min(firstComponent, secondComponent);
    return result;
}
// Функция для ввода данных с обработкой ошибок
double getInput(const string& prompt) 
{
    double input;
    while (true) 
    {
        cout << prompt;
        cin >> input;

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем неправильный ввод
            cout << "Ошибка ввода данных, попробуйте снова." << endl;
        }
        else 
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем оставшиеся символы в буфере
            return input;
        }
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian"); // Установка русской локализации

    double startX, endX, deltaX;
    const double num = 23; // Фиксированное значение num

    // Ввод начальных и конечных значений
    startX = getInput("Введите начальное значение X: ");
    endX = getInput("Введите конечное значение X: ");

    // Ввод DeltaX с проверкой

    do
    {
        deltaX = getInput("Введите шаг изменения deltaX (положительное число): ");
        if (deltaX <= 0)
        {
            cout << "Ошибка: шаг deltaX должен быть положительным. Попробуйте снова." << endl;
        }
    } while (deltaX <= 0);

    // Заголовок таблицы

    cout << "+----------+---------------+---------------------------+" << endl;
    cout << "| Номер    |       X       |          Результат        |" << endl;
    cout << "+----------+---------------+---------------------------+" << endl;

    int rowNum = 1;
    for (double x = startX; x <= endX + 1e-9; x += deltaX) 
    { 
        try {
            double result = computeExpression(x, num);
            cout << "| " << setw(8) << rowNum
                << " | " << setw(13) << fixed << setprecision(6) << x
                << " | " << setw(25) << fixed << setprecision(6) << result << " |" << endl;
        }
        catch (const runtime_error& e) {
            cout << "| " << setw(8) << rowNum
                << " | " << setw(13) << fixed << setprecision(6) << x
                << " | " << setw(25) << e.what() << " |" << endl;
        }
        cout << "+----------+---------------+---------------------------+" << endl;
        rowNum++;
    }


    return 0;
}
