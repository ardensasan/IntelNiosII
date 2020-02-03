#include <stdio.h>
int TEST_NUM[ ] = {0x0000e000, 0x3fabedef, 0x00000001, 0x00000002, 0x75a5a5a5,
0x01ffC000, 0x03ffC000, 0x55555555, 0x77777777, 0x08888888,0x00000000};
volatile int *HEX1 = (int *)0xFF200020;
volatile int *HEX2 = (int *)0xFF200030;
int main()
{
    int index,i,ones=0,zeros=0,alternating=0,length;
    index = sizeof(TEST_NUM) / sizeof(TEST_NUM[0]);
    for(i=0;i<=index;i++){
        if(TEST_NUM[i] == 0){
            break;
        }
        length = one(TEST_NUM[i]);
        if(length > ones){
            ones = length;
            length = 0;
        }
        length = zero(TEST_NUM[i]);
        if(length > zeros){
            zeros = length;
            length = 0;
        }
        length = alternate(TEST_NUM[i]);
        if(length > alternating){
            alternating = length;
            length = 0;
        }
    }
    printf("Ones: %d\nZeros: %d\nAlternating: %d",ones,zeros,alternating);
    splitNumbers(ones,zeros,alternating);
    return 0;
}

int one(int value)
{
    int count = 0;
    while(value !=0){
        value &= (value << 1);
        count++;
    }
    return count;
}

int zero(int value)
{
    int count = 0;
    while(value !=0xffffffff){
        value |= (value << 1);
        value |= 1;
        count++;
    }
    return count;
}

int alternate(int value)
{
    int value1,value2;
    value1 = value ^ 0xAAAAAAAA;
    value2 = value ^ 0x55555555;
    value1 = one(value1);
    value2 = one(value2);
    if(value1 > value2){
        return value1;
    }else
    {
        return value2;
    }
}

int splitNumbers(int ones,int zeros,int alternating){
    int onesR = 0;
    int onesL = 0;
    int zerosR = 0; 
    int zerosL = 0;
    int alternatingR = 0;
    int alternatingL = 0;
    if(ones > 9){
        onesR = ones % 10; //ones first digit
        onesL = ones / 10; //ones second digit
    }else{
        onesR = ones % 10;
        onesL = 0;
    }
    onesR = setBit(onesR);
    onesL = (setBit(onesL)) << 8;
    if(zeros > 9){
        zerosR = zeros % 10; //zeros first digit
        zerosL = zeros / 10; //zeros second digit
    }else{
        zerosR = zeros % 10;
        zerosL = 0;
    }
    zerosR = (setBit(zerosR)) << 16;
    zerosL = (setBit(zerosL)) << 24;
    if(alternating > 9){
        alternatingR = alternating % 10; //alternating first digit
        alternatingL = alternating / 10; //alternating second digit
    }else{
        alternatingR = alternating % 10;
        alternatingL = 0;
    }
    alternatingR = setBit(alternatingR);
    alternatingL = (setBit(alternatingL)) << 8;
    *HEX1 = onesR | onesL | zerosR | zerosL;
    *HEX2 = alternatingR | alternatingL;
    return;
}

int setBit(int value){
    int BIT_CODES[] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
    return(BIT_CODES[value]);
}
