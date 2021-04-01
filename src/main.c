#include "raylib.h"
#include "commandinterpret.h"
#include <string.h>
#include <math.h>
#include "../FileConverter/decode.c"
#include "raymath.h"
#include "animstates.h"
#include "utils.h"
#ifdef _WIN32
//GetModuleFileNameA for absolute filepaths
#include <libloaderapi.h>
#endif
#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

// Change this depending on the path of your executable relative to the assets folder
#define ASSET_PATH "./assets/"
#define HARDCODED_BINDS
#define CUSTOM_MAPPINGS
#if defined(PLATFORM_RPI)
#define XBOX360_NAME_ID "Microsoft X-Box 360 pad"
#define PS3_NAME_ID "PLAYSTATION(R)3 Controller"
#else
#define XBOX360_NAME_ID "Xbox 360 Controller"
#define PS3_NAME_ID "PLAYSTATION(R)3 Controller"
#endif

int glfwUpdateGamepadMappings(const char* string);

const int lookahead = 60;

extern SBMap active_map;

//sequence of images depicting command
typedef struct {
    Texture2D* textures;
    float* rotations;
    int length;
} MoveImgSequence;

enum TimingFeedback {
    miss_timing,
    good_timing,
    great_timing
};

int instruction_text_size = 40;

//list of commands, in order of priority
#define NUM_MOVES (8)
Move movelist[NUM_MOVES] = //{{"5B", 12, 26, mid, none}, {"5A", 4, 7, mid, none}};
{ {"236B", extra, extra, mid, none}, {"236A", lengthy, extra, mid, none}, {"2B", medium, medium, mid, none}, {"2A", brief, medium, mid, none},{"5E",15,23,mid,none}, {"5D", 7, 13, mid, none}, {"5B", 12, 26, mid, none}, {"5A", 4, 7, mid, none} };
int move_anims[NUM_MOVES] = { 99,99,99,99,4,3,2,1 };
MoveImgSequence move_img_list[NUM_MOVES];
KeyboardKey button_keys[6];
int buttons_gamepad[6];

extern SBMap active_map;

//tracks whether current song should end
bool game_should_end = false;


bool borderless = 0;
void ToggleBorderless() {
    if (!borderless) {
        SetWindowSize(1920, 1080);
        ToggleFullscreen();
    }
    else {
        ToggleFullscreen();
        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    borderless = !borderless;
}




int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "String Beat");
    InitAudioDevice();



    //go to executable directory
#ifdef _WIN32
    {
        LPSTR abspath = malloc(MAX_PATH * sizeof(char));
        GetModuleFileNameA(NULL, abspath, MAX_PATH);
        int i;
        for (i = strlen(abspath) - 1; i >= 0 && abspath[i] != '\\'; i--)
            abspath[i] = '\0';

        //truncate build for dev purposes - remove on release versions?
        const char bdir[] = "build\\";
        int j;
        for (j = 5; j >= 0 && bdir[j] == abspath[i]; j--) {
            i--;
        }
        if (j < 0)
            abspath[i + 1] = '\0';
        ChangeDirectory(abspath);
        free(abspath);
    }
#endif

    Image window_icon = LoadImage(ASSET_PATH "pbaglogo.png");
    SetWindowIcon(window_icon);


#ifdef CUSTOM_MAPPINGS
    //SDL2 mappings
    const char* mappings = LoadText(ASSET_PATH "gamepad_mapping.txt");
    glfwUpdateGamepadMappings(mappings);
#endif

#ifdef HARDCODED_BINDS
    button_keys[0] = KEY_A;
    button_keys[1] = KEY_S;
    button_keys[2] = KEY_D;
    button_keys[3] = KEY_Z;
    button_keys[4] = KEY_X;
    button_keys[5] = KEY_C;
    buttons_gamepad[0] = 8;
    buttons_gamepad[1] = 5;
    buttons_gamepad[2] = 11;
    buttons_gamepad[3] = 7;
    buttons_gamepad[4] = 6;
    buttons_gamepad[5] = 9;
