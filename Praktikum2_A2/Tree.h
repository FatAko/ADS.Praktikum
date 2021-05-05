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
public:
    Tree();
    ~Tree();
    void addNode(std::string name, int age, double income, int postCode);
    bool deleteNode(int nodeOrderID);
    bool searchNode(std::string name);
    void printAll();
    void deleteAll(TreeNode* ptr);
    TreeNode* kleinstesRechts(TreeNode* ptr, TreeNode*& ancestor);
    vector<TreeNode> getNodes(std::string name);

    
    friend TreeNode* get_anker(Tree& TN);
};
void searchPreOrder(TreeNode* ptr1, int& result, string name);
void printAllPreOrder(TreeNode* ptr1);
TreeNode* searchNodenAncestor(TreeNode* ptr1, int nodeOrderID, TreeNode*& successor);
void get_Nodes(vector<TreeNode>& vector, TreeNode* ptr, std::string name);
void printNodeList(vector<TreeNode> vector);
