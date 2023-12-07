/***
 * 测例生成器，根据命令行参数生成具有一定规律的测例
*/

#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

int n_insert = 10,
    n_query = 10;
int on = 0;
string input = "input.txt",
    output = "output.txt";
struct Ientry
{
    string str;
    int num;
};
struct Qentry
{
    string str;
};

vector<Ientry> I;
vector<Qentry> Q;


//设置输入文件
void set_input(char[]);

//设置插入数目
void set_insert(char[]);

//设置查询数目
void set_query(char[]);

//设置输出文件路径
void set_output(char[]);

//设置命中率
void set_on();

//生成数据
void makedata();

int main(int argc, char** argv){
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-input") == 0){
            set_input(argv[i+1]);
        }
        else if(strcmp(argv[i], "-insert") == 0){
            set_insert(argv[i+1]);
        }
        else if(strcmp(argv[i], "-query") == 0){
            set_query(argv[i+1]);
        }
        else if(strcmp(argv[i], "-output") == 0){
            set_output(argv[i+1]);
        }
        else if(strcmp(argv[i], "-on") == 0){
            set_on();
        }
    }

    cout << "n_insert = " << n_insert << endl;
    cout << "n_query = "<< n_query << endl;
    cout << "input file -> " << input << endl;
    cout << "output file -> " << output << endl;

    makedata();
    return 0;
}

void set_input(char a[]){
    if(strcmp(a, "hdu") == 0){
        input = "hdu.txt";
    }
    else if(strcmp(a,"poj") == 0){
        input = "poj.txt";
    }
    else{
        printf("-input error!\n");
    }
}

void set_insert(char a[]){
    n_insert = atoi(a);
    if(n_insert <= 0){
        printf("-insert error! Please input a valid number.\n");
    }
}

void set_query(char a[]){
    n_query = atoi(a);
    if(n_query <= 0){
        printf("-query error! Please input a valid number.\n");
    }
}

void set_output(char a[]){
    output = a;
}

void set_on(char a[]){
    on = 1;
}

void makedata(){
    srand((unsigned int)time(NULL));
    int index, a,b;
    string str;
    ifstream fin;
    ofstream fout;
    fin.open(input);
    for(int i = 0; i < 500000; i++){
        fin >> index >> str >> a >> b;
        if(on == 0){
            if(rand() % 10 < 5 && I.size() < n_insert){
                I.push_back({str,index});
            }
            if(rand() % 10 < 5 && Q.size() < n_query){
                Q.push_back({str});
            }
        }
        else{
            if(rand() % 4 < 3 && I.size() < n_insert&& Q.size() < n_query){
                I.push_back({str,index});
                Q.push_back({str});
            }
            else{
                if(rand() % 10 < 3 && I.size() < n_insert){
                    I.push_back({str,index});
                }
                if(rand() % 10 < 3 && Q.size() < n_query){
                    Q.push_back({str});
                }
            }
        }
        if(I.size() >= n_insert && Q.size() >= n_query) break;
    }
    fin.close();
    fout.open(output);
    for(Ientry a: I){
        fout << "0 " << a.str << " " << a.num << endl;
    }
    for(Qentry a: Q){
        fout << "1 " << a.str << endl;
    }
    fout << 2 << endl;
    fout.close();
}