#endif

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    //--- 3D Setup -----
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 0.0f, 0.0f };
    camera.target = (Vector3){ 0, 0, 0 };
    camera.up = (Vector3){ 0, 1, 0 };
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;

    Model longboi = LoadModel(ASSET_PATH "longboi(texture).iqm");
    Texture2D lboi_texture = LoadTexture(ASSET_PATH "longboi_texture.png");
    longboi.materials[0].maps[MAP_DIFFUSE].texture = lboi_texture;
    Shader lshader = LoadShader("shaders/getnormal.vs", "shaders/veclighting.fs");
    int lightloc = GetShaderLocation(lshader, "lightVec");
    float lightray[3] = { 3.0f, -1.0f, 1.0f };
    SetShaderValue(lshader, lightloc, lightray, UNIFORM_VEC3);
    longboi.materials[0].shader = lshader;

    //animations
    int longboi_animcount;
    ModelAnimation* longboi_anims = LoadModelAnimations(ASSET_PATH "longboi(texture).iqm", &longboi_animcount);
    animstates_init("");
    int last_frame = 0;

    //fix orientation
    longboi.transform = MatrixMultiply(MatrixRotateY(DEG2RAD * 180), longboi.transform);
    longboi.transform = MatrixMultiply(MatrixRotateX(DEG2RAD * 90.0f), longboi.transform);
    longboi.transform = MatrixMultiply(MatrixRotateZ(DEG2RAD * 90.0f), longboi.transform);

