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
    private:
        Node *head;    //這個一定要 攸關後面檢查完成條件
        Node **standard_row;
};
#endif
