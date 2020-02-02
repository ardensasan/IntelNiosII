volatile int *status =(int *)0xFF202000; 
volatile int *control = (int *)0xFF202004;
volatile int *counterLow = (int *)0xFF202008;
volatile int *counterHigh = (int *)0xFF20200C;
volatile int *HEXA = (int *)0xFF200020;
volatile int *HEXB = (int *)0xFF200030;
volatile int *KEYS = (int *)0xFF200050;
int main(void) {
int pushed = 0;
int pause = 0;
int wordDisplay[] = {5, 4, 3, 2, 1, 0, 5, 5, 5};
int counter = 25000000; // 1/(50 MHz) x (2500000) = 50 msec
int n = 0;
int movePlaces = 0;
*counterLow = (counter & 0xFFFF);
*counterHigh = (counter >> 16) & 0xFFFF;
*control = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

display(wordDisplay);
while (1)
{
    if(*KEYS == 0x1 && pause == 0 && pushed == 0){
        pause = 1;
        pushed = 1;
        *control = 0x0;
    }else if(*KEYS == 0x1 && pause == 1 && pushed == 0){
        pause = 0;
        pushed = 1;
        *control = 0x7;
    }else if(*KEYS == 0x0 && pushed == 1){
        pushed = 0;
    }
    if(*status == 3){
        rotate(wordDisplay);
        *status = 0;
    }
}
}
//rotate array to the right
void rotate(int wordDisplay[]){
       for(int i = 0; i < 1; i++){    
        int j, last;    
        //Stores the last element of the array    
        last = wordDisplay[9-1];    
        
        for(j = 9-1; j > 0; j--){    
            //Shift element of array by one    
            wordDisplay[j] = wordDisplay[j-1];    
        }    
        //Last element of array will be added to the start of array.    
        wordDisplay[0] = last;    
    }  
    display(wordDisplay);
    return;
}

void display(int time[]){
    int HEX1 = 0;
    int HEX2 = 0;
    for(int x = 0;x<=5;x++){
        if(x < 4){
            HEX1 |= bitCode(time[x]) << (x*8);
        }else{
            HEX2 |= bitCode(time[x]) << ((x-4)*8);
        }
    }
    *HEXA = HEX1;
    *HEXB = HEX2;
    return;
}
int bitCode(int value){
    int bits = 0;
    int BIT_CODES[] ={ 0b00000100, 0b01010100, 0b01111000, 0b01111001, 0b00111000, 0b00000000};
    bits = BIT_CODES[value];
    return bits;
}