#define TEXTURE_SCALE (.25f)
    //texture loading
    Texture2D arrow_texture = LoadTexture(ASSET_PATH "CommandArrow.png");
    Texture2D button_textures[6];
    button_textures[0] = LoadTexture(ASSET_PATH "CommandLetterA.png");
    button_textures[1] = LoadTexture(ASSET_PATH "CommandLetterB.png");
    button_textures[2] = LoadTexture(ASSET_PATH "CommandLetterC.png");
    button_textures[3] = LoadTexture(ASSET_PATH "CommandLetterD.png");
    button_textures[4] = LoadTexture(ASSET_PATH "CommandLetterE.png");
    button_textures[5] = LoadTexture(ASSET_PATH "CommandLetterF.png");

    //generate visual representations for moves
    for (int i = 0; i < NUM_MOVES; i++) {
        move_img_list[i].length = strlen(movelist[i].command);
        if (move_img_list[i].length == 2 && movelist[i].command[0] == '5') {
            move_img_list[i].length = 1;
        }
        //allocate memory for texture data
        move_img_list[i].textures = malloc(move_img_list[i].length * sizeof(Texture2D));
        move_img_list[i].rotations = malloc(move_img_list[i].length * sizeof(float));
        //last icon is button
        move_img_list[i].rotations[move_img_list[i].length - 1] = 0;
        move_img_list[i].textures[move_img_list[i].length - 1] = button_textures[movelist[i].command[strlen(movelist[i].command) - 1] - 'A'];
        for (int j = 0; j < move_img_list[i].length - 1; j++) {
            move_img_list[i].textures[j] = arrow_texture;
            if (movelist[i].command[j] == '6')
                move_img_list[i].rotations[j] = 0.0f;
            else if (movelist[i].command[j] > '6')
                move_img_list[i].rotations[j] = -45.0f * (10 - movelist[i].command[j] - '0');
            else if (movelist[i].command[j] == '4')
                move_img_list[i].rotations[j] = 180.0f;
            else
                move_img_list[i].rotations[j] = 45.0f * (4 - movelist[i].command[j] - '0');
        }
    }

    //inputs
    InputBuffer buffer = { .ringStart = 0, .ringLength = 0 };
    Input input = { .buttons = {0, 0, 0, 0, 0, 0} };

    //misc
    enum TimingFeedback hit_feedback;
    int active_gamepad;
    int circle_countdown;
    int fadeout_timer = 20;
    const char* button_string = NULL;
    int current_command = 0;
    unsigned int score = 0, combo = 0;

    //song timing
    int song_frame = 0;
    float frame_leftovers = 0.0f; //stores ms of frametime that did not form a full frame

    //text measuring
    Vector2 text_size_button = MeasureTextEx(GetFontDefault(), "5C", 20, 1);
    const Vector2 text_size_kb = MeasureTextEx(GetFontDefault(), "Keyboard", 20, 1);
    int textsize_start = MeasureText("CLICK TO START", 40);

    int main_menu = 1;

    //load song selection
    int file_count, song_count = 0;
    char** song_folder = GetDirectoryFiles("./songs/", &file_count);
    char** song_choices = NULL;
    if (file_count > 2) {
        song_choices = malloc(sizeof(char*) * (file_count - 2));

        for (int i = 2;i < file_count;i++) {
            //todo: check for files before adding
            song_choices[song_count] = song_folder[i];
            song_count++;
        }
    }

    FILE* input_file;
    Music music = { .ctxType = -1 };
    active_map.length = -1;


    int click_cd = 0;//delay to avoid duplicate mouse button presses
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        if (game_should_end && fadeout_timer == 0)
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                click_cd = 5;
                main_menu = 1;
            }


        // Main Menu
        //---------------------------------------------------------------------------------
        if (main_menu) {
            //reset song state
            song_frame = 0;
            fadeout_timer = 20;
            frame_leftovers = 0.0f;
            score = 0;
            combo = 0;
            current_command = 0;
            last_frame = 0;
            game_should_end = 0;
            circle_countdown = 0;

            //cleanup
            if (music.ctxType != -1) {
                StopMusicStream(music);
                UnloadMusicStream(music);
            }
            if (active_map.length != -1) {
                free(active_map.command_indices);
                free(active_map.timings);
            }

            const int menu_offset = 300;
            //start menu + song select
            int selected_song = -2;
            while (selected_song == -2 && !WindowShouldClose()) {
                if (IsKeyPressed(KEY_F11))
                    ToggleBorderless();
                for (int i = -1;i < song_count;i++) {
                    if (GetMouseX() >= GetScreenWidth() / 2 - textsize_start / 2 && GetMouseX() <= GetScreenWidth() / 2 + textsize_start / 2 &&
                        GetMouseY() >= menu_offset + i * 50 && GetMouseY() < menu_offset + 50 + i * 50 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && click_cd == 0)
                        selected_song = i;
                }
                if (click_cd > 0)
                    click_cd--;
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("SONG SELECT:", GetScreenWidth() / 2 - textsize_start / 2, 40, 60, BLACK);
                for (int i = -1;i < song_count;i++) {
                    if (GetMouseX() >= GetScreenWidth() / 2 - textsize_start / 2 && GetMouseX() <= GetScreenWidth() / 2 + textsize_start / 2 &&
                        GetMouseY() >= menu_offset + i * 50 && GetMouseY() < menu_offset + 50 + i * 50)
                        DrawRectangle(GetScreenWidth() / 2 - textsize_start / 2, menu_offset + i * 50, textsize_start, 50, LIGHTGRAY);
                    if (i == -1)
                        DrawText("DEFAULT SONG", GetScreenWidth() / 2 - textsize_start / 2, menu_offset + 5 + i * 50, 40, BLACK);
                    else
                        DrawText(song_choices[i], GetScreenWidth() / 2 - textsize_start / 2, menu_offset + 5 + i * 50, 40, BLACK);
                }
                EndDrawing();
            }

            if (WindowShouldClose())
                continue;

            //beatmap loading
            if (selected_song == -1) {
                input_file = fopen(ASSET_PATH "beatmap.sb", "rb");
                music = LoadMusicStream(ASSET_PATH "audio.mp3");
            }
            else {

                char* folderpath = strcat_safe("./songs/", song_choices[selected_song]);
                char* filepath = strcat_safe(folderpath, "/beatmap.sb");
                char* musicpath = strcat_safe(folderpath, "/audio.mp3");
                input_file = fopen(filepath, "rb");
                music = LoadMusicStream(musicpath);
                free(filepath);
                free(musicpath);
                free(folderpath);
            }
            decode(input_file, movelist, NUM_MOVES);
            fclose(input_file);


            //music setup
            music.loopCount = 1;
            SetMusicVolume(music, .15f); //anti-earrape
            Color gray = LIGHTGRAY;
            for (int i = 60; i > 0 && !WindowShouldClose(); i--) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("SONG SELECT:", GetScreenWidth() / 2 - textsize_start / 2, 40, 60, (Color) { 0, 0, 0, 255 * (i / 60.0f) });
                for (int j = -1;j < song_count;j++) {
                    gray.a = 255.0f * (i / 60);
                    if (selected_song == j)
                        DrawRectangle(GetScreenWidth() / 2 - textsize_start / 2, menu_offset + j * 50, textsize_start, 50, gray);
                    if (j == -1)
                        DrawText("DEFAULT SONG", GetScreenWidth() / 2 - textsize_start / 2, menu_offset + 5 + j * 50, 40, (Color) { 0, 0, 0, 255 * (i / 60.0f) });
                    else
                        DrawText(song_choices[j], GetScreenWidth() / 2 - textsize_start / 2, menu_offset + 5 + j * 50, 40, (Color) { 0, 0, 0, 255 * (i / 60.0f) });
                }

                EndDrawing();
            }
            if (WindowShouldClose())
                continue;

            main_menu = 0;
            PlayMusicStream(music); //starts up music
        }





        // Update
        //----------------------------------------------------------------------------------
        if (GetMusicTimeLength(music) - .1 <= GetMusicTimePlayed(music) && game_should_end)
            StopMusicStream(music);
        UpdateMusicStream(music);

        song_frame += (GetFrameTime() * 1000 + frame_leftovers) / (1000.0f / 60);
        frame_leftovers = (GetFrameTime() * 1000 + frame_leftovers) - (song_frame - last_frame) * (1000.0f / 60);

        UpdateModelAnimation(longboi, longboi_anims[get_anim_index()], get_anim_frame());
        animstates_update(song_frame - last_frame);
        last_frame = song_frame;

        //check if gamepad is connected
        if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
            //capture input on current frame
            if (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) > 0.01f) {
                input.right = 1;
                input.left = 0;
            }
            else if (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) < -0.01f) {
                input.left = 1;
                input.right = 0;
            }
            else {
                input.left = 0;
                input.right = 0;
            }

            if (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) < -0.01f) {
                input.up = 1;
                input.down = 0;
            }
            else if (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) > 0.01f) {
                input.down = 1;
                input.up = 0;
            }
            else {
                input.up = 0;
                input.down = 0;
            }
            for (int i = 0; i < 6; i++)
                input.buttons[i] = IsGamepadButtonPressed(GAMEPAD_PLAYER1, buttons_gamepad[i]) || IsGamepadButtonDown(GAMEPAD_PLAYER1, buttons_gamepad[i]);
        }
        else {
            //keyboard input
            input.up = IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP);
            input.down = IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN);
            input.left = IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT);
            input.right = IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT);
            for (int i = 0; i < 6; i++)
                input.buttons[i] = IsKeyPressed(button_keys[i]) || IsKeyDown(button_keys[i]);
        }

        //push input buffer with new input
        if (buffer.ringLength < MAX_BUFFER_SIZE) {
            buffer.ringLength++;
        }
        else {
            buffer.ringStart++;
            if (buffer.ringStart == buffer.ringLength)
                buffer.ringStart = 0;
        }
        buffer.commands[RING_INDEX(buffer.ringLength - 1, buffer.ringStart, buffer.ringLength)] = input;

        if (IsKeyPressed(KEY_F11))
            ToggleBorderless();
        /*for(int i=0;i<6;i++){
            if(buffer.commands[RING_INDEX(buffer.ringLength-1,buffer.ringStart,buffer.ringLength)].buttons[i]==1){
                button_letter[0]=i+'A';
            }
        }*/
        if (song_frame > active_map.timings[current_command] - lookahead) {
            if (song_frame < active_map.timings[current_command] + 3) {
                //checks whether command is correct
                if (isCommand(buffer, movelist[active_map.command_indices[current_command]].command)) {
                    if (abs(song_frame - active_map.timings[current_command]) <= 3) {
                        queue_anim(move_anims[active_map.command_indices[current_command]]);
                        //button_string="YES";
                        circle_countdown = 10;
                        if (abs(song_frame - active_map.timings[current_command]) <= 1) {
                            score += 300;
                            combo++;
                            hit_feedback = great_timing;
                        }
                        else {
                            score += 100;
                            combo++;
                            hit_feedback = good_timing;
                        }
                        if (current_command < active_map.length - 1)
                            current_command++;
                        else
                            game_should_end = true;
                    }
                }
                else {
                    if (circle_countdown > 0)
                        circle_countdown--;
                    //else
                    //button_string="NO";
                }
            }
            else {
                //missed input
                circle_countdown = 10;
                hit_feedback = miss_timing;
                if (current_command < active_map.length - 1) {
                    current_command++;
                    combo = 0;
                }
                else
                    game_should_end = true;
            }
        }
        else if (circle_countdown > 0)
            circle_countdown--;
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //3d
        BeginMode3D(camera);
        DrawModel(longboi, (Vector3) { 0, -1.5, 0 }, 3.0f, WHITE);
        EndMode3D();

