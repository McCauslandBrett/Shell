#ifndef Pipe_H
#define Pipe_H
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


class Pipe: public Token
{
public:
    Pipe();
    Pipe(string in);
    virtual ~Pipe();
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
Pipe::Pipe()
{
  left=NULL;
  right=NULL;
}
Pipe::Pipe(string in)
{
  left=NULL;
  right=NULL;
  _token=in;
}
Pipe::~Pipe()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool Pipe::execute()
{
  pid_t pid;
  int fd[2];
  bool rV=true;
  pipe(fd);
  pid=fork();
  if(pid==0)
  {
    dup2(fd[1],Types::STDOUT);
    close(fd[0]);
    close(fd[1]);
    rV=left->execute();
    exit(1);
  }
  else
  {
    pid=fork();
    if(pid==0)//child
    {
      dup2(fd[0],Types::STDIN);
      close(fd[0]);
      close(fd[1]);

      rV=right->execute();
      exit(1);
    }
    else
    {
      int stat;
      close(fd[1]);
      close(fd[0]);
      waitpid(pid,&stat,0);
      return rV;
    }
 }
}

Types::TokenType Pipe::getID()
{
  return _type;
}
string Pipe::get_token()
{
  return _token;
}

#endif // COMD_H
