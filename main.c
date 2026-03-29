#include <stdio.h>
#include <time.h>
#include "raylib.h"

#define WIDTH 1600
#define HEIGHT 900

#define OFFSET 28 // tuned for fitting HH:MM:SS in 900x600
#define DIGIT_DISTANCE 138
#define GROUP_GAP 36
#define DIGIT_COUNT 6
#define ON_COLOUR RED
#define OFF_COLOUR BLACK

float segment_width = 80;
float segment_height = 20;

int digits[10][7] = {
    {1,1,1,0,1,1,1}, //zero
    {0,0,1,0,0,1,0}, //one
    {1,0,1,1,1,0,1}, //two
    {1,0,1,1,0,1,1}, //three
    {0,1,1,1,0,1,0}, //four
    {1,1,0,1,0,1,1}, //five
    {1,1,0,1,1,1,1}, //six
    {1,0,1,0,0,1,0}, //seven
    {1,1,1,1,1,1,1}, //eight
    {1,1,1,1,0,1,1}  //nine
};


void DrawSegment(Vector2 center, bool horizontal, Color color){
    int count = 6;
    Vector2 a,b,c,d,e,f;

    if(horizontal){
        a = (Vector2){center.x - segment_width/2 - segment_height/2, center.y};
        c = (Vector2){center.x - segment_width/2, center.y - segment_height/2};
        b = (Vector2){center.x - segment_width/2, center.y + segment_height/2};
        e = (Vector2){center.x + segment_width/2, center.y - segment_height/2};
        d = (Vector2){center.x + segment_width/2, center.y + segment_height/2};
        f = (Vector2){center.x + segment_width/2 + segment_height/2, center.y};
    }
    else{
        a = (Vector2){center.x, center.y - segment_width/2 - segment_height/2};
        b = (Vector2){center.x - segment_height/2, center.y - segment_width/2};
        c = (Vector2){center.x + segment_height/2, center.y - segment_width/2};
        d = (Vector2){center.x - segment_height/2, center.y + segment_width/2};
        e = (Vector2){center.x + segment_height/2, center.y + segment_width/2};
        f = (Vector2){center.x, center.y + segment_width/2 + segment_height/2};
    }

    Vector2 points[] = {a,b,c,d,e,f};
    DrawTriangleStrip(points, count, color);
}

Color GetSegmentColor(bool on){
    return on ? ON_COLOUR : OFF_COLOUR;
}

void GetTimeDigits(time_t current_time, int time_digits[DIGIT_COUNT]){
    struct tm *local = localtime(&current_time);
    int hour = local->tm_hour;
    int minute = local->tm_min;
    int second = local->tm_sec;

    time_digits[0] = hour / 10;
    time_digits[1] = hour % 10;
    time_digits[2] = minute / 10;
    time_digits[3] = minute % 10;
    time_digits[4] = second / 10;
    time_digits[5] = second % 10;
}

void DrawColon(float x, float y){
    const float dot_radius = segment_height * 0.45f;
    const float dot_offset = segment_width * 0.45f;

    DrawCircleV((Vector2){x, y - dot_offset}, dot_radius, ON_COLOUR);
    DrawCircleV((Vector2){x, y + dot_offset}, dot_radius, ON_COLOUR);
}

void DrawDigit(Vector2 center, int digit){
    // which number to draw
    int *digit_segments = digits[digit];

    // draw first
    Vector2 first = {center.x, center.y - segment_width - OFFSET};
    DrawSegment(first, true, digit_segments[0] ? ON_COLOUR : OFF_COLOUR);

    Vector2 second = {center.x - segment_width/2 - OFFSET/2, center.y - segment_width/2 - OFFSET/2};
    DrawSegment(second, false, digit_segments[1] ? ON_COLOUR : OFF_COLOUR);

    Vector2 third = {center.x + segment_width/2 + OFFSET/2, center.y - segment_width/2 - OFFSET/2};
    DrawSegment(third, false, digit_segments[2] ? ON_COLOUR : OFF_COLOUR);

    Vector2 fourth = {center.x,center.y}; //middle one
    DrawSegment(fourth,true, digit_segments[3] ? ON_COLOUR : OFF_COLOUR);

    Vector2 fifth = {center.x - segment_width/2 - OFFSET/2,center.y + segment_width/2 + OFFSET/2};
    DrawSegment(fifth, false, digit_segments[4] ? ON_COLOUR : OFF_COLOUR);

    Vector2 sixth = {center.x + segment_width/2 + OFFSET/2,center.y + segment_width/2 + OFFSET/2};
    DrawSegment(sixth, false, digit_segments[5] ? ON_COLOUR : OFF_COLOUR);

    Vector2 seventh = {center.x, center.y + segment_width + OFFSET};
    DrawSegment(seventh, true, digit_segments[6] ? ON_COLOUR : OFF_COLOUR);
}

void DrawTime(time_t current_time){
    int time_digits[DIGIT_COUNT];
    float digit_positions[DIGIT_COUNT];
    float center_span = 0.0f;
    float start_x;
    float center_y = HEIGHT / 2.0f;

    GetTimeDigits(current_time, time_digits);

    digit_positions[0] = 0.0f;
    for (int i = 1; i < DIGIT_COUNT; i++){
        float step = DIGIT_DISTANCE;
        if (i == 2 || i == 4){
            step += GROUP_GAP;
        }

        digit_positions[i] = digit_positions[i - 1] + step;
    }

    center_span = digit_positions[DIGIT_COUNT - 1];
    start_x = (WIDTH - center_span) / 2.0f;

    for (int i = 0; i < DIGIT_COUNT; i++){
        float digit_x = start_x + digit_positions[i];
        DrawDigit((Vector2){digit_x, center_y}, time_digits[i]);

        if (i == 1 || i == 3){
            float next_digit_x = start_x + digit_positions[i + 1];
            DrawColon((digit_x + next_digit_x) / 2.0f, center_y);
        }
    }

}

int main(){
    InitWindow(WIDTH, HEIGHT, "Digital Clock");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        time_t current_time = time(NULL);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTime(current_time);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

