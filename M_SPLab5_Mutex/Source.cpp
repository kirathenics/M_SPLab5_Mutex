#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int main()
{
    setlocale(0, "");

    float resultValue = 0.0;
    float addValue = 0.0;
    cout << "������� ��������� ��������: " ;
    cin >> resultValue;
    mutex calcMutex;

    thread additionThread([&]() {
        calcMutex.lock();

        cout << "������� ����������� ��������: ";
        cin >> addValue;
        resultValue += addValue;
        cout << "��������� ��������: " << resultValue << endl;

        calcMutex.unlock();
        });

    thread multiplicationThread([&]() {
        calcMutex.lock();

        cout << "������� ���������: ";
        cin >> addValue;
        resultValue *= addValue;
        cout << "��������� ���������: " << resultValue << endl;

        calcMutex.unlock();
        });

    thread divisionThread([&]() {
        calcMutex.lock();

        cout << "������� ��������: ";
        cin >> addValue;
        if (fabs(addValue - 0.0) < FLT_EPSILON)
        {
            cout << "������� �� 0 ����������!" << endl;
            calcMutex.unlock();
            return;
        }
        resultValue /= addValue;
        cout << "��������� �������: " << resultValue << endl;

        calcMutex.unlock();
        });

    additionThread.join();
    multiplicationThread.join();
    divisionThread.join();

    cout << "��������� ����������: " << resultValue << endl;

    return 0;
}