#ifndef AND_H
#define AND_H
#include<iostream>

#include "Types.h"
using namespace std;


class AND:public Token
{
public:
    AND();
    AND(string in);
    AND(Token* l,Token* r);
    virtual ~AND();
    virtual Types::TokenType getID();
    virtual string get_token();
    virtual bool execute();
    Token* getRight(){return right;}
    Token* getLeft(){return left;}
    virtual void setRight(Token* r){right=r;}
    virtual void setLeft(Token* l){left=l; }
private:
  Token* right;
  Token* left;
  static const Types::TokenType _type = Types::binary;
  string _token;

};
AND::AND()
{
  right=NULL;
  left=NULL;
  _token="&&";
}
AND::AND(string in)
{
  right=NULL;
  left=NULL;
  _token=in;
}
AND::~AND()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool AND::execute()// should be try blocked
{
 if(left==NULL||right==NULL)
  return false;
 else
  return (left->execute()) && (right->execute());
}
Types::TokenType AND::getID()
{
  return _type;
}
string AND::get_token()
{
  return _token;
}
#endif // COMD_H
