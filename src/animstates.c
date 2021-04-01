#include "animstates.h"

#define MAX_ANIM_COUNT (10)
static int anim_count = 0;
static int anim_durations[MAX_ANIM_COUNT];

static int curr_anim = 0;
static int framecounter = 0;

void animstates_init(const char* file) {
    //todo non-hardcoded
    anim_count = 5;
    anim_durations[0] = 51; //idle
    anim_durations[2] = 37; //hp
    anim_durations[1] = 15; //lp
    anim_durations[3] = 20; //lk
    anim_durations[4] = 38; //hk
    framecounter = 0;
    curr_anim = 0;
}
void animstates_update(int frames) {
    if (anim_count == 0)
        return;
    framecounter += frames;
    if (framecounter >= anim_durations[curr_anim]) {
        //return to idle
        framecounter -= anim_durations[curr_anim]; //skip through the rest of the animation
        curr_anim = 0;
        framecounter %= anim_durations[0]; //round down to duration of idle
    }
}
void queue_anim(int index) {
    if (index >= anim_count)
        return;
    curr_anim = index;
    framecounter = 0;
}
int get_anim_frame() {
    return framecounter;
}
int get_anim_index() {
    return curr_anim + 1; //ignore t pose
}