#ifdef DISPLAY_GAMEPAD_DEBUG
        if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
            char* text_pad = FormatText("Gamepad: %s", GetGamepadName(GAMEPAD_PLAYER1));
            //Vector2 text_size_axes=MeasureTextEx(GetFontDefault(),text_axes,20,1);
            Vector2 text_size_pad = MeasureTextEx(GetFontDefault(), text_pad, 20, 1);
            DrawText(text_pad, SCREEN_WIDTH / 2 - text_size_pad.x / 2, 120, 20, BLACK);
        }
        else {
            DrawText("Keyboard", SCREEN_WIDTH / 2 - text_size_kb.x, 120, 20, BLACK);
            //DrawText(TextFormat("C:%i S:%i L:%i",buffer.ringLength-1,buffer.ringStart,buffer.ringLength),220,220,20,BLACK);
        }
#endif
        //draw scoreboard elements
        DrawText(TextFormat("Score: %i", score), 0, 0, 20, BLACK);
        DrawText(TextFormat("Combo: %i", combo), 0, GetScreenHeight() - 20, 20, BLACK);
        //DrawText(TextFormat("Frame: %i, Leftovers: %f", song_frame, frame_leftovers), 0, 30, 20, BLACK);
        Vector2 hit_center = { GetScreenWidth() / 2 - text_size_button.x / 2, GetScreenHeight() / 2 - text_size_button.y / 2 + instruction_text_size / 2 };
        //draw next command in the queue
        Rectangle base_texture_rect = { 0, 0, arrow_texture.width, arrow_texture.height };
        Rectangle dest_texture_rect = { (GetScreenWidth() / 2 - text_size_button.x),
                                       GetScreenHeight() * 3 / 4, base_texture_rect.width * TEXTURE_SCALE, base_texture_rect.height * TEXTURE_SCALE };
        Vector2 base_texture_origin = { base_texture_rect.x + 20, base_texture_rect.y + 20 };
        Color cmd_color = GRAY;
        if (game_should_end && fadeout_timer > 0) {
            //fadeout if song has ended
            cmd_color.a = 255 * fadeout_timer / 20.0f;
            fadeout_timer--;
        }

        for (int j = 0; j < move_img_list[active_map.command_indices[current_command]].length && (!game_should_end || fadeout_timer > 0); j++) {
            DrawTexturePro(move_img_list[active_map.command_indices[current_command]].textures[j], base_texture_rect,
                dest_texture_rect, base_texture_origin, move_img_list[active_map.command_indices[current_command]].rotations[j], cmd_color);
            dest_texture_rect.x += move_img_list[active_map.command_indices[current_command]].textures[j].width * TEXTURE_SCALE;
        }

        //draw hit feedback
        if (circle_countdown > 0 && (!game_should_end || fadeout_timer > 0)) {
            switch (hit_feedback) {
            case great_timing:
                DrawRing(hit_center, 20 + instruction_text_size, instruction_text_size + 23, 0, 360, 32, GREEN);
                break;
            case good_timing:
                DrawRing(hit_center, instruction_text_size + 20, instruction_text_size + 23, 0, 360, 32, YELLOW);
                break;
            case miss_timing:
                DrawRing(hit_center, instruction_text_size + 20, instruction_text_size + 23, 0, 360, 32, RED);
                break;
            }
        }
        //draw incoming commands
        for (int i = current_command; song_frame > active_map.timings[i] - lookahead && i < active_map.length && !game_should_end; i++) {
            dest_texture_rect.x = (GetScreenWidth() / 2 - text_size_button.x);
            dest_texture_rect.y = (GetScreenHeight() * 3 / 4) * ((lookahead - active_map.timings[i] * 1.0f + song_frame) / lookahead);
            for (int j = 0; j < move_img_list[active_map.command_indices[i]].length; j++) {

                DrawTexturePro(move_img_list[active_map.command_indices[i]].textures[j], base_texture_rect,
                    dest_texture_rect, base_texture_origin, move_img_list[active_map.command_indices[i]].rotations[j], WHITE);
                dest_texture_rect.x += move_img_list[active_map.command_indices[i]].textures[j].width * TEXTURE_SCALE;
            }
        }
        if (game_should_end && fadeout_timer <= 0)
            DrawText("CLICK TO RETURN TO MENU", GetScreenWidth() / 2 - MeasureText("CLICK TO RETURN TO MENU", 40) / 2, GetScreenHeight() / 2 - 20, 40, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music);

    for (int i = 0; i < longboi_animcount; i++) {
        UnloadModelAnimation(longboi_anims[i]);
    }
    free(longboi_anims);
    UnloadModel(longboi);
    UnloadTexture(arrow_texture);
    for (int i = 0; i < 6; i++) {
        UnloadTexture(button_textures[i]);
    }
    for (int i = 0; i < NUM_MOVES; i++) {
        free(move_img_list[i].rotations);
        free(move_img_list[i].textures);
    }
    free(active_map.command_indices);
    free(active_map.timings);
    ClearDirectoryFiles();
    if (song_choices != NULL) {
        free(song_choices);
    }
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}