#include <iostream>
#include <cstdlib>
using namespace std;
#include "DL.h"

bool DLX::init(int number){
    number++;
    standard_row = (Node **) calloc(number, sizeof(Node *));
    sum_row = (int *) calloc(number, sizeof(int));
    success = 0;
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
    sum_row[where]++;

    return p;
}

void DLX::check_sum(void){
    for(int i=1;i<=324;i++){
        cout << sum_row[i] << endl;
    }

    return;
}

int DLX::Dance(int n){
    if(head->right == head){    //當standard都不見時 代表有解
        success++;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                answer[i][j] = tmp_answer[i][j];
            }
        }
        return success;
    }
    int min = 1000000;
    Node *where;
    for(Node *i=head->right;i!=head;i=i->right){    //找到可能數最少的standard 把它移掉
        if(sum_row[i->number] < min){
            min = sum_row[i->number], where = i;
        }
    }
    Remove(where);
    for(Node *i = where->down; i != where; i = i->down){    //再去找它下面的橫排連到的standard 把它移掉 因為代表選擇行已經選到了 所以不用那個standard了
        tmp_answer[i->x][i->y] = i->number;
        for(Node *j = i->right; j != i; j = j->right){
            Remove(j->RowHead);
        }
        Dance(n+1);
        for(Node *j = i->left; j != i; j = j->left){    //找完把它加回來
            Recover(j->RowHead);
        }
        if(success >= 2){
            break;
        }
    }
    Recover(where);

    return success;
}

void DLX::Remove(Node *k){    //先把standard移除掉 再去把下面一橫排移除掉
    k->left->right = k->right;
    k->right->left = k->left;
    for(Node *i = k->down; i != k; i = i->down){
        for(Node *j = i->right; j != i; j = j->right){
            j->up->down = j->down;
            j->down->up = j->up;
            sum_row[j->RowHead->number]--;
        }
    }
    return;
}

void DLX::Recover(Node *k){    //先把閜面一橫排加回來 再把standard加回來
    for(Node *i = k->down; i != k; i = i->down){
        for(Node *j = i->left ; j != i; j = j->left){
            j->up->down = j;
            j->down->up = j;
            sum_row[j->RowHead->number]++;
        }
    }
    k->left->right = k;
    k->right->left = k;

    return;
}

void DLX::output_answer(void){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(j == 8){
                cout << answer[i][j] << endl;
            }else{
                cout << answer[i][j] << " ";
            }
        }
    }
    return;
}
