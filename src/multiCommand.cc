#include <iostream>
#include <typeinfo> //c++11
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>
#include "Tokenizer.h"
#include "Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void parseTesting();

int main(int argc, const char * argv[])
{
    parseTesting();

    return 0;
}

void parseTesting()
{
  Tokenizer work;
  string a ="ls; ( echo man && ( [ -e OR.h ] && test Comd.h ) || echo no ) && ls";
  cout<<a<<endl<<endl;
  work.set_token(a);
  cout << '\n';
  work.printIds();
  work.execute();
  cout<<endl;
}
