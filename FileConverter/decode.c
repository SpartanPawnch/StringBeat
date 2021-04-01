#include <stdio.h>
#include <stdlib.h>
//internal timing object
typedef struct {
    int time;     //(ms)
    int type;     //type - 0- circle, 1-slider
    int duration; //(ms),for sliders
} OsuObj;

#define FRAME_GAP(a, b) ((b.time - a.time) / (1000.0f / 60))
//Speed categories for startup and recovery
//values are used for ideal framegaps
//ideal framegap: startup+active+recovery+ 4f recovery modifier
enum SBSpeed {
    brief = 4,
    medium = 8,
    lengthy = 12,
    extra = 16
};
//Hit heights
enum SBHitHeight {
    far,  //hits wallsplat
    high, //hits air
    mid,  //hits everywhere, but only prioritised for no launches
    low   //hits ground
};
//Launch height (if any)
enum SBLaunch {
    air,
    wallsplat,
    ground,
    none //aka reground
};

//move interface - command, frame data and properties
typedef struct {
    char* command;
    enum SBSpeed startup;
    enum SBSpeed recovery;
    enum SBHitHeight height;
    enum SBLaunch launch;
} Move;

//beatmap interface, load with decode()
typedef struct {
    int* command_indices; //Commands in numpad notation
    int* timings;         //Timings in frames
    int length;           //number of array elements
} SBMap;
SBMap active_map;

//Generates a beatmap based on the provided movelist and loads it to activeMap
void decode(FILE* input, const Move* movelist, int num_moves) {
    OsuObj current = { .type = -1 }, previous = { .type = -1 }, next = { .type = -1 };

    //active map setup
    active_map.length = 0;
    active_map.command_indices = malloc(sizeof(int) * 20);
    active_map.timings = malloc(sizeof(int) * 20);
    int allocated = 20;

    //counter to help ensure combo variety, where possible
    //if a move is used the staleness is doubled, otherwise it decays by 1 per timing point
    int staleness[num_moves];
    //maximum staleness
#define STALENESS_CAP (10)
//maximum acceptable staleness for specials
#define SPECIAL_STALENESS_CAP (4)
    for (int i = 0; i < num_moves; i++)
        staleness[i] = 1;

#ifdef DECODE_DUMP
    FILE* dump = fopen("hdump.csv", "w");
#endif

    int minimum_startup;   //fastest startup in the entirety of the movelist
    int fallback_move = 0; //index of move with fastest startup - fallback if no fitting moves are found
    int preference_coeff;  //difference between frame gap and ideal gap,lower is better
    minimum_startup = movelist[0].startup - 1;
    for (int i = 1; i < num_moves; i++) {
        if (minimum_startup > movelist[i].startup - 1) {
            minimum_startup = movelist[i].startup - 1;
            fallback_move = i;
        }
    }

    while (!feof(input)) {
        //allocate more space if needed
        if (active_map.length == allocated) {
            active_map.command_indices = realloc(active_map.command_indices, sizeof(int) * allocated * 2);
            active_map.timings = realloc(active_map.timings, sizeof(int) * allocated * 2);
            allocated *= 2;
        }

        //load timing points to analyse
        previous = current;
        if (current.type == -1) {
            fread(&current, sizeof(OsuObj), 1, input); //first input
            if (&current.time == 0) {
                fread(&current, sizeof(OsuObj), 1, input);
            }
        }
        else {
            current = next; //not first input
        }
        if (!feof(input)) {
            fread(&next, sizeof(OsuObj), 1, input);
        }
        else {
            next.type = -2;
        }
        active_map.command_indices[active_map.length] = -1;
        active_map.timings[active_map.length] = current.time / (1000.0f / 60);
        //printf("Ms timing: %i, Added timing: %i at %i\n", current.time, active_map.timings[active_map.length], active_map.length);

        //choose move based on timing point
        for (int i = 0; i < num_moves; i++) {
            //TENTATIVE - specials are only allowed in place of a slider or spinner
            if (strlen(movelist[i].command) > 2 && (current.type == 0 || staleness[i] >= SPECIAL_STALENESS_CAP))
                continue;
            //recovery needs to be short enough to link to the next move
            if (FRAME_GAP(current, next) - movelist[i].startup - movelist[i].recovery >= 0 || next.type == -2) {
                if (active_map.command_indices[active_map.length] == -1) {
                    active_map.command_indices[active_map.length] = i;
                    preference_coeff = FRAME_GAP(current, next) - movelist[i].startup - movelist[i].recovery;
                }
                else if (FRAME_GAP(previous, current) - movelist[i].startup - movelist[i].recovery + staleness[i] / 2 < preference_coeff) {
                    //based on previous move
                    active_map.command_indices[active_map.length] = i;
                    preference_coeff = FRAME_GAP(current, next) - movelist[i].startup - movelist[i].recovery;
                }
            }
        }
        //adds fastest move in case there are no others that fit
        if (active_map.command_indices[active_map.length] == -1)
            active_map.command_indices[active_map.length] = fallback_move;
        //adjust staleness
        for (int i = 0; i < num_moves; i++) {
            if (i == active_map.command_indices[active_map.length]) {
                if (staleness[i] < STALENESS_CAP)
                    staleness[i] *= 2;
                else
                    staleness[i] = STALENESS_CAP;
            }
            else if (staleness[i] > 1) {
                staleness[i]--;
            }
        }
        //move has been chosen
        active_map.length++;
#ifdef DECODE_DUMP
        fprintf(dump, "%i, %i, %i \n", current.time, current.type, current.duration);
#endif
    }
    //trim excess
    active_map.command_indices = realloc(active_map.command_indices, sizeof(int) * active_map.length);
    active_map.timings = realloc(active_map.timings, sizeof(int) * active_map.length);
#ifdef DECODE_DUMP
    fclose(dump);
#endif
}
#ifdef DECODE_STANDALONE
void main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: ./osuconverter <filename>\n");
        return;
    }
    FILE* input;
    input = fopen(argv[1], "rb");
    Move movelist[1] = { {"5A", brief, brief, mid, none} };
    decode(input, movelist, 1);
    fclose(input);
    printf("DECODE - COMPLETE, Entries: %i", active_map.length);
}
#endif