#ifndef ANIMSTATES__H
#define ANIMSTATES__H
//Animation States Header

//initialise module
//todo iniitialise from file
void animstates_init(const char *file);
//update state machine by a number of frames
void animstates_update(int frames);

//play attack at movelist index
void queue_anim(int index);

int get_anim_frame();
int get_anim_index();

#endif
