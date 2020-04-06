#include <iostream>
using namespace std;
#include "DL.h"

int main(void){
    DLX a;
    if(a.init(324) != 1){
        cout << "Init error!!!" << endl;
        return -1;
    }

}
