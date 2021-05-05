#pragma once
class Node
{
public:
    int   key;
    Node* next, * prev;

public:
    Node();
    Node(int key, Node* next = 0, Node* prev = 0);
    ~Node();
};

