/*2019/11/14_V1 加密完成*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int gcd(int a, int b);

int main()
{
    int a, b, i;
    char m[1000];//明文
    char c[1000];//密文

    //1)輸入兩個整數a,b
    cout << "請輸入兩個整數a, b：" << endl;
    cin >> a >> b;

    //2）如果a和26沒有互質,回到1）
    while(gcd(a, 26) != 1) {
        cout << "a和26沒有互質, 請重新輸入兩個整數a, b:\n";
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
            c[i] = (a*(c[i] - 'A')+b)%26 + 'A';

        } else if(c[i] >= 'a' && c[i] <= 'z') {
            c[i] = (a*(m[i] - 'a')+b)%26 + 'a';
        }
    }
    c[i] = '\0';
    cout << "密文是：\n" << c << endl;

    return 0;
}

int gcd(int a, int b)
{
    int ans;
    for(int i=1; i<=a; i++) {
        if(a%i==0 && b%i==0)ans=i;
    }
    return ans;
}
