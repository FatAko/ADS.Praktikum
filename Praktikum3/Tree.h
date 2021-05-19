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
    TreeNode* anker;
    int currentNodeChronologicalID;

    void balance(TreeNode* ptr);
    bool split4Node(TreeNode* ptr);
    bool rotateTreeLeft(TreeNode* x, TreeNode* y);
    bool rotateTreeRight(TreeNode* x, TreeNode* y);
    int proofRBCriterion(TreeNode* x);

public:
    Tree();
    ~Tree();
    bool addNode(std::string name, int age, double income, int postCode);
    bool searchNode(std::string name);
    void printAll();
    void deleteAll(TreeNode* ptr);
    void printLevelOrder();
    void printLevelOrder(int parameter);
    vector<TreeNode> getNodes(std::string name);
    void LevelOrder();
    void starterProofRBCriterion();

    TreeNode* getanker(Tree& Tr) {//nur für Test
        return Tr.anker;
    }

    friend TreeNode* get_anker(Tree& TN);
};
void recolor(TreeNode* x, TreeNode* y);
void searchPreOrder(TreeNode* ptr1, int& result, string name);
void printAllPreOrder(TreeNode* ptr1);
void get_Nodes(vector<TreeNode>& vector, TreeNode* ptr, std::string name);
void printNodeList(vector<TreeNode> vector);
