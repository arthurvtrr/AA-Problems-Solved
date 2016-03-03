 #include <cstdio>
					#include <stack>
					#include <string.h>

                        using namespace std;

       									 int main(){

        									char qwert[10001];

                           while(scanf("%s",qwert) != EOF){

                            stack <int> pilha;

                             bool jujuba = true;

                             for(int i=0 ; i< strlen(qwert) ; i++){

                               if(qwert[i] == '('){
                                        pilha.push(1);
                               }

                               if(qwert[i] == ')' && pilha.empty()){

                               			jujuba = false;

                               }

                               else if(qwert[i] == ')'){

                               			pilha.pop();
                               }

                             }

                             if(jujuba && pilha.empty()){
                                printf("correct\n");
                             }
                             else{
                                printf("incorrect\n");
                             }

                           }


        							return 0;
       									 }
