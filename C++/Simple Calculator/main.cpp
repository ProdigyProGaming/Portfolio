#include <iostream>
#include <limits>
#include <string>

using namespace std;


int main()
{
    int Repeat = 1;
    cout << "Do you want to do a calculation? 1 = Yes, 2 = No" << endl;
    cin >> Repeat;
    while (Repeat == 1)
    {
        string FirstName;
        string LastName;
        int Choice = 0;


        float NumberOne;
        float NumberTwo;
        int NumberModOne;
        int NumberModTwo;
        float Total;
        int another;

        cout << "This program is a test of my skills!" << endl;
        cout << "Please enter your first name:" << endl;
        cin >> FirstName;
        cout << "So your first name is " << FirstName << "?" << endl;
        cout << "Please enter your last name:" << endl;
        cin >> LastName;
        cout << "And you last name is " << LastName << "?" << endl;
        cout << "That means your full name is " << FirstName << " " << LastName << endl;
        cout << "Now that I know your name, what calculation would you like to perform?" << endl;

        while (Choice == 0)
        {
            cout << "If you want addition, enter 1" << endl;
            cout << "If you want subtraction, enter 2" << endl;
            cout << "If you want multiplication, enter 3" << endl;
            cout << "If you want division, enter 4" << endl;
            cout << "If you want modulus, enter 5" << endl;
            cout << "If you want to quit, enter 6" << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cin >> Choice;
            switch (Choice)
            {
            case 1:
                cout << "You chose addition" << endl;

                cout << "What is the first number in the calculation?" << endl;
                cin >> NumberOne;

                cout << "What is the second number in the calculation?" << endl;
                cin >> NumberTwo;

                Total = NumberOne + NumberTwo;
                cout << "The answer is " << Total << endl;

                break;
            case 2:
                cout << "You chose subtraction" << endl;

                cout << "What is the first number in the calculation?" << endl;
                cin >> NumberOne;

                cout << "What is the second number in the calculation?" << endl;
                cin >> NumberTwo;

                Total = NumberOne - NumberTwo;
                cout << "The answer is " << Total << endl;

                break;
            case 3:
                cout << "You chose multiplication" << endl;

                cout << "What is the first number in the calculation?" << endl;
                cin >> NumberOne;

                cout << "What is the second number in the calculation?" << endl;
                cin >> NumberTwo;

                Total = NumberOne * NumberTwo;
                cout << "The answer is " << Total << endl;

                break;
            case 4:
                cout << "You chose division" << endl;

                cout << "What is the first number in the calculation?" << endl;
                cin >> NumberOne;

                cout << "What is the second number in the calculation?" << endl;
                cin >> NumberTwo;

                Total = NumberOne / NumberTwo;
                cout << "The answer is " << Total << endl;

                break;
            case 5:
                cout << "You chose modulus" << endl;

                cout << "What is the first number in the calculation?" << endl;
                cin >> NumberModOne;

                cout << "What is the second number in the calculation?" << endl;
                cin >> NumberModTwo;

                Total = NumberModOne % NumberModTwo;
                cout << "The answer is " << Total << endl;
                break;

            case 6:
                cout << "Thanks for using this program." << endl;
                return 0;
            default:
                cout << "That's not valid! Please enter 1, 2, 3 or 4:" << endl;
                break;
            }
        }
    }
    cout << "Thanks for using this program." << endl;
    return 0;
}
