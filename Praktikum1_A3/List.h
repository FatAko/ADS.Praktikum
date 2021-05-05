//Bearbeitet von Fatih Akoglan
#pragma once
#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <iostream>
#include <string>

template <typename T> class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
    List kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        std::string start = "<< ";
        std::string zwischen = ", ";
        std::string ende = " >>\n";
    } list_form;
    Node<T>* head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
                     // -> prev der letzte Knoten
    int  list_size;  // Länge der Kette
    bool temp; // normalerweise false; ist true, wenn es sich um eine temor�re
               // Liste handelt die innerhalb der überladenen Operatoren
               // angelegt wird
public:
    List();
    List(const List& _List); // Kopie Konstruktor
    ~List();
    void insertFront(T key);     // Einfügen eines Knotens am Anfang
    void insertFront(List& _List); // Einfügen einer vorhandenen Liste am Anfang
    void insertBack(T key);      // Einfügen eines Knotesn am Ende
    void insertBack(List& _List);  // Einfügen einer vorhandenen Liste am Ende
    bool getFront(T& key);       // Entnehmen eines Knoten am Anfang
    bool getBack(T& key);        // Entnehmen eines Knoten am Ende
    bool del(T key);             // löschen eines Knotens [key]
    bool search(T key);          // Suchen eines Knoten
    bool swap(T key1, T key2); // Knoten in der Liste vertauschen
    int  size(void);               // Größe der Lise (Anzahl der Knoten)
    bool test(void);               // Überprüfen der Zeigerstruktur der Liste
    void format(const std::string& start,
        const std::string& zwischen,
        const std::string& ende);
    // Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
    // start: stirng vor der Ausgabe der Liste
    // zwischen: string zwischen Listenknoten
    // ende: string am Ende der Liste
    List& operator=(const List& _List); // Zuweisungsoperator definieren
    List& operator+(const List& List_Append); // Listen zusammenführen zu einer Liste
    template <typename T> friend std::ostream& operator<<(std::ostream& stream, List<T> const& Liste); // Ausgabeoperator überladen
    friend Node<T>* get_anker(List& l);
    friend int   get_AnzahlNodes(List& l);
};

template <typename T>
List<T>::List()
{
    // Konstruktor für eine leere Liste
    head_tail = new Node<T>;
    list_size = 0;
    temp = false;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
}

template <typename T>
List<T>::List(const List& _List)
{
    // Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen.
    list_form = _List.list_form;
    head_tail = new Node<T>;
    list_size = 0;
    temp = _List.temp;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
    Node<T>* tmp_node;
    tmp_node = _List.head_tail->next;
    while (tmp_node != _List.head_tail)
    {
        head_tail->prev =
            new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
        head_tail->prev->prev->next = head_tail->prev;
        list_size++;
        tmp_node = tmp_node->next;
    }
    if (_List.temp)
        delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                       // Operator +
}

template <typename T>
List<T>::~List()
{
    // Dekonstruktor
    // Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht
    // wird.
    Node<T>* tmp = head_tail->next;
    while (tmp != head_tail)
    {
        tmp = tmp->next;
        delete tmp->prev;
    }
    delete head_tail;
}

template <typename T>
void List<T>::insertFront(T key)
{
    // Einfuegen eines neuen Knotens am Anfang der Liste
    /*
    Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
    */
    Node<T>* neuer_Knoten = new Node<T>(key);
    if (!list_size) // Falls die Liste Leer ist...
    {
        head_tail->next = neuer_Knoten;
        head_tail->prev = neuer_Knoten; // ... sollen die Pointer next und Prev (des head_tail Knotens) auf das neue Element verweisen.
        neuer_Knoten->next = head_tail; // Da nur ein Element vorhanden ist, verweisen sowohl next als auch prev auf das Ankerobjekt 
        neuer_Knoten->prev = head_tail;
        list_size++; // Anzahl der Listenelemente beim Einfügen um eins erhöhen
    }
    else // Falls bereits Elemente in der Liste vorhanden sind
    {
        neuer_Knoten->next = head_tail->next;
        head_tail->next->prev = neuer_Knoten;
        neuer_Knoten->prev = head_tail;
        head_tail->next = neuer_Knoten;
        list_size++; // Anzahl der Listenelemente beim Einfügen um eins erhöhen
    }
}

