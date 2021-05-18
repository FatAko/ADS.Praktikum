/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>
#include <queue>

class Tree
{

private:
    ///////////////////////////////////////
    // Ihr Code hier:
    TreeNode* anker;
    int currentNodeChronologicalID;
    //
    ////////////////////////////////////

public:
    ///////////////////////////////////////
    // Ihr Code hier:
    Tree();
    ~Tree() {};
    bool addNode(string parameter_1, int parameter_2, double parameter_3, int parameter_4);
    bool searchNode(string parameter_1);
    void printAll(void);
    void printLevelOrder(int parameter); 
    void balance(TreeNode* t);
    bool split4Node(TreeNode* ptr);
    int proofRBCriterion(TreeNode* x);
    bool rotateTreeRight(TreeNode* x, TreeNode* y);
    bool rotateTreeLeft(TreeNode* a, TreeNode* b);

    void printLevelOrder(void);
    void printPreorder(TreeNode* k);
    void printInorder(TreeNode* k);

    void printInorder(TreeNode* k, string Name, bool& yn);
    void printPreorder(TreeNode* k, string Name, bool& yn);

    ////////////////////////////////////
    // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
    // bleiben!
    friend TreeNode* get_anker(Tree& TN);
};
void recolor(TreeNode* x, TreeNode* y);