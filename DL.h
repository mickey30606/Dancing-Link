#ifndef DDDLLLXXX
#define DDDLLLXXX

#include <iostream>
using namespace std;

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
    private:
        Node *head;
};
#endif
