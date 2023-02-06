#include <stdio.h>
#include <stdlib.h>

// --- --- --- deque --- --- ---
#define ERROR 0

typedef struct dqNode{
    struct dqNode *forward;
    struct dqNode *back;
    int value;
}DQNode;

typedef struct deque{
    int size;
    DQNode *front;
    DQNode *back;
}Deque;

//Dequeの生成
Deque genDeque(){
    Deque dq = {
        .size = 0,
        .front = NULL,
        .back = NULL,
    };
    
    return dq;
}

//先頭にvalue(int)を追加
void pushDeq(Deque *dq, int value){
    dq->size++;
    DQNode *node = malloc(sizeof(DQNode));
    node->forward = NULL;
    node->back = dq->front;
    node->value = value;

    //Dequeの要素が無ければ末尾も更新する
    if(dq->front == NULL){
        dq->back = node;
    }else{
        dq->front->forward = node;
    }
    
    dq->front = node;
}

//先頭のvalue(int)を取り出し(破壊的処理)
int popDeq(Deque *dq){
    //frontにnodeがないときは0を返す.
    if(dq->front == NULL){
        return ERROR;
    }

    dq->size--;
    DQNode *dqfront = dq->front;
    int value = dqfront->value;

    //dqの先頭を更新
    if(dq->size == 0){
        dq->front = NULL;
        dq->back = NULL;
    }else{
        dq->front = dqfront->back;
        dq->front->forward = NULL;
    }

    //取り出したメモリの開放
    free(dqfront);

    return value;
}

//末尾にvalue(int)を追加
void push_backDeq(Deque *dq, int value){
    dq->size++;
    DQNode *node = malloc(sizeof(DQNode));
    node->forward = dq->back;
    node->back = NULL;
    node->value = value;

    //Dequeの要素が無ければ末尾も更新する
    if(dq->back == NULL){
        dq->front = node;
    }else{
        dq->back->back = node;
    }

    dq->back = node;
}

//末尾のvalue(int)を取り出し(破壊的処理)
int pop_backDeq(Deque *dq){
    //backにnodeがないときは0を返す.
    if(dq->back == NULL){
        return ERROR;
    }

    dq->size--;
    DQNode *dqback = dq->back;
    int value = dqback->value;

    //dqの先頭を更新
    if(dq->size == 0){
        dq->front = NULL;
        dq->back = NULL;
    }else{
        dq->back = dqback->forward;
        dq->back->back = NULL;
    }

    //取り出したメモリの開放
    free(dqback);
    
    return value;
}

//先頭のデータ取得(非破壊的処理)
int frontDeq(const Deque *dq){
    //frontがNULLなら例外処理
    if(dq->front == NULL){
        return ERROR;
    }
    return dq->front->value;
}

//末尾のデータ取得(非破壊的処理)
int backDeq(const Deque *dq){
    //backがNULLなら例外処理
    if(dq->back == NULL){
        return ERROR;
    }
    return dq->back->value;
}
// --- --- --- --- --- ---

// --- --- --- 問題 --- --- ---
/*
* 問題: https://atcoder.jp/contests/abc229/tasks/abc229_d
*/

#define CROSS 'X'
#define DOT '.'


int main(void){
    char S[200001];
    int K;

    scanf("%s %d", S, &K);

    int max_cain = 0;//Dequeの最長値
    int change = 0;//.を置き換えた数
    Deque dq = genDeque();

    char Sc, tmpc;
    for(int i = 0; (Sc = S[i]) != '\0'; i++){
        if(Sc == CROSS){
            pushDeq(&dq, Sc);
        }else if(Sc == DOT && change < K){
            pushDeq(&dq, Sc);
            change++;
        }else{
            while(((tmpc = pop_backDeq(&dq)) != DOT) && tmpc != ERROR);
            if(K != 0){
                pushDeq(&dq, Sc);
            }
            // change--;
        }

        if(dq.size > max_cain){
            max_cain = dq.size;
        }
    }
    printf("%d\n", max_cain);
}