//
//  main.cpp
//  recursive sandbox
//
//  Created by Chad Smith on 12/16/18.
//  Copyright © 2018 Chad Smith. All rights reserved.
//

#include <iostream>
using namespace std;


void f(char ch)
{
    if (('A' <= ch) && (ch <= 'H'))
    {
        f(ch - 1);
        cout << ch;
    }
    else
        cout << endl;
}

int main()
{
    f('G');
    return 0;
}
