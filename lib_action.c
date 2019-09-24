#include <string.h>
#include<stdio.h>

#include <math.h>

// board : 10 * 10 char array : 각 행의 메모리가 연속적이진 않음
// board_size = 10
// 보드 위에서
// snake의 머리 = 3
// snake의 몸통 = 2
// food = 1

// 유저는 뱀의 다음 행동을 결정하는 [0, 3] 네 숫자 중 하나를 반환해야 함.
// 0 : left
// 1 : right
// 2 : up
// 3 : down
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

// body : length * 2 char array
//  body[0] : 머리, body[1 ~ len - 1] : 몸통
//  body[i][0] : y값, body[i][1] : x값

// head : 보고있는 방향
// remain_time : 게임 종료까지 남은 턴. 0이 되면 종료

// for sample code
struct str{
    int x,y,prev_x,prev_y;

} typedef str;
int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0, -1, 1};
int turn[] = {3, 2, 0, 1};
int X[4] = {0,0,1,-1};
int Y[4] = {1,-1,0,0};
str que[100100];
int chk[110][110];
// 함수명과 인자의 타입 수정 금지 !
int action_decision(const char **board, const char **body, int length, int head, int remain_time) {
    int find_x,find_y,trig = 1;
    int test_x,test_y;
    for(int i=0;i<10 && trig;i++){
        for(int j=0;j<10 && trig;j++){
            if(board[i][j] == 1){
                find_x = i;find_y = j;
                trig = 0;
            }
        }
    }
    int hx = body[0][0], hy = body[0][1];
    //printf("head : %d %d\n",test_x,test_y,hx,hy);
    //printf("find_x , find_y : %d %d\n",find_x,find_y);
    int st=0,ed=1,next_x=find_x,next_y=find_y;
    memset(chk,0,sizeof chk);
    que[st].x = que[st].prev_x = find_x;que[st].y = que[st].prev_y = find_y;
    while(st != ed){
        str cur = que[st];st = (st+1)%100000;
        if(hx == cur.x && hy == cur.y){
           // printf("------------is next?-------------------------------\n");
            next_x = cur.prev_x; next_y = cur.prev_y;
            break;
        }
        if(chk[cur.x][cur.y])continue;
        chk[cur.x][cur.y] = 1;
        for(int i=0;i<4;i++){
            int nx = cur.x+X[i],ny = cur.y+Y[i];
            if(nx < 0 || nx >= 10 || ny < 0 || ny >= 10)continue;
            if(board[nx][ny] != 2 && board[nx][ny] != 1 && chk[nx][ny] == 0){
                str temp;
                temp.x = nx; temp.y = ny; temp.prev_x = cur.x;temp.prev_y = cur.y;
                que[ed] = temp;
                ed =(ed+1)%100000;
            }
        }
    }

   // printf("next_x , next_y : %d %d\n",next_x,next_y);
    if(next_x == hx){
        if(next_y > hy) return RIGHT;
        else return LEFT;
    }
    else{
        if(next_x > hx) return DOWN;
        else return UP;
    }
    for(int i=0;i<4;i++){
        int nx = X[i]+hx,ny = Y[i]+hy;
        if(board[nx][ny] == 2 || nx < 0 || nx >= 10 || ny < 0 || ny >= 10)continue;
        else {
            if(nx == hx){
                if(ny > hy) return RIGHT;
                else return LEFT;
            }
            else{
                if(nx > hx) return DOWN;
                else return UP;
            }
        }
    }
    return UP;
    /*
    int cx = body[0][1],cy = body[0][0];
    int nx = cx + dx[head], ny = cy + dy[head];
    if (nx < 0 || ny < 0 || nx >= 10 || ny >= 10)
        head = turn[head];
    return head;
    */
}
