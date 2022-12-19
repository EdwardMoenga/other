#include <string.h>
#include <iostream>

using namespace std;

string test(string s1)
{
    std::string subStr = s1.substr(0, 2);

    if (subStr == "//")
    {
        s1 = "It is a comment";
    }
    else if (subStr == "/*")
    {
        s1 = "It is a comment";
    }
    else
    {
        s1 = "It is not a comment";
    }

    return s1;
}

int main()
{
    string theString;

    cout << "Input: ";
    cin >> theString;
    cout << "Output: " << test(theString) << endl;

    system("pause");

    return 0;
}
