#include <iostream>
#include <stack>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <deque>
#include <map>
#include <utility>
#include <cstdio>
#include <iterator>
#include <queue>
#include <set>
#include <bitset>
using namespace std;

bool _zero;
int num (char a, int b , int c){
        int operacao;
        b -= 48;
        if (a == '+')
                operacao = c + b;
        else if (a == '-')
                operacao = c - b;
        else if (a == '*')
                operacao = c * b;
        else if (a == '/' && b == 0){
                _zero = 1;
                operacao = c;
        }
        else if (a == '/' && b != 0)
                operacao = c / b;

        return operacao;
}


int main() {
        //chamada de funcao: num (sinal, x, num)
        string prefix;
        while (getline(cin, prefix)){
                reverse(prefix.begin(), prefix.end());
                bool invalid;
                int l = prefix.length();
                char a, b, c;
                char f = prefix[0];
                if (f == '+' || f == '-' || f == '*' || f == '/'){
                        printf("Invalid expression.\n");
                        continue;
                }
                if (prefix[2] == '+' || prefix[2] == '-' || prefix[2] == '*' || prefix[2] == '/'){
                        printf("Invalid expression.\n");
                        continue;
                }
                if (prefix[l - 1] != '+' && prefix[l - 1] != '-' && prefix[l - 1] != '*' && prefix[l - 1] != '/'){
                        if (l > 1){
                                printf("Invalid expression.\n");
                                continue;
                        }
                        else if (l == 1){
                                cout << prefix[0] << endl;
                                continue;
                        }
                }
                long long numb = 0LL;
                numb += prefix[0]; //terceiro argumento da funcao
                int pos_n = 2;
                int pos_test = 2;
                int counter_n = 0;
                long long n = 0LL;
                invalid = l % 2 == 0;
                if (invalid){
                        printf("Invalid expression.\n");
                        continue;
                }
                numb -= 48;
                //chamada de funcao: num(sinal, x, num)
                for (int i = 4; i <= l; i += 2){
                        int teste = prefix[pos_test];
                        if (isdigit(teste) and not counter_n){
                                        pos_n = pos_test;
                                        counter_n += 1;
                        }
                        if (prefix[i] == '+' or prefix[i] == '-' or prefix[i] == '*' or prefix[i] == '/'){
                                n = num(prefix[i], prefix[pos_n], numb);
                                counter_n = 0;
                        }
                        if (_zero){
                                break;
                        }
                        numb = n;
                        pos_test += 2;
                }
                if (_zero){
                        cout << "Division by zero." << endl;
                        continue;
                }
                printf("The answer is %llu.\n", numb);
        }

        return 0;
}
