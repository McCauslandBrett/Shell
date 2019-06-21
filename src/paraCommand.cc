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

void testing();

int main()
{
    testing();

    return 0;
}

void testing()
{
  Tokenizer work;
  string a ="(ls || echo it doesnt works) && echo it works";
  cout<<a<<endl<<endl;
  work.set_token(a);
  work.execute();

  cout<<endl;
}
