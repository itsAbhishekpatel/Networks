#include <iostream>
#include <string>
using namespace std;

string removeLeading0s(string str)
{
    int i;
    for (i = 0; i < str.length(); ++i)
        if (str[i] == '1')
            break;
    return str.substr(i);
}

bool isZero(string str)
{
    str = removeLeading0s(str);
    if (str.length() <= 0)
        return true;
    else
        return false;
}

bool checkInput(string str)
{
    str = removeLeading0s(str);
    if (isZero(str))
    {
        cout << "\nInput Error!\nEntered bits are only zero.\n"
             << endl;
        return false;
    }
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] != '1' && str[i] != '0')
        {
            cout << "\nInput Error!\nEntered bits contain characters other than 0 or 1.\n"
                 << endl;
            return false;
        }
    }
    return true;
}
string division(string dividend, string divisor)
{
    string remainder = "";
    for (int i = 0; i <= dividend.length() - divisor.length();)
    {
        for (int j = 0; j < divisor.length(); ++j)
            dividend[i + j] = (dividend[i + j] == divisor[j]) ? '0' : '1';
        while (i < dividend.length() && dividend[i] != '1')
            ++i;
        remainder = dividend.substr(dividend.length() - divisor.length());
        return remainder;
    }
}

void CRC(string encoded, string gen)
{
    cout << "\nApplying Cyclic Redundancy Check...." << endl;
    string rem = division(encoded, gen);
    if (!isZero(rem))
        cout << "\n Errordetected!\n Remainder:" << removeLeading0s(rem);
    else
        cout << "\nNo error!\nRemainder is 0.";
}

int main()
{
    int i;
    string msg, gen, rem, temp, encoded; /*TakingInputandperformingchecksonInput*/
    cout << "\nEnter the frame:";
    cin >> msg;
    if (!checkInput(msg))
        return 1;
    cout << "Enter the generator:";
    cin >> gen;
    if (!checkInput(gen))
        return 1;
    if (gen[gen.length() - 1] != '1')
    {
        cout << "\nInput Error!\nLast bit ingenerator is not1.\n"
             << endl;
        return 1;
    }
    if (msg.length() < gen.length())
    {
        cout << "\nInput Error!\nLength of frame is smaller than length of generator.\n"
             << endl;
        return 1;
    }
    msg = removeLeading0s(msg);
    gen = removeLeading0s(gen);
    temp = msg;
    for (i = 0; i < gen.length() - 1; ++i)
        temp += "0";
    rem = division(temp, gen);
    cout << "\nRemainder:" << removeLeading0s(rem) << endl;
    encoded = msg + rem.substr(1);
    cout << "Transmitted frame:" << encoded << endl; 
    char ch;
    cout << "\nWant to add errors?(Y/N):";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        int n;
        cout << "\nEnter the index of bit to add the error:";
        cin >> n;
        encoded[n - 1] = (encoded[n - 1] == '0') ? '1' : '0';
        cout << "\nTransmitted frame with error:" << encoded << endl; 
        CRC(encoded, gen);
    }
    cout << endl
         << endl;

    return 0;
}