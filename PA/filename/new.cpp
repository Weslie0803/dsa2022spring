#include<cstdio>

char    str1[501001],
        str2[501001],
        st[201][501001];//st[row][index]


int N,M,K,tk;
void renew_ri(int,int);//renew the unit 更新数组单元值
//坐标变换函数
int x_calc(int, int);//get x from (r,i)
int y_calc(int, int);//get y from (r,i)
int r_calc(int, int);//get r from (x,y)
int i_calc(int, int);//get i from (x,y)


int main(){
    // input 处理输入
    scanf("%d%d%d",&N,&M,&K);
    scanf("%s",str1);
    scanf("%s",str2);

    if(M - N > K || N - M > K) printf("-1\n");//if |N-M|>K then print the result  若|N-M|>K则直接得出结果
    else{
        //setting edge value 填充边界值
        st[0][0] = 0;
        for(int r = 1; r <= K; r++){
            st[r][0] = r;
            st[r + 100][0] = r;
        }
        //renew inner unit 填充内部单元
        for(int i = 1; i <= N;i++){
            renew_ri(0,i);
            for(int r = 1; r <= K; r++){
                renew_ri(r,i);
                renew_ri(r+100,i);
                if((x_calc(r,i) > N || y_calc(r,i) > M) && (x_calc(r+100,i) > N || y_calc(r+100,i) > M) ){
                    break;//when all valid r renewed, break to renew next i 遍历完所有有意义的r后跳入下一个i
                }
            }
            if(st[r_calc(N,M)][i] > K) {//predict result 判断结果所在的r行是否有超过K
                tk = -1;//mark 标记
                break;
            }
        }
        int result = st[r_calc(N,M)][i_calc(N,M)];
        if(tk == -1){
            printf("-1\n");
        }
        else {
            printf("%d\n",result);
        }
    }
/*
    //print st[r][i] for debug 输出数组内容用于debug（但输出函数本身有bug）
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
    if(_x > N || _y > M) return;//invaild input 跳过非法输入
    if(str1[_x - 1] == str2[_y - 1]){//if t1 = t2 若t1 = t2
        st[_r][_i] = st[_r][_i - 1];//copy the value in upleft 填充左上方值
    }
    else{
        if(_r == K){//edge unit 边界情形
            st[_r][_i] = st[r_calc(_x-1, _y)][i_calc(_x-1, _y)] + 1;
        }
        else if(_r == K+100){//edge unit in the other side 另一侧的边界
            st[_r][_i] = st[r_calc(_x, _y-1)][i_calc(_x, _y-1)] +1;
        }
        else{//general situation 一般内部情形
            up   = st[r_calc(_x-1, _y)][i_calc(_x-1, _y)];
            left = st[r_calc(_x, _y-1)][i_calc(_x, _y-1)];
            if(up > left) st[_r][_i] = left + 1;
                else      st[_r][_i] = up + 1;
        }
    }
    if(st[_r][_i] > K) st[_r][_i] = K+1;//avoid overflow 超过K的值记为K+1，避免溢出
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