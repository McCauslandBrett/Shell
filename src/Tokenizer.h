#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <fstream>
#include "Token.h"
#include<iostream>
#include <vector>
#include <stdlib.h>
#include<cstdlib>

#include "AND.h"
#include "OR.h"
#include "SemiColon.h"
#include "Comd.h"
#include "Comment.h"
#include "Brack.h"
#include "OutRedir.h"
#include "InRedir.h"
#include "Pipe.h"
#include "DoubleRedir.h"
enum errors { MissingParamater,missmatch};
using namespace std;
class Tokenizer //public Token
{
public:

   Tokenizer();
   ~Tokenizer();


   void set_token(string t);
   void insert_token(Token*& _root,Token*& in);
   void printIds();
   string get_token();
   bool execute();

   //parser
  void insertCommand(Token*& _root,string temp);

   void insertOR(Token*& _root,string temp);
   void insertAND(Token*& _root,string temp);
   void insertSemicolon(Token*& _root);
   void insertConnector(Token*& _root,string temp);
   void insertComment(Token*& _root,string temp);
   void insertBracket(Token*& _root,string temp);
   void deleteTree(Token* node);
   void preorderT(Token* r);
   Token* expTree(string str);

   bool inputRD(string temp);//       <
   void insertInputRD(Token*& _root);
   bool OutputRD(string temp); //     >
   void insertOutputRD(Token*& _root);
   bool DoubleOutRD(string temp);//          >>
   void insertDoubleOutRD(Token*&_root);
   bool Dpipe(string temp);
   void insertDpipe(Token*&_root);

private:
  Token* root;
  string _token;
  // int   p[2];
  // pid_t pid;
   //fd_in is pointing to the file descriptor that
   //holds the output from a previous loop.
  // int   fd_in;

   bool connector(string a);
   bool space(char a){return a==' ';}
   bool comment(char a){return a=='#';}
   bool semi(char a){return a==';';}
   bool semi(string a){return a==";";}
   bool And(string a){return a=="&&";}
   bool Or(string a){return a =="||";};
};

Tokenizer::Tokenizer()
{
  root=NULL;
  // p[2];
  // pid_t pid;
  // fd_in = 0;
}
Tokenizer::~Tokenizer()
{
  _token.clear();
  deleteTree(root);

}
Token* Tokenizer::expTree(string str)
{
  int i,j;
  j=i=0;
  str+=" ";//might need to get rid of this
  int count = str.size()-1;

  string cmdbuilder,temp,cmd,blk;
  cmd.clear();
  bool building_a_command=false;
  bool building_a_bracket=false;
  Token* head=NULL;
 for (;j< count; j++)
 {
   if(str[j]==')')//check for left
    {
      cout<<"must of mismatch parenthesis"<<endl;
      return NULL;
    }
  if(str[j]=='(') //Assumeing i==j always might need to verifie
  {

    int l=1;
    int r=0;
    j++;
    try//checking for a match
    {
     while(j<count) //find the mathcing parenthesis
     {
      if(str[j]==')')
        r++;
      else if(str[j]=='(')
        l++;
      if(l==r)
        break;
      j++;
     }
     if(j==count && l!=r)
      throw missmatch;
    }
    catch(errors)
    {
      //mismtch parenthesis
      cout<<"You missmatch your parenthesis"<<endl;
      return NULL;
    }
    Token* tk;
    tk = expTree(str.substr(i+1,((j-1)-i)));//ignore left bracket and right bracket
    insert_token(head,tk);
    i=j+1;
    // if(tk==NULL)
    //   return NULL;
    continue;
  }
  if(str[j]=='[')
  {
    j++;
    while(j<count)
    {
      if(str[j]==']')
        break;
      j++;
    }
    Token* B;
    string s=str.substr(i+1,((j-1)-i));
    B = new Brack(str.substr(i+1,((j-1)-i)));
    insert_token(head,B);
    i=j+1;
    continue;
  }
  if(space(str[j]))
  {
     if(i != j) //not just a space
     {
       temp=str.substr(i,(j-i));

       if(connector(temp))
       {
         if(building_a_command)
         {
           insertCommand(head,cmd);
           building_a_command=false;
           cmd.clear();
         }
         if(building_a_bracket)
         {
           insertBracket(head,blk);
           building_a_bracket=false;
           blk.clear();
         }
         insertConnector(head,temp);
       }
       else //not a connector
       {
         if(temp=="test")
           building_a_bracket=true;
         else
         {
           if(building_a_bracket)
           {
             temp=str.substr(i,((j+1)-i));
             blk+=temp;
           }
           else //building_a_command
           {
             temp=str.substr(i,((j+1)-i));
             building_a_command=true;
             cmd+=temp;
           }
        }
       }
     }
     i=j+1;
     continue;
    }
  if(semi(str[j]))
  {
     if(i==j) //just a SemiColon
     {
       if(building_a_command)
       {
         insertCommand(head,cmd);
         building_a_command=false;
         cmd.clear();
       }
       if(building_a_bracket)
       {
         insertBracket(head,blk);
         building_a_bracket=false;
         blk.clear();
       }
     }
     else
     {
       temp=str.substr(i,(j)-i);
       cmd+=temp;
       insertCommand(head,cmd);
       building_a_command=false;
       cmd.clear();
     }
     insertSemicolon(head);
     i=j+1;
     continue;
  }
  if(comment(str[j])) //will only make prevoiuse Command if there was a space
  {
     if(building_a_command)
     {
      insertCommand(head,cmd);
      building_a_command=false;
      cmd.clear();
     }
     if(building_a_bracket)
     {
      insertBracket(head,blk);
      building_a_bracket=false;
      blk.clear();
     }
     temp= str.substr(j,count);
     insertComment(head,temp);
     i=j=count;
     break;
   }
 }
  if(i!=j||building_a_bracket||building_a_command)
  {

    if(building_a_bracket)
    {
      temp =str.substr(i,j-i);
      blk+=temp;
      insertBracket(head,blk);
    }
    else//(building_a_command) OR single word command
    {
      temp =str.substr(i,j-i);
      cmd+=temp;
      insertCommand(head,cmd);
    }
  }
return head;
}
void Tokenizer::insertConnector(Token*& _root,string temp)
{
  if(And(temp))
    insertAND(_root,temp);
  else if(Or(temp))
    insertOR(_root,temp);
  else if(semi(temp))
    insertSemicolon(_root);
  else if(inputRD(temp))//     <
    insertInputRD(_root);//
  else if(OutputRD(temp))//    >
    insertOutputRD(_root);//
  else if(DoubleOutRD(temp))// >>
    insertDoubleOutRD(_root);
  else if(Dpipe(temp))//        |
    insertDpipe(_root);

}
bool Tokenizer::inputRD(string temp){return temp=="<";}//     <
void Tokenizer::insertInputRD(Token*& _root)
{
  Token* t = new InRedir();
   insert_token(_root,t);
}//
bool Tokenizer::OutputRD(string temp){return temp == ">";} //    >
void Tokenizer::insertOutputRD(Token*& _root)
{
  Token* t = new OutRedir();
   insert_token(_root,t);
}
bool Tokenizer::DoubleOutRD(string temp){return temp == ">>";}// >>
void Tokenizer::insertDoubleOutRD(Token*& _root)
{
  Token* t = new DoubleRedir();
   insert_token(_root,t);
}
bool Tokenizer::Dpipe(string temp){return temp == "|";}
void Tokenizer::insertDpipe(Token*& _root)
{
  Token* t = new Pipe();
   insert_token(_root,t);
}
void Tokenizer::printIds()
{
  preorderT(root);
}
void Tokenizer::preorderT(Token* r)
{
  //Command,And,Or,sem,comment
  if(r == NULL)
      return;
  if(r->getID()==Types::unary)
   cout<< "unary"<<endl;
  if(r->getID()==Types::binary)
    cout<<"Binary"<<endl;
  preorderT(r->getLeft());
  preorderT(r->getRight());
}

