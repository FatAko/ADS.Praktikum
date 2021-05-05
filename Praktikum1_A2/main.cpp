//Bearbeitet von Fatih Akoglan
#include <iostream>
#include "List.h"
using namespace std;

int main(void)
{
    int  i;
    List<int> MyList;

    // Tests f�r die Funktionen insertFront(int key) & insertBack(int key)
    for (i = 0; i < 10; i++)
    {
        MyList.insertFront(i + 1);
        MyList.insertBack(i + 100);
    }

    cout << MyList;

    //Tests f�r die Funktion search(int key)

    cout << "100: " << (MyList.search(100) ? "gefunden" : "nicht gefunden")
        << endl;
    cout << "99: " << (MyList.search(99) ? "gefunden" : "nicht gefunden")
        << endl
        << endl;

    // Tests f�r die Funktion getBack(int key)

    while (MyList.getBack(i))
        cout << i << " ";
    cout << endl << endl;

    for (i = 0; i < 10; i++) // Liste wieder "auff�llen"
    {
        MyList.insertFront(i + 1);
        MyList.insertBack(i + 100);
    }

    // Tests f�r die Funktion getFront(int key)

    while (MyList.getFront(i))
        cout << i << " ";
    cout << endl << endl;


    List<int>  MyList1, MyList2, MyList3;
    List<int>* MyList_dyn = new List<int>();

    for (i = 0; i < 10; i++)
    {
        MyList1.insertFront(i + 1);
        MyList2.insertBack(i + 100);
    }

    MyList1.format("MyList1\n<<", ", ", ">>\n\n");
    cout << MyList1;

    MyList_dyn->format("MyList_dyn\n<<", ", ", ">>\n\n");
    MyList_dyn->insertFront(-111);
    cout << *MyList_dyn;

    MyList2.format("MyList2\n<<", ", ", ">>\n\n");
    cout << MyList2;

    MyList3 = MyList1 + (*MyList_dyn) + MyList2;

    delete MyList_dyn;

    // Test f�r die Funktion size()

    cout << "Groesse von MyList3: " << MyList3.size() << endl << endl;

    MyList3.format("MyList3\n<<", ", ", ">>\n\n");
    cout << MyList3 << endl;

    // Tests f�r die Funktion swap(int key1,int key2)
    MyList3.swap(8, 103);
    MyList3.swap(100, -111);

    cout << MyList3;

    // Test f�r die Funktion del(int key)
    MyList3.del(10);
    MyList3.del(100);
    MyList3.del(109);

    cout << MyList3;

    // Tests f�r die  Funktionen insertFront(list) und insertBack(list)
    MyList3.insertFront(MyList1);
    cout << MyList3;
    MyList3.insertBack(MyList2);
    cout << MyList3;


    if (MyList3.test())
        cout << "MyList3: Zeiger OK\n\n";
    else
        cout << "MyList3: Zeiger ******Error\n\n";


    system("PAUSE");
    return 0;
}
