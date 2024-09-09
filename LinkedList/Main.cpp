#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);
    
    std::cout << "Linked List: ";
    list.display();

    return 0;
}
