#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int main()
{
    setlocale(0, "");

    float resultValue = 0.0;
    float addValue = 0.0;
    cout << "Введите начальное значение: " ;
    cin >> resultValue;
    mutex calcMutex;

    thread additionThread([&]() {
        calcMutex.lock();

        cout << "Введите прибавлямое значение: ";
        cin >> addValue;
        resultValue += addValue;
        cout << "Результат сложения: " << resultValue << endl;

        calcMutex.unlock();
        });

    thread multiplicationThread([&]() {
        calcMutex.lock();

        cout << "Введите множитель: ";
        cin >> addValue;
        resultValue *= addValue;
        cout << "Результат умножения: " << resultValue << endl;

        calcMutex.unlock();
        });

    thread divisionThread([&]() {
        calcMutex.lock();

        cout << "Введите делитель: ";
        cin >> addValue;
        if (fabs(addValue - 0.0) < FLT_EPSILON)
        {
            cout << "Деление на 0 невозможно!" << endl;
            calcMutex.unlock();
            return;
        }
        resultValue /= addValue;
        cout << "Результат деления: " << resultValue << endl;

        calcMutex.unlock();
        });

    additionThread.join();
    multiplicationThread.join();
    divisionThread.join();

    cout << "Результат вычислений: " << resultValue << endl;

    return 0;
}