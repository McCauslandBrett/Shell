#ifndef InRedir_H
#define InRedir_H
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <fcntl.h>
#include "Token.h"
#include "Types.h"
#include "stdio.h"
#include "stdlib.h"
using namespace std;


class InRedir: public Token
{
public:
    InRedir();
    InRedir(string in);
    virtual ~InRedir();
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
InRedir::InRedir()
{
  left=NULL;
  right=NULL;
  _token="<";
}
InRedir::InRedir(string in)
{
  left=NULL;
  right=NULL;
  _token=in;
}
InRedir::~InRedir()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool InRedir::execute()
{
  int in;
  string outfile = right->get_token();
  if(outfile[outfile.size()-1] == ' '){
    outfile = outfile.substr(0,outfile.size()-1);
  }

  int tempIn=dup(0);
  // int tempOut=dup(Types::STDOUT);
  in = open(outfile.c_str(), O_RDONLY);
  if(in==-1)
  {
    perror("Open file error");
    return false;
  }
  close(0);
  dup2(in,0);
  bool t =left->execute();
  close(0);
  dup2(tempIn,0);
  // dup2(tempOut,Types::STDOUT);

  return t;
}

Types::TokenType InRedir::getID()
{
  return _type;
}
string InRedir::get_token()
{
  return _token;
}

#endif // COMD_H
