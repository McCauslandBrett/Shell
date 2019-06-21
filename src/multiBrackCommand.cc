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
  string a ="[ AND.h ]; test -f workingTestDir/file2.txt && echo man";
  cout<<a<<endl<<endl;
  work.set_token(a);
  work.execute();

  cout<<endl;
}
