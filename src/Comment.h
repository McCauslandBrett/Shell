#ifndef COMMENT_H
#define COMMENT_H
#include<iostream>
#include "Token.h"
#include"Types.h"
#include "stdio.h"
#include "stdlib.h"
using namespace std;


class Comment: public Token
{
public:
    Comment();
    Comment(string in);
    virtual ~Comment();
    virtual Types::TokenType getID();
    virtual string get_token();
    virtual bool execute();
    virtual Token* getRight(){return right;}
    virtual Token* getLeft(){return left;}
    virtual void setRight(Token* r){right=r;}
    virtual void setLeft(Token* l){left=l; }
private:
  static const Types::TokenType _type = Types::unary;
  Token* left;
  Token* right;
  string _token;
  //HELPER FUNCTIONS
};
Comment::Comment()
{
  left=NULL;
  right=NULL;
}
Comment::Comment(string in)
{
  left=NULL;
  right=NULL;
  _token=in;
}
Comment::~Comment()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool Comment::execute()
{
  if(left!=NULL)
    left->execute();
  return true;
}

Types::TokenType Comment::getID()
{
  return _type;
}
string Comment::get_token()
{
  return _token;
}

#endif // COMD_H
