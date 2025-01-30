#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    int ball_radius = 20;
    int ball_x = 0;
    int ball_y = 0;
    int ball_speed = 3;
    int ball_xv = ball_speed;
    int ball_yv = ball_speed;

    Rectangle paddle1;
    paddle1.x = 33;
    paddle1.y = 0;
    paddle1.width = 10;
    paddle1.height = 100;
    int paddle_speed = 5;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per
    int frameCount = 0;
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            char my_string[256];
            sprintf(&my_string[0], "%d", frameCount);

            frameCount++;

            ball_x += ball_xv;
            ball_y += ball_yv;

            if (ball_x < ball_radius){
                ball_xv = ball_speed;
            }
            if (ball_x < ball_radius+paddle1.x+paddle1.width && ball_x > ball_radius+paddle1.x && abs((ball_y + ball_radius/2) - (paddle1.y + paddle1.height / 2)) < paddle1.height / 2 + ball_radius/2){
                ball_xv = ball_speed;
                paddle1.height -= 5;
            }
            if (ball_x + ball_radius > screenWidth){
                ball_xv = -ball_speed;
            }
            if (ball_y < ball_radius){
                ball_yv = ball_speed;
            }
            if (ball_y + ball_radius > screenHeight){
                ball_yv = -ball_speed;
            }

            if(IsKeyDown(KEY_UP)){
                paddle1.y -= paddle_speed;
            }
            if(IsKeyDown(KEY_DOWN)){
                paddle1.y += paddle_speed;
            }

            DrawRectangleRec(paddle1, RED);

            DrawText(my_string, 2, 0, 21, RAYWHITE);
            DrawCircle(ball_x,ball_y,ball_radius,BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
