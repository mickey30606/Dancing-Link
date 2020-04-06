#include <iostream>
#include <cstdlib>
using namespace std;
#include "DL.h"

bool DLX::init(int number){
    number++;
    standard_row = (Node **) calloc(number, sizeof(Node *));
    sum_row = (int *) calloc(number, sizeof(int));
    Node *tmp_left = NULL;
    head = NULL;
    tmp_left = head = add_standard_node(tmp_left, head, 0);
    for(int i=1;i<number;i++){
        tmp_left = add_standard_node(tmp_left, head, i);
    }

    if(head == NULL){
        return 0;
    }else{
        //check_standard_node(head);
        return 1;
    }
}

Node* DLX::add_standard_node(Node* tmp_left, Node* tmp_head, int num){
    Node *p = new Node();
    p->up = p->down = p;
    p->left = tmp_left;
    p->right = tmp_head;
    p->number = num;
    standard_row[num] = p;
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
    for(int i=0;i<=324;i++){
        cout << standard_row[i]->number << endl;
    }

    return;
}

bool DLX::add_member_node(int x, int y, int number){
    //每一種的問題這邊都不一樣 因為數獨共4個條件所以每個數字會跑4次
    int k=0;    //用來計數的
    if(number != 0){
        Row_tmp[k++] = x*9 + y +1;    //1~81
        Row_tmp[k++]= 9*9 + x*9 + number;    //在一個橫排裡有什麼數字
        Row_tmp[k++] = 2*9*9 + y*9 + number;    //在一個直行裡有什麼數字
        Row_tmp[k++] = 3*9*9 + x/3*3*9 + y/3*9 + number;    //在一個宮格里有什麼數字
        add_member_row(Row_tmp, k, x, y, number);
        k=0;
    }else{
        for(int i=1;i<10;i++){
            Row_tmp[k++] = x*9 + y +1;    //1~81
            Row_tmp[k++]= 9*9 + x*9 + i;    //在一個橫排裡有什麼數字
            Row_tmp[k++] = 2*9*9 + y*9 + i;    //在一個直行裡有什麼數字
            Row_tmp[k++] = 3*9*9 + x/3*3*9 + y/3*9 + i;    //在一個宮格里有什麼數字
            add_member_row(Row_tmp, k, x, y, i);
            k=0;
        }
    }

    return 1;
}

void DLX::add_member_row(int Row[], int k, int x, int y, int number){
    Node *tmp[k];
    for(int i=0;i<k;i++){
        tmp[i] = member_node(Row[i], x, y, number);
    }
    for(int i=0;i<k;i++){
        if(i==0){
            tmp[i]->right = tmp[i+1];
            tmp[i]->left = tmp[i+k-1];
        }else if(i == k-1){
            tmp[i]->right = tmp[0];
            tmp[i]->left = tmp[i-1];
        }else{
            tmp[i]->right = tmp[i+1];
            tmp[i]->left = tmp[i-1];
        }
    }

    return;
}

Node * DLX::member_node(int where, int x, int y, int number){
    Node *p = new Node();
    p->left = p->right = p;
    p->RowHead = standard_row[where];
    p->x = x, p->y = y, p->number = number;
    if(sum_row[where] == 0){
        standard_row[where]->down = standard_row[where]->up = p;
        p->up = p->down = standard_row[where];
    }else{
        p->up = standard_row[where]->up;
        p->down = standard_row[where];
        standard_row[where]->up->down = p;
        standard_row[where]->up = p;
    }

    return p;
}
