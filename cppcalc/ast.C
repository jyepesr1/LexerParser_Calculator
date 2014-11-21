#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <string>

// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivideNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

ModNode::ModNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModNode::evaluate() {
   return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

EqualsNode::EqualsNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int EqualsNode::evaluate(){
  int ret = getRightSubTree()->evaluate();
  return ret;
}

NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
} 

StoreNode::StoreNode(AST* sub) :
   UnaryNode(sub)
{}

int StoreNode::evaluate(){

  int value = getSubTree()->evaluate();
  calc->store(value);
  return value;
}

IdentifierNode::IdentifierNode(string id) :
  AST(),
  id(id)
{}

int IdentifierNode::evaluate(){
  return calc->getVar(id);
}

RecallNode::RecallNode() : AST() {}

int RecallNode::evaluate(){
  return calc->recall();
}

ClearNode::ClearNode() : AST() {}

int ClearNode::evaluate(){
  calc->store(0);
  return 0;
}

PlusNode::PlusNode(AST* sub) : 
    UnaryNode(sub)
{}

int PlusNode::evaluate(){
    int value = getSubTree()->evaluate();
    int suma = calc->recall() + value;
    calc->store(suma);

    return suma;
}

MinusNode::MinusNode(AST* sub) :
    UnaryNode(sub)
{}

int MinusNode::evaluate(){
    int value = getSubTree()->evaluate();
    int resta = calc->recall() - value;
    calc->store(resta);
    
    return resta;
}