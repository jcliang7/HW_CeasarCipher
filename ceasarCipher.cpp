/*
程式碼存放在此網址:
https://github.com/jcliang7/HW_CeasarCipher/blob/master/ceasarCipher.cpp#L1
*/

#include <iostream>

using namespace std;

int gcd(int a, int b);
int inverseA(int a, int b);
int bePostiveInt(int n, int shift);//讓mod之後的數字是正整數
bool checkA(int a);
bool checkInt(string s);
bool checkInput(string inputA, string inputB);
int str2int(string s);



int main()
{

    int a, b, i;
    string inputA, inputB;
    char e_or_d;
    char m[1000];//明文
    char c[1000];//密文
    char m2[1000];
    char again = 'y';
    while(again == 'Y' || again == 'y') {
        //1)輸入兩個整數a,b
        cout << "\n請輸入兩個正整數a, b：" << endl;
        do {

            cin >> inputA >> inputB;

        } while(!checkInput(inputA, inputB)); //2) 檢查輸入是否合法

        a = str2int(inputA);
        b = str2int(inputB);

        //3)選擇加密或解密
        cout << "\n請問您要執行甚麼動作?" << endl;
        cout << "加密(E), 解密(D):" << endl;
        cin >> e_or_d;

        if(e_or_d == 'E' || e_or_d == 'e') {
            //4)輸入明文m
            cout << "\n請輸入一段明文:\n";
            cin.ignore();
            cin.getline(m, 1000);

            //5) 加密 y=ax+b mod 26
            for(i=0; m[i]; i++) {
                c[i] = m[i];
                if(c[i] >= 'A' && c[i] <= 'Z') {
                    c[i] = bePostiveInt(a*(c[i] - 'A')+b, 26) + 'A';

                } else if(c[i] >= 'a' && c[i] <= 'z') {
                    c[i] = bePostiveInt(a*(c[i] - 'a')+b, 26) + 'a';
                }
            }
            c[i] = '\0';
            //6)輸出密文
            cout << "\n密文是：\n" << c << endl;
        } else   if(e_or_d == 'D' || e_or_d == 'd') {
            //7) 求inverse A;
            int invA = inverseA(a, b);
            c[0] = 0;
            //8)輸入密文
            cout << "\n請輸入一段密文:\n";
            cin.ignore();
            cin.getline(c, 1000);

            //9) 解密x = a^-1(y-b) mod 26
            for(i=0; c[i]; i++) {
                m2[i] = c[i];
                if(m2[i] >= 'A' && m2[i] <= 'Z') {
                    m2[i] = bePostiveInt(invA*(m2[i] - 'A' - b), 26) + 'A';

                } else if(m2[i] >= 'a' && m2[i] <= 'z') {
                    m2[i] = bePostiveInt(invA*(m2[i] - 'a' - b), 26 )+ 'a';
                }
            }
            m2[i] = 0;
            //10)輸出明文m
            cout << "\n明文是:\n" << m2  << endl;
        }

        cout << "\nPlay Again?" << endl;
        cout << "再玩一次(Y), 結束(N):" << endl;
        cin >> again;

    }
    return 0;
}

int gcd(int a, int b)
{
    int ans;
    if(a<0)
        a = a%26+26;
    for(int i=1; i<=a; i++) {
        if(a%i==0 && b%i==0)
            ans=i;
    }
    return ans;
}

int inverseA(int a, int b)
{
    int t[5] = {0, 0, 26, 1, a%26};
    if(t[4]<0)
        t[4] = (t[4]%26)+26;
    while(t[4] != 1) {

        t[0] = t[3];
        t[3] = t[1] - (t[3]*(t[2]/t[4]));
        t[1] = t[0];
        t[2] = t[4];
        t[4] = (a*t[3])%26;
        if(t[4]<0)
            t[4]+=26;

    }

    return t[3];
}

int bePostiveInt(int n, int shift)
{
    if((n%shift)< 0)
        return n%shift+shift;
    return n % shift;
}

bool checkA(int a)
{

    if(gcd(a, 26) != 1) {
        cout << "a和26沒有互質。\n請重新輸入兩個整數a, b:\n";
        return false;
    }
    return true;
}

bool checkInt(string s)
{
    if((s[0] == '-') || ((s[0]>='0') && (s[0]<='9'))) {
        //It's OK
    } else {
        return false;
    }
    for(int i=1; i<s.length(); i++) {
        if(s[i]>='0' && s[i]<='9')
            continue;
        else
            return false;

    }
    return true;
}

bool checkInput(string inputA, string inputB)
{
    //檢查a數不是整數
    if(!checkInt(inputA)) {
        cout << "a 不是整數，請重新輸入兩個整數a, b:" << endl;
        return false;
    }

    //檢查b是不是整數
    if(!checkInt(inputB)) {
        cout << "b 不是整數，請重新輸入兩個整數a, b:" << endl;
        return false;
    }

    //檢查(a, 26)有沒有互質
    if(checkA(str2int(inputA)))
        return true;
    else
        return false;

}

int str2int(string s)
{
    int ans=0, sign = 1;
    if(s[0] == '-')
        sign = -1;
    else
        ans += s[0]-'0';
    for(int i=1; s[i]; i++) {
        ans *= 10;
        ans += s[i]-'0';
    }
    return sign*ans;
}
