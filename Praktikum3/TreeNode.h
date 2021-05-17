/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode
{

private:
    int nodeOrderID, nodeChronologicalID, postCode, age;
    double income;
    bool red;
    TreeNode* left = nullptr, * right = nullptr, * parent = nullptr;
    std::string name;
public:
    TreeNode(int nodeOrderID, int nodeChronologicalID, std::string name, int age, double income, int postCode, bool red);
    void setNodeOrderID(int nodeOrderID);
    void setNodeChronologicalID(int nodeChronologicalID);
    void setName(std::string name);
    void setAge(int age);
    void setPostCode(int postCode);
    void setLeft(TreeNode* left);
    void setRight(TreeNode* right);
    void setIncome(double income);
    void setRed(bool b);
    void setParent(TreeNode* parent);
    int getNodeOrderID();
    int getNodeChronologicalID();
    int getPostCode();
    int getAge();
    bool getRed();
    double getIncome();
    TreeNode* getLeft();
    TreeNode* getRight();
    TreeNode* getParent();
    std::string getName();
};

