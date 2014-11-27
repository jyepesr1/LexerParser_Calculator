#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <string>
#include <sstream>

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

string AddNode::toEwe(){
  string comp = getLeftSubTree()->toEwe();
         comp+= getRightSubTree()->toEwe();
         comp+= "# Add\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   operator1 := M[sp+1]\n";
         comp+= "   operator1 := operator1 + operator2\n";
         comp+= "   sp := sp + one\n";
         comp+= "   M[sp+0] := operator1\n";

  return comp;
}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

string TimesNode::toEwe(){
  string comp = getLeftSubTree()->toEwe();
         comp+= getRightSubTree()->toEwe();
         comp+= "# Times\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   operator1 := M[sp+1]\n";
         comp+= "   operator1 := operator1 * operator2\n";
         comp+= "   sp := sp + one\n";
         comp+= "   M[sp+0] := operator1\n";

  return comp;
}

DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivideNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

string DivideNode::toEwe(){
  string comp = getLeftSubTree()->toEwe();
         comp+= getRightSubTree()->toEwe();
         comp+= "# Divide\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   operator1 := M[sp+1]\n";
         comp+= "   operator1 := operator1 / operator2\n";
         comp+= "   sp := sp + one\n";
         comp+= "   M[sp+0] := operator1\n";

  return comp;

}  

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

string SubNode::toEwe(){
  string comp = getLeftSubTree()->toEwe();
         comp+= getRightSubTree()->toEwe();
         comp+= "# Sub\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   operator1 := M[sp+1]\n";
         comp+= "   operator1 := operator1 - operator2\n";
         comp+= "   sp := sp + one\n";
         comp+= "   M[sp+0] := operator1\n";

  return comp;
}

ModNode::ModNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModNode::evaluate() {
   return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

string ModNode::toEwe(){
  string comp = getLeftSubTree()->toEwe();
         comp+= getRightSubTree()->toEwe();
         comp+= "# Mod\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   operator1 := M[sp+1]\n";
         comp+= "   operator1 := operator1 % operator2\n";
         comp+= "   sp := sp + one\n";
         comp+= "   M[sp+0] := operator1\n";

  return comp;
}

EqualsNode::EqualsNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int EqualsNode::evaluate(){
  int ret = getRightSubTree()->evaluate();
  return ret;
}

string EqualsNode::toEwe(){
  string comp = getRightSubTree()->toEwe();

  return comp;
}

NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
}

string NumNode::toEwe(){
  stringstream ss;
  ss << val;
  string  comp = "# push("+ss.str()+")\n";
          comp+= "   sp := sp - one\n";
          comp+= "   operator1 := "+ss.str()+"\n";
          comp+= "   M[sp+0] := operator1\n";

  return comp;
}

StoreNode::StoreNode(AST* sub) :
   UnaryNode(sub)
{}

int StoreNode::evaluate(){
  int value = getSubTree()->evaluate();
  calc->store(value);
  return value;
}

string StoreNode::toEwe(){
  string  comp = getSubTree()->toEwe();
          comp+= "# Store\n";
          comp+= "   memory := M[sp+0]\n";

  return comp;
}

IdentifierNode::IdentifierNode(string id) :
  AST(),
  id(id)
{}

int IdentifierNode::evaluate(){
  return calc->getVar(id);
}

string IdentifierNode::toEwe(){
  string  comp = "# push("+id+")\n";
          comp+= "   sp := sp - one\n";
          comp+= "   operator1 := "+id+"\n";
          comp+= "   M[sp+0] := operator1\n";

  return comp;

}

RecallNode::RecallNode() : AST() {}

int RecallNode::evaluate(){
  return calc->recall();
}

string RecallNode::toEwe(){
  string  comp = "# Recall\n";
          comp+= "   sp := sp - one\n";
          comp+= "   M[sp+0] := memory\n";

  return comp;
}

ClearNode::ClearNode() : AST() {}

int ClearNode::evaluate(){
  calc->store(0);
  return 0;
}

string ClearNode::toEwe(){
  string  comp = "# Clear\n";
          comp+= "   memory := zero\n";
          comp+= "   sp := sp - one\n";
          comp+= "   M[sp+0] := memory\n";

  return comp;

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

string PlusNode::toEwe(){
  string comp = getSubTree()->toEwe();
         comp+= "# Memory Plus\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   memory := memory + operator2\n";
         comp+= "   M[sp+0] := memory\n";

  return comp;
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

string MinusNode::toEwe(){
  string comp = getSubTree()->toEwe();
         comp+= "# Memory Minus\n";
         comp+= "   operator2 := M[sp+0]\n";
         comp+= "   memory := memory - operator2\n";
         comp+= "   M[sp+0] := memory\n";

  return comp;
}
