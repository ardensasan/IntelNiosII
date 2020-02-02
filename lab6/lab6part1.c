#include <stdio.h>
int LIST[8] = {7,6,3,3,4};

int main()
{
    int n,index,lNum=0;
    index = sizeof(LIST)/sizeof(LIST[0]);
    for(n=0;n<=index;n++){
        if(lNum < LIST[n]){
            lNum = LIST[n];
        }
    }
    printf("Largest Number: %d",lNum);
}
