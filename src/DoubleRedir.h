#ifndef DoubleRedir_H
#define DoubleRedir_H
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


class DoubleRedir: public Token
{
public:
    DoubleRedir();
    DoubleRedir(string in);
    virtual ~DoubleRedir();
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
DoubleRedir::DoubleRedir()
{
  left=NULL;
  right=NULL;
  _token =">>";
}
DoubleRedir::DoubleRedir(string in)
{
  left=NULL;
  right=NULL;
  _token=in;
}
DoubleRedir::~DoubleRedir()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool DoubleRedir::execute()
{
  int p[2];
  int fd_in = 0;
  int in;
  int out;
  string outfile = right->get_token();
  int tempIn=dup(Types::STDIN);
  int tempOut=dup(Types::STDOUT);
  close(1);
  in = open(outfile.c_str(), O_WRONLY | O_APPEND
  | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  if(in==-1)
  {
    perror("Open file error");
    return false;
  }

  left->execute();
  close(in);
  dup2(tempIn,Types::STDIN);
  dup2(tempOut,Types::STDOUT);
  // exit(EXIT_FAILURE);
  return true;
}

Types::TokenType DoubleRedir::getID()
{
  return _type;
}
string DoubleRedir::get_token()
{
  return _token;
}

#endif // COMD_H
