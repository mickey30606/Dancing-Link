#ifndef DDDLLLXXX
#define DDDLLLXXX

#include <iostream>
using namespace std;

#define STANDARDSIZE 324

//這個typedef 要看你要解的問題而定義 但RowHead很重要 雙向指標也很重要
typedef struct Node{
    Node *up, *down, *left, *right;
    int x, y, number;
    Node *RowHead;
}Node;

class DLX{
    public:
        bool init(int);
        Node* add_standard_node(Node *, Node *, int);
        void check_standard_node(Node *);
        bool add_member_node(int, int, int);
        void add_member_row(int [], int, int, int, int);
        Node* member_node(int, int, int, int);
    private:
        Node *head;    //這個一定要 攸關後面檢查完成條件
        Node **standard_row;    //用來快速尋找standard_row 不然要從head慢慢推 程式應該會變很慢
        int Row_tmp[4];    //因為數獨有4個條件 所以設4個來暫存要連到的standard row
        int *sum_row;
};
#endif
