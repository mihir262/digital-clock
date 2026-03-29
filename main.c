#include <stdio.h>
#include <time.h>
#include "raylib.h"

#define WIDTH 900
#define HEIGHT 600

float segment_width = 200;
float segment_height = 50;

void DrawSegment(Vector2 center, bool horizontal){
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
    DrawTriangleStrip(points, count, SKYBLUE);
}

void DrawDigit(Vector2 center){

    // draw first
    Vector2 first = {center.x, center.y - segment_width};
    DrawSegment(first, true);

    Vector2 second = {center.x - segment_width/2, center.y - segment_width/2};
    DrawSegment(second, false);

    Vector2 third = {center.x + segment_width/2, center.y - segment_width/2};
    DrawSegment(third, false);

    Vector2 fourth = {center.x,center.y}; //middle one
    DrawSegment(fourth,true);

    Vector2 fifth = {center.x - segment_width/2,center.y + segment_width/2};
    DrawSegment(fifth, false);

    Vector2 sixth = {center.x + segment_width/2,center.y + segment_width/2};
    DrawSegment(sixth, false);

    Vector2 seventh = {center.x, center.y + segment_width};
    DrawSegment(seventh, true);
}

int main(){

    time_t current_time = time(NULL);
    char *time_string = ctime(&current_time);

    printf("the current time is %s\n", time_string);
    InitWindow(WIDTH, HEIGHT, "Digital Clock");

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        SetTargetFPS(60);

        DrawDigit((Vector2){WIDTH/2,HEIGHT/2});

        EndDrawing();
    }

    return 0;
}

