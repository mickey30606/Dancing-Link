#include <iostream>
using namespace std;
#include "DL.h"

bool DLX::init(int number){
    number++;
    Node *tmp_left = NULL;
    head = NULL;
    tmp_left = head = add_standard_node(tmp_left, head, 0);
    for(int i=1;i<number;i++){
        tmp_left = add_standard_node(tmp_left, head, i);
    }

    if(head == NULL){
        return 0;
    }else{
        check_standard_node(head);
        return 1;
    }
}

Node* DLX::add_standard_node(Node* tmp_left, Node* tmp_head, int num){
    Node *p = new Node();
    p->up = p->down = p;
    p->left = tmp_left;
    p->right = tmp_head;
    p->number = num;
    if(tmp_left != NULL && tmp_head != NULL){
        tmp_left->right = p;
        tmp_head->left = p;
    }

    return p;
}

void DLX::check_standard_node(Node *head){
    for(Node *i = head->right; i != head ; i = i->right){
        cout << i->number << endl;
    }

    return;
}
