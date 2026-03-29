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

int main(){

    time_t current_time = time(NULL);
    char *time_string = ctime(&current_time);

    printf("the current time is %s\n", time_string);
    InitWindow(WIDTH, HEIGHT, "Digital Clock");

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 center = (Vector2){300,200};
        DrawSegment(center,true);

        Vector2 other_center = (Vector2){400,400};
        DrawSegment(other_center,false);
        EndDrawing();
    }

    return 0;
}

