#include <iostream>
#include "List.h"
using namespace std;

int main(void)
{
    List* list1 = new List();
    List* list2 = new List();
    List* list3 = new List();
    List test;
    List test2;

    cout << "Test insertFront(key): " << endl;
    list1->insertFront(5);
    list1->insertFront(4);
    list1->insertFront(3);
    list1->insertFront(2);
    list1->insertFront(1);
    list1->ausgabe();
    cout << endl;

    cout << "Test insertBack(key): " << endl;
    list2->insertBack(5);
    list2->insertBack(4);
    list2->insertBack(3);
    list2->insertBack(2);
    list2->insertBack(1);
    list2->ausgabe();
    cout << endl;

    cout << "Test getFront(&key): " << endl;
    int key = 0;
    list1->getFront(key);
    list1->ausgabe();
    cout << endl;

    cout << "Test getback(&key): " << endl;
    list2->getBack(key);
    list2->ausgabe();
    cout << endl;

    cout << "Test size(): " << endl;
    int size = 0;
    size = list1->size();
    cout << "list1 size: " << size << endl;
    size = list2->size();
    cout << "list2 size: " << size << endl;
    cout << endl;


    cout << "Test search(): " << endl;
    cout << list1->search(3) << endl;
    cout << list1->search(99) << endl;
    cout << list2->search(3) << endl;
    cout << list2->search(99) << endl;
    cout << endl;

    cout << "Test swap(key1 key2): " << endl;
    cout << "vorher: " << endl;
    list1->ausgabe();
    cout << endl;
    list2->ausgabe();
    cout << endl;
    list1->swap(2, 5);
    list2->swap(3, 4);
    cout << "list 1: ";
    list1->ausgabe();
    cout << endl;
    cout << "list 2: ";
    list2->ausgabe();
    cout << endl; cout << endl;
    
    /*
    cout << "Test del(&key): " << endl;
    list1->del(2);
    list2->del(2);
    cout << "list 1: ";
    list1->ausgabe();
    cout << endl;
    cout << "list 2: ";
    list2->ausgabe();
    cout << endl; cout << endl;

    cout << "Test search(key): " << endl;
    if (list1->search(5) == true && list2->search(4) == true) {
        cout << "Korrekt!" << endl;
    }
    cout << endl;

    cout << "Test insertFront(list): " << endl;
    test.insertFront(99);
    test.insertFront(44);
    test.insertFront(22);
    test.insertFront(55);
    test.insertFront(66);
    test2.insertFront(33);
    test2.insertFront(33);
    cout << "test: ";
    test.ausgabe();
    cout << endl;
    cout << "list1: ";
    list1->ausgabe();
    cout << endl;
    list1->insertFront(test);
    cout << endl;
    cout << "list1: ";
    list1->ausgabe();
    cout << endl;
    cout << "test: ";
    test.ausgabe();
    cout << endl; cout << endl;
    list1->getFront(key);
    list1->getFront(key);
    list1->getFront(key);
    list1->getFront(key);
    list1->getFront(key);

    cout << "Test insertBack(list): " << endl;
    test.insertFront(99);
    test.insertFront(99);
    test.insertFront(99);
    test.insertFront(99);
    test.insertFront(99);
    test2.insertFront(33);
    test2.insertFront(33);
    cout << "test: ";
    test.ausgabe();
    list1->insertBack(test);
    cout << endl;
    cout << "list1: ";
    list1->ausgabe();
    cout << endl;
    cout << "test: ";
    test.ausgabe();
    cout << endl; cout << endl;
    */


    system("PAUSE");
    return 0;
}
