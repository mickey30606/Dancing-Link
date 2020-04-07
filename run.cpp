#include <iostream>
using namespace std;
#include "DL.h"

#define STANDARDSIZE 324

int main(void){
    DLX a;
    if(a.init(STANDARDSIZE) != 1){
        cout << "Init error!!!" << endl;
        return -1;
    }
    //進行讀入條件 以數獨作為演示
    //當然這要看你對標頭列（324）的定義才能決定你增加列時要的資料
    int sudoku[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin >> sudoku[i][j];
            if(a.add_member_node(i, j, sudoku[i][j]) != 1){
                cout << "add_member_node error!!!" << endl;
                return -1;
            }
        }
    }
    int n = a.Dance(0);
    if(n == 1){
        cout << "1" << endl;
        a.output_answer();
    }else{
        cout << n << endl;
    }

    //a.check_sum();

}
