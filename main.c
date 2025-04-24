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
// #define semicolon ;
// #define is =
// #define equals ==
// #define notequal !=
// #define not !
// #define zero 0
// #define one 1
// #define two 2
// #define three 3
// #define four 4
// #define pointer *
// #define integer int
// #define constant const

double rng()
{
    return (double)(rand())/RAND_MAX;
}

double square(double x)
{
    return x * x;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int STEPS_PER_FRAME = 3;
    const int WIN_SCORE = 100;
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    int aiDifficulty = 1;
    int bonus_active = 1;
    double ball_radius = 20;
    double bonus_radius = 20;
    double ball_x = screenWidth / 2;
    double ball_y = screenHeight / 2;
    double bonus_x = screenWidth / 2;
    double bonus_y = screenHeight / 2;
    double ball_speed = 4 / STEPS_PER_FRAME;
    double ball_xv = ball_speed;
    double ball_yv = ball_speed;
    double ai_deviation = 0;

    Rectangle paddle1;
    paddle1.x = 32;
    paddle1.y = 0;
    paddle1.width = 10;
    paddle1.height = 80;
    int paddle_speed = 5;
    int outcome = 0;

    Rectangle paddle2;
    paddle2.y = 0;
    paddle2.width = 10;
    paddle2.x = screenWidth - 32 - paddle2.width;
    paddle2.height = 80;

    double ai_target_y = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per
    int frameCount = 0;
    int score = -3;
    int enemy_score = 0;

    bool game_started = false;

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

            if(IsKeyDown(KEY_ONE)){
                aiDifficulty = 1;
                game_started = true;
            }
            if(IsKeyDown(KEY_TWO)){
                aiDifficulty = 2;
                game_started = true;
            }
            if(IsKeyDown(KEY_THREE)){
                aiDifficulty = 3;
                game_started = true;
            }
            if(IsKeyDown(KEY_FOUR)){
                aiDifficulty = 4;
                game_started = true;
            }

            SetTextLineSpacing(23);

            sprintf(&my_string[0], "Press 1 for easy mode\nPress 2 for normal mode\nPress 3 for hard mode\nPress 4 for nightmare mode");

            if (game_started){
                frameCount++;
                sprintf(&my_string[0], "%d - %d", score, enemy_score);
                if (outcome == 0) {
                    for (int i = 0; i < STEPS_PER_FRAME; i++){

                        ball_x += ball_xv;
                        ball_y += ball_yv;

                        if (ball_x < ball_radius+paddle1.x+paddle1.width && ball_x > ball_radius+paddle1.x && abs((paddle1.y+paddle1.height/2) - (ball_y)) < (paddle1.height / 2 + ball_radius)){
                            ball_speed += 0.09375 / STEPS_PER_FRAME;
                            ball_xv = ball_speed;
                            ball_yv = -2.4 * ((paddle1.y+paddle1.height/2) - (ball_y))/(paddle1.height) * ball_speed;
                            score += 2;
                            ball_x = ball_radius+paddle1.x+paddle1.width + ball_xv;
                            bonus_active = 1;
                        }
                        if (ball_x + ball_radius > paddle2.x && ball_x + ball_radius < paddle2.x + paddle2.width && abs((paddle2.y+paddle2.height/2) - (ball_y)) < (paddle2.height / 2 + ball_radius)){
                            ball_speed += 0.09375 / STEPS_PER_FRAME;
                            ball_xv = -ball_speed;
                            ball_yv = -2.4 * ((paddle2.y+paddle2.height/2) - (ball_y))/(paddle2.height) * ball_speed;
                            enemy_score += 2;
                            ball_x = paddle2.x - ball_radius - ball_xv;
                            bonus_active = 1;
                        }
                        if (ball_y < ball_radius){
                            ball_yv *= -1;
                            ball_y = ball_radius + ball_speed;
                        }
                        if (ball_y + ball_radius > screenHeight){
                            ball_yv *= -1;
                            ball_y = screenHeight - ball_radius - ball_speed;
                        }
                        if (sqrt(square(ball_x - bonus_x) + square(ball_y - bonus_y)) < (ball_radius + bonus_radius) && bonus_active == 1){
                            if (ball_xv > 0){
                                score += 3;
                            } else {
                                enemy_score += 3;
                                if (aiDifficulty < 3) {
                                    ai_deviation = ((rng() * 2) - 1) * 12.5;
                                }
                                if (aiDifficulty == 1) {
                                    ai_deviation = ((rng() * 2) - 1) * 50.0;
                                }
                            }
                            bonus_x = (((rng() + 0.5) * screenWidth) / 2);
                            bonus_y = bonus_radius + rng() * (screenHeight - (bonus_radius * 2));
                            bonus_active = 0;
                        }
                        if (ball_x < ball_radius * -1){
                            ball_x = screenWidth / 2;
                            ball_y = screenHeight / 2;
                            ball_xv /= 2;
                            ball_yv = 0;
                            enemy_score += 10;
                        }
                        if (ball_x > screenWidth + ball_radius){
                            ball_x = screenWidth / 2;
                            ball_y = screenHeight / 2;
                            ball_xv /= 2;
                            ball_yv = 0;
                            score += 10;
                            ai_deviation = 0;
                        }
                        if (score >= WIN_SCORE){
                            outcome = 1;
                        } else if (enemy_score >= WIN_SCORE){
                            outcome = -1;
                        }
                    }
                } else {
                    if (outcome == -1){
                        // ClearBackground(frameCount % 2 == 0 ? BLACK : RAYWHITE);
                        sprintf(&my_string[0], "You lose! (why?)\nScore: %d", score - enemy_score + WIN_SCORE);
                    } else {
                        sprintf(&my_string[0], "You win! (yay!)\nScore: %d", score - enemy_score + WIN_SCORE);
                    }
                }

                if(IsKeyDown(KEY_UP)){
                    paddle1.y -= paddle_speed;
                }
                if(IsKeyDown(KEY_DOWN)){
                    paddle1.y += paddle_speed;
                }

                ai_target_y = ball_y;
                {
                    double ai_active_factor = 0.65;

                    if (aiDifficulty > 2 && abs(ball_xv) > 4) {
                        ai_active_factor = 0.5;
                    }

                    // if (paddle2.y < (ai_target_y - paddle2.height / 2)) {
                    //     paddle2.y += paddle_speed;
                    // }
                    // if (paddle2.y > (ai_target_y - paddle2.height / 2)) {
                    //     paddle2.y -= paddle_speed;
                    // }
                    
                    if (ball_x > screenWidth * ai_active_factor) {
                        ai_target_y += paddle2.height * (ai_target_y - bonus_y)/(paddle2.x - bonus_x)/2.4;
                        if (aiDifficulty > 3){
                            if ((ai_target_y - bonus_y)/(paddle2.x - bonus_x)/2.4 > 0.25) {
                                ai_target_y = ball_y + (paddle2.height * (ai_target_y - bonus_y)/(paddle2.x - bonus_x)/4.8);
                            }
                        }
                    }
                    ai_target_y += ai_deviation;
                    if (ball_x < screenWidth * ai_active_factor && ball_x > screenWidth * 1 / 3) {
                        if (aiDifficulty > 3 && ball_y + ball_yv * 15 > 0 && ball_y + ball_yv * 15 < screenWidth){
                            ai_target_y = ball_y + ball_yv * 15;
                        }
                    }
                    else {
                        if (paddle2.y < (ai_target_y - paddle2.height / 2)) {
                            paddle2.y += paddle_speed;
                        }
                        if (paddle2.y > (ai_target_y - paddle2.height / 2)) {
                            paddle2.y -= paddle_speed;
                        }
                    }
                }

                DrawRectangleRec(paddle1, (Color) { 65, 175, 249, 255 });
                DrawRectangleRec(paddle2, (Color) { 253, 0, 0, 255 });

                DrawText(my_string, 2, 0, 21, RAYWHITE);
                DrawCircle(ball_x,ball_y,ball_radius,GREEN);
                DrawCircle(bonus_x,bonus_y,bonus_radius,bonus_active == 1 ? YELLOW : ORANGE);
            } else {
                DrawText(my_string, 2, 0, 21, RAYWHITE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
