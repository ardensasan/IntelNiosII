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
int time[] = {0, 0, 0, 0, 0};
int counter = 250000; // 1/(50 MHz) x (2500000) = 50 msec

*counterLow = (counter & 0xFFFF);
*counterHigh = (counter >> 16) & 0xFFFF;
*control = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

display(time);

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
        timer(time,0);
        *status = 0;
    }
}
}

void timer(int time[],int index){
    if(index == 1){
        if(time[index] > 8){
            time[index] = 0;
            timer(time,index+1);
        }else{
            time[index] += 1;
        }
    }
    else if(time[index] > 8 && (index % 2 == 0)){
        time[index] = 0;
        timer(time,index+1);
    }else if(time[index] > 4 && (index % 2 != 0)){
        time[index] = 0;
        timer(time,index+1);
    }
    else{
        time[index] += 1;
    }
    display(time);
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
    int BIT_CODES[] ={ 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
    bits = BIT_CODES[value];
    return bits;
}
