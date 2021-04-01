#ifndef CMDINTERPRET_H
#define CMDINTERPRET_H
#define RING_INDEX(i,rs,rl) (i+rs-rl*(i+rs>=rl))
#define BUFFER_TO_NUMPAD(buffer,i) 5+3*buffer.commands[RING_INDEX(i,buffer.ringStart,buffer.ringLength)].up-3*buffer.commands[RING_INDEX(i,buffer.ringStart,buffer.ringLength)].down+\
buffer.commands[RING_INDEX(i,buffer.ringStart,buffer.ringLength)].right-buffer.commands[RING_INDEX(i,buffer.ringStart,buffer.ringLength)].left
#define MAX_BUFFER_SIZE 60
//single frame of input, directions + buttons
typedef struct{
    bool up;
    bool left;
    bool down;
    bool right;
    bool buttons[6];
}Input;
//input ring buffer
typedef struct{
    Input commands[MAX_BUFFER_SIZE];
    int ringStart;
    int ringLength;
}InputBuffer;
/* Numpad notation primer:
   joystick buttons
    7 8 9   A B C
    4 5 6  
    1 2 3   D E F
*/
/**Checks whether the latest motions in the input buffer match the command provided
Command format is numpad notation, ex. quarter circle forward + A is written as 236A
*/
bool isCommand(InputBuffer a, char* command);
#endif