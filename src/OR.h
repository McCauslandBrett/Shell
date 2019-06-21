#ifndef OR_H
#define OR_H
#include<iostream>

#include"Types.h"
using namespace std;


class OR: public Token
{
public:
    OR();
    OR(Token* l,Token* r);
    OR(string in);
    virtual ~OR();
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
OR::OR()
{
  right=NULL;
  left=NULL;
  _token="||";
}
OR::OR(string in)
{
  left=NULL;
  right=NULL;
  _token = in;
}
OR::~OR() // this will eventually need to be implemented
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool OR::execute()
{
  return (left->execute())||(right->execute());

}
Types::TokenType OR::getID()
{
  return _type;
}
string OR::get_token()
{
  return _token;
}
#endif // COMD_H