template <typename T>
void List<T>::insertFront(List& _List)
{
    // Einfuegen der Liste _List am Anfang an einer vorhandenen Liste 
    /*
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
    */
    if (head_tail == _List.head_tail) {
        return;
    }
    else
    {
        list_size = list_size + _List.list_size; // Anzahl der Elemente aktualisieren
        (this)->head_tail->next->prev = (_List).head_tail->prev; // _Lists erstes Element wird mit dem Anker der aktuellen Liste verknüpft
        (_List).head_tail->prev->next = (this)->head_tail->next; // Das letzte Element auf _List mit dem ersten der aktuellen Liste
        (this)->head_tail->next = (_List).head_tail->next;
        (_List).head_tail->next->prev = (this)->head_tail;

        (_List).head_tail->next = (_List).head_tail; // Anker von _List auf sich selbst verweisen lassen
        (_List).head_tail->prev = (_List).head_tail;
        //return;
    }
    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */
}

template <typename T>
void List<T>::insertBack(T key)
{
    // Einfuegen eines neuen Knotens am Ende der Liste
    /*
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
    */
    Node<T>* neuer_Knoten = new Node<T>(key);
    if (!list_size) // Falls die Liste Leer ist...
    {
        head_tail->next = neuer_Knoten;
        head_tail->prev = neuer_Knoten; // ... sollen die Pointer next und Prev (des head_tail Knotens) auf das neue Element verweisen.
        neuer_Knoten->next = head_tail;
        neuer_Knoten->prev = head_tail;
        list_size++;
    }
    else
    {
        head_tail->prev->next = neuer_Knoten;
        neuer_Knoten->next = head_tail;
        neuer_Knoten->prev = head_tail->prev;
        head_tail->prev = neuer_Knoten;
        list_size++;
    }
}

template <typename T>
void List<T>::insertBack(List& _List)
{
    // Einfuegen der Liste _List am Ende einer vorhandenen Liste
    /*
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
    */
    if (head_tail == _List.head_tail) {
        return;
    }
    else
    {
        list_size = list_size + _List.list_size; // Anzahl der Elemente aktualisieren
        (_List).head_tail->next->prev = (this)->head_tail->prev;    //Das erste Element von _List mit dem Letzten aus der aktuellen Liste, Das Letzte Element aus
        (this)->head_tail->prev->next = (_List).head_tail->next;    //_List mit dem Anker vom aktuellen
        (_List).head_tail->prev->next = (this)->head_tail;
        (this)->head_tail->prev = (_List).head_tail->prev;

        _List.head_tail->next = _List.head_tail; // alte Liste referenzlos machen
        _List.head_tail->prev = _List.head_tail;
        //return;
    }
    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */
}

template <typename T>
bool List<T>::getFront(T& key)
{
    // entnehmen des Knotens am Anfang der Liste
    // der Wert wird als Parameter zurueckgegeben
    // der Knoten wird entnommen
    // im Fehlerfall wird false zurückgegeben
    if (!list_size) return false;	// leere Liste -> kein Wert
    key = head_tail->next->key;
    head_tail->next = head_tail->next->next;
    delete(head_tail->next->prev);
    head_tail->next->prev = head_tail;
    list_size--;
    return true;
    /*
        Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
        Die Methode del(key) darf nicht zum löschen benutzt werden.
    */
}

template <typename T>
bool List<T>::getBack(T& key)
{ // entnehmen des Knotens am Ende der Liste
    // der Wert wird als Parameter zurueckgegeben
    // der Knoten wird entnommen
    // im Fehlerfall wird false zurückgegeben
    if (!list_size) return false;	// leere Liste -> kein Wert
    key = head_tail->prev->key;
    head_tail->prev = head_tail->prev->prev;
    delete(head_tail->prev->next);
    head_tail->prev->next = head_tail;
    list_size--;
    return true;
    /*
        Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
        Die Methode del(key) darf nicht zum löschen benutzt werden.
    */
}

