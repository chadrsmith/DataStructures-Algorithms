//
//  main.cpp
//  pointer-examples
//
//  Created by Chad Smith on 10/22/18.
//  Copyright © 2018 Chad Smith. All rights reserved.
//

#include <iostream>
#include "node.h"

using namespace std;

int  main() {
    
    Node <char> * n = NULL;
    
    insert('c', n, true);               // { c }
    insert('d', n);                     // { c, d }
    insert('f', n->pNext);              // { c, d, f }
    insert('b', n, true);               // { b, c, d, f }
    insert('e', n->pNext->pNext);       // { b, c, d, e, f }
    insert('a', n, true);               // { a, b, c, d, e, f }
    
    cout << "\t{ " << n << " }\n";

    
    return 0;
}
