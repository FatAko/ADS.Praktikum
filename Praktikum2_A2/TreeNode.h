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
    int nodeOrderID;
    int nodeChronologicalID;
    std::string name;
    int age;
    double income;
    int postCode;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
public:
    TreeNode(int nodeOrderID, int nodeChronologicalID, std::string name, int age, double income, int postCode);
    void setNodeOrderID(int nodeOrderID);
    int getNodeOrderID();
    void setNodeChronologicalID(int nodeChronologicalID);
    int getNodeChronologicalID();
    void setName(std::string name);
    std::string getName();
    void setAge(int age);
    int getAge();
    void setIncome(double income);
    double getIncome();
    void setPostCode(int postCode);
    int getPostCode();
    void setLeft(TreeNode* left);
    TreeNode* getLeft();
    void setRight(TreeNode* right);
    TreeNode* getRight();
};