template <typename T>
bool List<T>::del(T key)
{
    // Loeschen eines gegebenen Knotens
    // im Fehlerfall wird false zurückgegeben
    if (!list_size) return false; // leere Liste -> keine Aktion
    else if (head_tail->next == head_tail->prev)
    {
        delete head_tail->next;
        list_size--;
        return true;
    }
    else
    {
        Node<T>* ptr = head_tail->next;
        while (ptr != head_tail)
        {
            if (ptr->key == key)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                delete ptr;
                list_size--;
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }
    /*
        Löschen des Knotens mit dem Wert value
    */
}

template <typename T>
bool List<T>::search(T key)
{
    // suchen eines Knotens
    // nicht gefunden -> Rueckgabe: false
    if (!list_size) return false; // leere Liste -> keine Aktion
    Node<T>* tmp = head_tail->next;
    while (tmp != head_tail)
    {
        if (tmp->key == key)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
    /*
        suchen ob ein Knoten mit dem Wert value existiert.
    */
}

template <typename T>
bool List<T>::swap(T key1, T key2)
{
    // Vertauschen von zwei Knoten
    // Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
    // im Fehlerfall wird false zurueckgegeben
    if (list_size < 2) return false; // leere oder einer Liste -> keine Aktion
    Node<T>* ptr1 = head_tail->next;
    Node<T>* ptr2 = head_tail->next;
    Node<T>* dummy1 = new Node<T>();
    Node<T>* dummy2 = new Node<T>();
    while (ptr1 != head_tail)
    {
        if (ptr1->key == key1)
        {
            break;
        }
        ptr1 = ptr1->next;
    }
    while (ptr2 != head_tail)
    {
        if (ptr2->key == key2)
        {
            break;
        }
        ptr2 = ptr2->next;
    }
    if (ptr1->key != key1 || ptr2->key != key2)
    {
        return false;
    }
    dummy1->next = ptr1->next;
    ptr1->next->prev = dummy1;
    dummy1->prev = ptr1->prev;
    ptr1->prev->next = dummy1;

    dummy2->next = ptr2->next;
    ptr2->next->prev = dummy2;
    dummy2->prev = ptr2->prev;
    ptr2->prev->next = dummy2;

    ptr1->next = dummy2->next;
    ptr1->prev = dummy2->prev;
    dummy2->prev->next = ptr1;
    dummy2->next->prev = ptr1;

    ptr2->next = dummy1->next;
    ptr2->prev = dummy1->prev;
    dummy1->prev->next = ptr2;
    dummy1->next->prev = ptr2;

    delete dummy1;
    delete dummy2;
    /*
        Vertauschen von zwei Knoten mit dem Wert value1 und dem Wert value2.
        Es duerfen nicht nur einfach die Werte in den Knoten getauscht werden!
        Die Knoten sind in der Kette umzuhaengen.
    */
    return true;
}

template <typename T>
int List<T>::size(void)
{
    // Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
    return list_size;
    /*
        Anzahl der Knoten in der Liste zurückgeben.
    */
}

template <typename T>
bool List<T>::test(void)
{
    // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
    // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
    // der Knoten überein liefert die Methode true
    Node<T>* tmp = head_tail->next;
    int   i_next = 0, i_prev = 0;
    while (tmp != head_tail)
    {
        tmp = tmp->next;
        if (i_next > list_size)
            return false;
        i_next++;
    }
    if (i_next != list_size)
        return false;
    tmp = head_tail->prev;
    while (tmp != head_tail)
    {
        tmp = tmp->prev;
        if (i_prev > list_size)
            return false;
        i_prev++;
    }
    return i_prev == i_next;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node<T>* tmp_node;
    if (list_size)
    {
        Node<T>* tmp_del;
        tmp_node = head_tail->next;
        while (tmp_node !=
            head_tail) // Alle eventuell vorhandenen Knoten in this löschen
        {
            tmp_del = tmp_node;
            tmp_node = tmp_node->next;
            delete tmp_del;
        }
        list_size = 0;
        head_tail->next = head_tail;
        head_tail->prev = head_tail;
    }
    tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
    while (tmp_node != _List.head_tail)
    {
        insertBack(tmp_node->key);
        tmp_node = tmp_node->next;
    }
    if (_List.temp)
        delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                       // Operator +
    return *this;
}

template <typename T>
List<T>& List<T>::operator+(const List<T>& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node<T>* tmp_node;
    List<T>* tmp;
    if (temp)
    { // this ist eine temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List(*this); // this ist keine temporäre Liste -> Kopie erzeugen
        tmp->temp = true;    // Merker setzten, dass es sich um eine temporäre
                             // Liste handelt
    }
    if (List_Append.list_size)
    { // anhängen der übergebenen Liste an tmp
        tmp_node = List_Append.head_tail->next;
        while (tmp_node != List_Append.head_tail)
        {
            tmp->insertBack(tmp_node->key);
            tmp_node = tmp_node->next;
        }
    }
    if (List_Append.temp)
        delete& List_Append; // wurde eine temporäre Liste übergeben, dann wird
                             // diese gelöscht
    return *tmp;
}

template <typename T>
void List<T>::format(const std::string& start,
    const std::string& zwischen,
    const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start = start;
    list_form.zwischen = zwischen;
    list_form.ende = ende;
}
template <typename T>
std::ostream& operator<<(std::ostream& stream, List<T> const& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node<T>* tmp = Liste.head_tail->next; tmp != Liste.head_tail;
        tmp = tmp->next)
        stream << tmp->key
        << (tmp->next == Liste.head_tail ? Liste.list_form.ende :
            Liste.list_form.zwischen);
    if (Liste.temp)
        delete& Liste; // wurde eine temporäre Liste übergeben, dann wird diese
                       // gelöscht
    return stream;
}


#endif

