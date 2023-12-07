#include<cstdio>

char    str1[501000],
        str2[501000];
int N,M,K,tk,
    st[201][501000];//st[row][index]
void renew_ri(int,int);
int x_calc(int, int);
int y_calc(int, int);
int r_calc(int, int);
int i_calc(int, int);


int main(){
    scanf("%d%d%d",&N,&M,&K);
    scanf("%s",str1);
    scanf("%s",str2);

    if(M - N > K || N - M > K) printf("-1\n");
    else{
        st[0][0] = 0;
        for(int r = 1; r <= K; r++){
            st[r][0] = r;
            st[r + 100][0] = r;
        }
        for(int i = 1; i <= N;i++){
            tk = K+1;
            renew_ri(0,i);
            for(int r = 1; r <= K; r++){
                renew_ri(r,i);
                renew_ri(r+100,i);
                if((x_calc(r,i) > N || y_calc(r,i) > M) && (x_calc(r+100,i) > N || y_calc(r+100,i) > M) ){
                    break;
                }
            }
            //if(tk > K) break;
        }
        int result = st[r_calc(N,M)][i_calc(N,M)];
        if(/*tk > K || */result > K){
            printf("-1\n");
        }
        else {
            printf("%d\n",result);
        }
    }
/*
    printf("test\n");
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
            printf("%d\t", st[r_calc(i,j)][i_calc(i,j)]);
        }
        printf("\n");
    }
*/
    return 0;
}

void renew_ri(int _r, int _i){
    int _x = x_calc(_r, _i),
        _y = y_calc(_r, _i),
        up, left;
    if(_x > N || _y > M) return;
    if(str1[_x - 1] == str2[_y - 1]){
        st[_r][_i] = st[_r][_i - 1];
    }
    else{
        if(_r == K){
            st[_r][_i] = st[r_calc(_x-1, _y)][i_calc(_x-1, _y)] + 1;
        }
        else if(_r == K+100){
            st[_r][_i] = st[r_calc(_x, _y-1)][i_calc(_x, _y-1)] +1;
        }
        else{
            up   = st[r_calc(_x-1, _y)][i_calc(_x-1, _y)];
            left = st[r_calc(_x, _y-1)][i_calc(_x, _y-1)];
            if(up > left) st[_r][_i] = left + 1;
                else      st[_r][_i] = up + 1;
        }
    }
    if(tk > K) tk = st[_r][_i];
    return;
}


int r_calc(int _x, int _y){
    if(_x < _y){
        return _y - _x + 100;
    }
    else return _x - _y;
}

int i_calc(int _x, int _y){
    if(_x < _y){
        return _x;
    }
    else return _y;
}

int x_calc(int _r, int _i){
    if(_r > 100){
        return _i;
    }
    else return _r + _i;
}

int y_calc(int _r, int _i){
    if(_r > 100){
        return _r + _i - 100;
    }
    else return _i;
}