bool Tokenizer::connector(string a)
{
  return (And(a)||Or(a)||semi(a)||inputRD(a)||OutputRD(a)
          ||DoubleOutRD(a)||Dpipe(a));
}
bool Tokenizer::execute()
{
  if(root==NULL)
    return false;
  return root->execute();
  deleteTree(root);
  _token.clear();
}
string Tokenizer::get_token()
{
  return _token;
}
void Tokenizer::set_token(string t)
{
  _token=t;
  root=expTree(_token);
}

 void Tokenizer::insert_token(Token*& _root,Token*& in)
 {
   if(_root==NULL)
      _root = in;
   else
   {
      Token* hold;
      if(_root->getID()==Types::binary) //if a AND or a OR
      {
        if(_root->getRight()!=NULL) // if no space is free on the right
        {
           hold = _root; // hold -> [root OBJ]
          _root = in;  //  root-> in
          _root->setLeft(hold); // inLEFT-> [root OBJ]

        }
        else //space is free on the right
        {
          _root->setRight(in);

        }
      }
      if(_root->getID()==Types::unary) // if a left pointer only object
      {
        hold = _root;
        _root=in;
        _root->setLeft(hold);
      }
     }
 }
 void Tokenizer::deleteTree(Token* node)
{
    if (node == NULL) return;

    /* first delete both subtrees */
    deleteTree(node->getLeft());
    deleteTree(node->getRight());
    delete node;
}
 void Tokenizer::insertOR(Token*& _root,string temp)
 {
   Token* t = new OR(temp);
    insert_token(_root,t);
 }
 void Tokenizer::insertBracket(Token*& _root,string temp)
 {
   Token* t = new Brack(temp);
    insert_token(_root,t);
 }
 void Tokenizer::insertAND(Token*& _root,string temp)
 {
   Token* t = new AND(temp);
   insert_token(_root,t);
 }
 void Tokenizer::insertCommand(Token*& _root,string temp)
 {
   Token* t = new Comd(temp);
   insert_token(_root,t);
 }
 void Tokenizer::insertComment(Token*& _root,string temp)
 {
   Token* t = new Comment(temp);
   insert_token(_root,t);
 }
 void Tokenizer::insertSemicolon(Token*& _root)
 {
   Token* t = new Semicolon();
   insert_token(_root,t);
 }


#endif // STOKENIZE_H
