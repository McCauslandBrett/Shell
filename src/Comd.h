#ifndef COMD_H
#define COMD_H
#include <iostream>
#include "string.h"
#include "Token.h"
#include "Types.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


class Comd: public Token
{
public:
    Comd();
    Comd(string in);
    virtual ~Comd();
    virtual Types::TokenType getID();
    virtual string get_token();
    virtual bool execute();
    Token* getRight(){return right;}
    Token* getLeft(){return left;}
    virtual void setRight(Token* r){right=r;}
    virtual void setLeft(Token* l){left=l; }
private:
  static const Types::TokenType _type = Types::unary;
  string _token;
  Token* left;
  Token* right;
  //HELPER FUNCTIONS
};
Comd::Comd()
{
  left=NULL;
  right=NULL;
}
Comd::Comd(string in)
{
  _token=in;
  left=NULL;
  right=NULL;
}
Comd::~Comd()
{
  right=NULL;
  left=NULL;
  _token.clear();
}
bool Comd::execute()
{
    //cout<<"cmd:"<<_token<<endl;
    bool truth = true;

    char ** tokenList = new char*[50];
    char * token = new char[_token.length()];
    strcpy(token,_token.c_str());
    char *status = strtok(token, " ");
    int i = 0;

    while(status != 0){
      tokenList[i] = status;
      status = strtok(NULL, " ");
      i++;
    }

    tokenList[i] = 0;

    pid_t pid = fork();

      if (pid == 0 && execvp(token, tokenList)){ //execution in child process
        perror("Command is invalid or does not work");
        cin.clear();
        truth = false;
      }
    else if (pid > 0){
      if (wait(0) == -1){
        perror("Waiting process failed");
        cin.clear();
        return false;
      }
    }
    delete[] tokenList; //saves memory this way
    delete[] token;
  cin.clear();
  return truth;
}
Types::TokenType Comd::getID()
{
  return _type;
}
string Comd::get_token()
{
  return _token;
}

#endif // COMD_H
