#include<stdbool.h>
#include<string.h>
#include<stdio.h>
#include"commandinterpret.h"
/*numpad notation ex qcf+A: 236A
stick   buttons
7 8 9
4 5 6 + A B C
1 2 3   D E F
*/
/**checks whether a button press is correct, if any*/
static int buttonPress(bool buttonsPressed[6], char *command, int i){
    for(int j=0;j<6;j++){
        if(buttonsPressed[j]==true)
            if(command[i]>='A'&&command[i]<='F'&&command[i]==j+'A'){
                return 1;//correct button press
            }
            else if(i==strlen(command)-2){
                if(command[i+1]>='A'&&command[i+1]<='F'&&command[i+1]==j+'A'){
                    return 1;//correct button press on same frame
                }
                else{
                    return -1;
                }
            }
            else{
                return -1;//incorrect button press
            }
    }
    return 0;
}
static const int DELAY_TOLERANCE=5;//maximum num of frames before next motion of command
static const int MISS_TOLERANCE=2;//maximum num of wrong directionals
/**Checks whether the command is the last one performed in the buffer. Inputs for different commands can still
 *  overlap, ex. 236236A and 236A, so always check them in a hierarchy*/
bool isCommand(InputBuffer a, char* command){
    int commandI=strlen(command)-1,delays=0,misses=0,misstol=MISS_TOLERANCE;
    bool buttonmod=0;
    if(commandI==1){
        misstol=0;
    }
    if(command[commandI]>='A'&&command[commandI]<='F'&&buttonPress(a.commands[RING_INDEX(a.ringLength-1,a.ringStart,a.ringLength)].buttons,command,commandI)!=1){
        return 0;
    }
    else{
        commandI--;
    }
    for(int i=a.ringLength-1;i>=0&&commandI>=0;i--){
        //printf("Checking: %c...",command[commandI]);
        if(BUFFER_TO_NUMPAD(a,i)==command[commandI]-'0'){
            //printf("Correct\n");
            delays=0;
            commandI--;
        }
        //same direction as previous command - delay
        else if(commandI<strlen(command)-1&&BUFFER_TO_NUMPAD(a,i)==command[commandI+1]-'0'){
            //printf("Same\n");
            if(misstol>0){
                delays++;
            }
            else{
                misses++;
            }
        }
        //any other directionals - miss
        else if(BUFFER_TO_NUMPAD(a,i)!=5){
            //printf("Miss,%i\n",BUFFER_TO_NUMPAD(a,i));
            misses++;
        }
        //neutral stick - delay
        else{
            //printf("Neutral\n");
            delays++;
        }
        if(commandI<0){
            return 1;
        }
        if(misses>misstol||delays>DELAY_TOLERANCE){
            return 0;
        }
    }
    if(commandI<0){
        return 1;
    }
    return 0;
}
//define HASMAIN if you want to test the compile and test this file as its own executable
#ifdef HASMAIN
int main(){
    InputBuffer bufferY,bufferN;
    bufferY.ringLength=12;
    bufferY.ringStart=0;
    bufferN.ringLength=12;
    bufferN.ringStart=0;
    Input dfA={.up=0,.left=0,.right=1,.down=1,.buttons={1,0,0,0,0,0}},
    d={0,0,1,0,1,0,0,0,0,0},
    n={0,0,0,0,0,0,0,0,0,0},
    dfB={0,0,1,1,0,1,0,0,0,0},
    u={1,0,0,0,0,0,0,0},
    df={0,0,1,1,0,0,0,0,0,0},
    fA={0,0,0,1,1,0,0,0,0,0};
    for(int i=0;i<12;i++){
        bufferN.commands[i]=n;
        bufferY.commands[i]=n;
    }
    bufferY.commands[5]=d;
    bufferY.commands[8]=df;
    bufferY.commands[11]=fA;
    bufferN.commands[5]=d;
    bufferN.commands[6]=d;
    //bufferN.commands[8]=u;
    bufferN.commands[11]=dfB;
    printf("%i %i\n",isCommand(bufferY,"236A"),isCommand(bufferN,"2B"));
    return 0;
}
#endif