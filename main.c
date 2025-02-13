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

double rng(void)
{
    return (double)rand()/(RAND_MAX+1.0);
}

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
    double ball_x = screenWidth / 2;
    double ball_y = screenHeight / 2;
    double ball_speed = 2.5;
    double ball_xv = ball_speed;
    double ball_yv = ball_speed;

    Rectangle paddle1;
    paddle1.x = 32;
    paddle1.y = 0;
    paddle1.width = 10;
    paddle1.height = 125;
    int paddle_speed = 5;

    Rectangle paddle2;
    paddle2.x = screenWidth - 32 - 10;
    paddle2.y = 0;
    paddle2.width = 10;
    paddle2.height = 125;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per
    int frameCount = 0;
    int score = 0;
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
            sprintf(&my_string[0], "%d", score);

            frameCount++;

            ball_x += ball_xv;
            ball_y += ball_yv;

            if (paddle2.y < ball_y - paddle2.height / 2) {
                paddle2.y += paddle_speed;
            }

            if (paddle2.y > ball_y - paddle2.height / 2) {
                paddle2.y -= paddle_speed;
            }

            if (ball_x < ball_radius){
                //
            }
            if (ball_x < ball_radius+paddle1.x+paddle1.width && ball_x > ball_radius+paddle1.x && abs((ball_y + ball_radius/2) - (paddle1.y + paddle1.height / 2)) < paddle1.height / 2 + ball_radius/2){
                ball_speed += 0.125;
                ball_xv = ball_speed;
                if (score % 2 == 0){
                    paddle1.height -= 1;
                    paddle1.y += (int)(rng()+0.5);
                }
                score += 1;
                ball_x = ball_radius+paddle1.x+paddle1.width + ball_xv;
            }
            if (ball_x + ball_radius > paddle2.x && ball_x + ball_radius < paddle2.x + paddle2.width && abs((ball_y + ball_radius/2) - (paddle2.y + paddle2.height / 2)) < paddle2.height / 2 + ball_radius/2){
                ball_speed += 0.125;
                ball_xv = -ball_speed;
                if (score % 2 == 0){
                    paddle2.height -= 1;
                    paddle2.y += (int)(rng()+0.5);
                }
                ball_x = paddle2.x - ball_radius - ball_xv;
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

            DrawRectangleRec(paddle1, (Color) { 65, 175, 249, 255 });
            DrawRectangleRec(paddle2, (Color) { 253, 0, 0, 255 });

            DrawText(my_string, 2, 0, 21, RAYWHITE);
            DrawCircle(ball_x,ball_y,ball_radius,GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
