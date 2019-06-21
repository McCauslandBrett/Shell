#include <iostream>
#include <typeinfo> //c++11
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>
#include "Tokenizer.h"
// #include "Token.h"
// #include "Comd.h"
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

using namespace std;

bool getInput(Tokenizer& Stokens);
int main(int argc, char *argv[])
{
    Tokenizer Stokens;

    while(getInput(Stokens)){
      Stokens.execute();
    }
    return 0;//a.exec();
}
bool getInput(Tokenizer& Stokens)
{
  char* cwd;
  char currdir[100];
  cwd= getcwd(currdir,sizeof(currdir));
   if ( cwd== NULL )
     cwd = getpwuid(getuid())->pw_dir;
  printf("%s", cwd);
    cout<<"$ ";
    string line;
    getline(cin,line);
    //cout<<"line:"<<line<<":"<<endl;
    if(line == "exit")
      return false;
    else{
      Stokens.set_token(line);
      return true;
    }

}
