#ifndef TOKEN_H
#define TOKEN_H
#include<iostream>
using namespace std;
#include"Types.h"
class Token
{
public:
    Token(){};
    virtual ~Token(){};
    virtual Types::TokenType getID()=0;
    virtual string get_token()=0;
    virtual bool execute()=0;
    virtual Token* getRight()=0;
    virtual Token* getLeft()=0;
    virtual void setRight(Token* r)=0;
    virtual void setLeft(Token* l)=0;

};

#endif // TOKEN_H
