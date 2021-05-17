/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>

TreeNode::TreeNode(int nodeOrderID, int nodeChronologicalID, std::string name, int age, double income, int postCode,bool red) : nodeOrderID{ nodeOrderID }, nodeChronologicalID{ nodeChronologicalID }, name{ name }, age{ age }, income{ income }, postCode{ postCode }, red{ red } {};
void TreeNode::setNodeOrderID(int nodeOrderID) {
	this->nodeOrderID = nodeOrderID;
}
int TreeNode::getNodeOrderID() {
	return this->nodeOrderID;
}
void TreeNode::setNodeChronologicalID(int nodeChronologicalID) {
	this->nodeChronologicalID = nodeChronologicalID;
}
int TreeNode::getNodeChronologicalID() {
	return this->nodeChronologicalID;
}
void TreeNode::setName(std::string name) {
	this->name = name;
}
std::string TreeNode::getName() {
	return this->name;
}
void TreeNode::setAge(int age) {
	this->age = age;
}
int TreeNode::getAge() {
	return this->age;
}
void TreeNode::setIncome(double income) {
	this->income = income;
}
double TreeNode::getIncome() {
	return this->income;
}
void TreeNode::setPostCode(int postCode) {
	this->postCode = postCode;
}
int TreeNode::getPostCode() {
	return this->postCode;
}
void TreeNode::setLeft(TreeNode* left) {
	this->left = left;
}
TreeNode* TreeNode::getLeft() {
	return this->left;
}
void TreeNode::setRight(TreeNode* right) {
	this->right = right;
}
TreeNode* TreeNode::getRight() {
	return this->right;
}
void TreeNode::setRed(bool b) {
	this->red = b;
}
bool TreeNode::getRed() {
	return this->red;
}
void TreeNode::setParent(TreeNode* parent) {
	this->parent = parent;
}
TreeNode* TreeNode::getParent() {
	return this->parent;
}