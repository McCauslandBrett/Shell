#ifndef BRACK_H
#define BRACK_H
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "Token.h"
#include "Types.h"
#include "stdio.h"
#include "stdlib.h"
using namespace std;


class Brack: public Token
{
public:
    Brack();
    Brack(string in);
    virtual ~Brack();
    virtual Types::TokenType getID();
    virtual string get_token();
    virtual bool execute();
    virtual Token* getRight(){return right;}
    virtual Token* getLeft(){return left;}
    virtual void setRight(Token* r){right=r;}
    virtual void setLeft(Token* l){left=l; }
private:
  static const Types::TokenType _type = Types::binary;
  Token* left;
  Token* right;
  string _token;
  //HELPER FUNCTIONS
};
Brack::Brack()
{
  left=NULL;
  right=NULL;
}
Brack::Brack(string in)
{
  left=NULL;
  right=NULL;
  _token=in;
}
Brack::~Brack()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool Brack::execute()
{
  string brackpar1 = "";
  string brack1 = "";
  if(_token[0]==' '){
    brack1 = _token.substr(1,_token.size()-2);
  }
  else{
    brack1 = _token.substr(0,_token.size());
    if(brack1[brack1.size()-1] == ' '){
      brack1 = _token.substr(0,_token.size()-1);
    }
  }
  string opbrack1 = brack1.substr(0,2);

  if(opbrack1 == "-e" || opbrack1 == "-f" || opbrack1 == "-d")
    brackpar1 = brack1.substr(3,_token.size()-3);
  else{
    opbrack1 = "-e";
    brackpar1 = brack1.substr(0,brack1.size());
  }

  const char* brack = brack1.c_str();
  const char* brackpar = brackpar1.c_str();
  const char* opbrack = opbrack1.c_str();

  struct stat buf;
  if(!strncmp(opbrack,"-e",2)){
    if(stat(brackpar, &buf) == 0 && S_ISDIR(buf.st_mode))
      cout << "(TRUE)" << endl;
    else if(stat(brackpar, &buf) == 0 && S_ISREG(buf.st_mode))
      cout << "(TRUE)" << endl;
    else{
      cout << "(FALSE)" << endl;
    }
  }
  else if(!strncmp(opbrack,"-d",2)){
    if(stat(brackpar, &buf) == 0 && S_ISDIR(buf.st_mode))
      cout << "(TRUE)" << endl;
    else{
      cout << "(FALSE)" << endl;
    }
  }
  else if(!strncmp(opbrack,"-f",2)){
    if(stat(brackpar, &buf) == 0 && S_ISREG(buf.st_mode))
      cout << "(TRUE)" << endl;
    else{
      cout << "(FALSE)" << endl;
    }
  }
  return true;
}

Types::TokenType Brack::getID()
{
  return _type;
}
string Brack::get_token()
{
  return _token;
}

#endif // COMD_H
