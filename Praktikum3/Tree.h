/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>

class Tree
{

private:
    TreeNode* anker;
    int currentNodeChronologicalID;

    void balance(TreeNode* ptr);
    bool split4Node(TreeNode* ptr);
    int printRBCriterion(TreeNode* ptr);
    bool rotateTreeRight(TreeNode* ptr1, TreeNode* ptr2);
    bool rotateTreeLeft(TreeNode* ptr1, TreeNode* ptr2);

public:
    Tree();
    ~Tree();
    bool addNode(std::string name, int age, double income, int postCode);
    bool searchNode(std::string name);
    void printAll();
    void deleteAll(TreeNode* ptr);
    TreeNode* kleinstesRechts(TreeNode* ptr, TreeNode*& ancestor);
    vector<TreeNode> getNodes(std::string name);
    bool searchOrderID(int orderID);
    
    void printLevelOrder();
    void printLevelOrder(int p);

    friend TreeNode* get_anker(Tree& TN);
};
void searchPreOrder(TreeNode* ptr1, int& result, string name);
void printAllPreOrder(TreeNode* ptr1);
void get_Nodes(vector<TreeNode>& vector, TreeNode* ptr, std::string name);
void printNodeList(vector<TreeNode> vector);
void search_OrderID(TreeNode* ptr1, int& result, int orderID);
