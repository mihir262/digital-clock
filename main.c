#include <stdio.h>
#include <time.h>
#include "raylib.h"

#define WIDTH 900
#define HEIGHT 600

float segment_width = 200;
float segment_height = 50;

void DrawSegment(Vector2 center){
        // making the 7 segment display
        int count = 6;

        Vector2 a,b,c,d,e,f;
        a = (Vector2){center.x - segment_width/2 - segment_height/2, center.y};
        b = (Vector2){center.x - segment_width/2, center.y - segment_height/2};
        c = (Vector2){center.x - segment_width/2, center.y + segment_height/2};
        d = (Vector2){center.x + segment_width/2, center.y - segment_height/2};
        e = (Vector2){center.x + segment_width/2, center.y + segment_height/2};
        f = (Vector2){center.x + segment_width/2 + segment_height/2, center.y};

        Vector2 points[] = {a,c,b,e,d,f};
        DrawTriangleStrip(points, count, SKYBLUE);
}

int main(){

    time_t current_time = time(NULL);
    char *time_string = ctime(&current_time);

    printf("the current time is %s\n", time_string);
    InitWindow(WIDTH, HEIGHT, "Digital Clock");

    while (!WindowShouldClose()){
        BeginDrawing();
        Vector2 center = {WIDTH/2, HEIGHT/2};
        DrawSegment((Vector2){300, 200});
        EndDrawing();
    }

    return 0;
}

