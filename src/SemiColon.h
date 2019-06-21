#ifndef SEMICOLON_H
#define SEMICOLON_H
#include<iostream>

#include"Types.h"
using namespace std;


class Semicolon:public Token
{
public:
    Semicolon();
    Semicolon(string in);
    virtual ~Semicolon();
    virtual Types::TokenType getID();
    virtual string get_token();
    virtual bool execute();
    Token* getRight(){return right;}
    Token* getLeft(){return left;}
    virtual void setRight(Token* r){right=r;}
    virtual void setLeft(Token* l){left=l;}
private:
  Token* right;
  Token* left;

  static const Types::TokenType _type = Types::binary;
  string _token;
};
Semicolon::Semicolon()
{
  _token=";";
  right=NULL;
  left=NULL;
}
Semicolon::Semicolon(string in)
{
  _token=in;
  right=NULL;
  left=NULL;
}

Semicolon::~Semicolon()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool Semicolon::execute()
{
    if(left != NULL)
     left->execute();
    if(right != NULL)
     right->execute();
  return true;
}
Types::TokenType Semicolon::getID()
{
  return _type;
}
string Semicolon::get_token()
{
  return _token;
}
#endif // COMD_H
