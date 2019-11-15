/*2019/11/14_V1 加密完成*/
/*2019/11/15 V2 基本上可以用了。
  有些bug待修：
    1）a 是負數怎麼辦？
    2） 如果a, b不是正整數，會出錯。
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int gcd(int a, int b);
int inverseA(int a, int b);
int bePostiveInt(int n, int shift);
bool checkA(int a);



int main()
{

    int a, b, i;

    char m[1000];//明文
    char c[1000];//密文
    char m2[1000];

    //1)輸入兩個整數a,b
    cout << "請輸入兩個正整數a, b：" << endl;
    cin >> a >> b;


    //2）如果a和26沒有互質,回到1）
    while(!checkA(a)) {

        cin >> a >> b;
    }

    //3)輸入明文m
    cout << "請輸入一段信息:\n";
    cin.ignore();
    cin.getline(m, 1000);

    //4) 加密 y=ax+b mod 26
    for(i=0; m[i]; i++) {
        c[i] = m[i];
        if(c[i] >= 'A' && c[i] <= 'Z') {
            c[i] = bePostiveInt(a*(c[i] - 'A')+b, 26) + 'A';

        } else if(c[i] >= 'a' && c[i] <= 'z') {
            c[i] = bePostiveInt(a*(c[i] - 'a')+b, 26) + 'a';
        }
    }
    c[i] = '\0';
    cout << "密文是：\n" << c << endl;

    //5) 求inverse A;
    int invA = inverseA(a, b);

    //6) 解密x = a^-1(y-b) mod 26
    for(i=0; c[i]; i++) {
        m2[i] = c[i];
        if(m2[i] >= 'A' && m2[i] <= 'Z') {
            m2[i] = bePostiveInt(invA*(m2[i] - 'A' - b), 26) + 'A';

        } else if(m2[i] >= 'a' && m2[i] <= 'z') {
            m2[i] = bePostiveInt(invA*(m2[i] - 'a' - b), 26 )+ 'a';
        }
    }

    cout << "明文是:\n" << m2  << endl;

    return 0;
}

int gcd(int a, int b)
{
    int ans;
    if(a<0)a = a%26+26;
    for(int i=1; i<=a; i++) {
        if(a%i==0 && b%i==0)ans=i;
    }
    return ans;
}

int inverseA(int a, int b)
{
    int t[5] = {0, 0, 26, 1, a};
    while(t[4] != 1) {

        t[0] = t[3];
        t[3] = t[1] - (t[3]*(t[2]/t[4]));
        t[1] = t[0];
        t[2] = t[4];
        t[4] = (a*t[3])%26;
        if(t[4]<0)t[4]+=26;

    }

    return t[3];
}

int bePostiveInt(int n, int shift)
{
    if((n%shift)< 0) return n%shift+shift;
    return n % shift;
}

bool checkA(int a)
{
    if(a<0) {
        cout << "a是負數，我不會處理。\n請重新輸入兩個整數a, b：\n";
        return false;
    }
    if(gcd(a, 26) != 1) {
        cout << "a和26沒有互質。\n請重新輸入兩個整數a, b:\n";
        return false;
    }
    return true;
}
