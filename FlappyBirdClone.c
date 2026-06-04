#include <stdio.h>
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    //seeding time
    srand((unsigned)time(NULL));

    //collecting random num for pipe spawn
    int pipe_num = rand() % 4;

    //creating window
    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "FlappyBirdClone");
    SetTargetFPS(60);

    //loading textures
    Texture2D background = LoadTexture("background.png");
    Texture2D pipe = LoadTexture("pipe.png");
    Texture2D upsidedown_pipe = LoadTexture("upsidedown_pipe.png");
    Texture2D ball = LoadTexture("ball.png");

    //declaring important variables
    int radius = 100;
    int score = 0;
    int gameOver = 0;
    int pipeX = 800;
    int pipe_speed = 4;
    int ballX = 200;
    int ballY = 300;

    //opening window
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(GRAY);
        DrawTexture(background, 0, 0, WHITE);

        //game loop only allowing pipe movement if the game is not over
        if (gameOver == 0)
        {
            DrawRectangle(10, 10, 180, 50, Fade(BLACK, 0.5f));
            DrawText(TextFormat("score: %i", score), 20, 20, 30, WHITE);

            pipeX -= pipe_speed;

            if (pipeX < -201)
            {
                pipeX = 800;
                pipe_num = rand() % 4;
                score++;
            }

            //moves character up unless already at the top of the screen
            if (IsKeyPressed(KEY_SPACE) && ballY > 0)
                ballY -= 100;

            //gravity
            if (ballY < 600)
                ballY += 4;
        }

        //drawing character
        DrawTexture(ball, ballX - radius, ballY - radius, WHITE);

        //next 4 if statements draw a pipe depending on the random number, check boundries against the character, and update the x position of the pipe
        if (pipe_num == 0)
        {
            DrawTexture(pipe, pipeX, 400, WHITE);

            if (ballX + radius - 100 >= pipeX &&
                ballX - radius + 100 <= pipeX + 201 - 30 &&
                ballY + radius - 100 >= 400 &&
                ballY - radius + 100 <= 400 + 535 - 60)
            {
                gameOver = 1;
            }
        }

        if (pipe_num == 1)
        {
            DrawTexture(pipe, pipeX, 200, WHITE);

            if (ballX + radius - 100 >= pipeX &&
                ballX - radius + 100 <= pipeX + 201 - 30 &&
                ballY + radius - 100 >= 200 &&
                ballY - radius + 100 <= 200 + 535 - 60)
            {
                gameOver = 1;
            }
        }

        if (pipe_num == 2)
        {
            DrawTexture(upsidedown_pipe, pipeX, -200, WHITE);

            if (ballX + radius - 100 >= pipeX &&
                ballX - radius + 100 <= pipeX + 201 - 30 &&
                ballY + radius >= -200 &&
                ballY - radius <= -200 + 535 - 60)
            {
                gameOver = 1;
            }
        }

        if (pipe_num == 3)
        {
            DrawTexture(upsidedown_pipe, pipeX, -400, WHITE);

            if (ballX + radius - 100 >= pipeX &&
                ballX - radius + 100 <= pipeX + 201 - 30 &&
                ballY + radius >= -400 &&
                ballY - radius <= -400 + 535 - 60)
            {
                gameOver = 1;
            }
        }

        //checks if the game is over and prints information if it is
        if (gameOver == 1)
        {
           DrawRectangle(200, 180, 400, 220, Fade(BLACK, 0.6f));

           DrawText("GAME OVER!", 260, 200, 45, RED);

           DrawText(TextFormat("score: %i", score), 340, 270, 30, WHITE);

           DrawText("Press R to restart", 280, 330, 25, LIGHTGRAY);

            if (IsKeyPressed(KEY_R))
            {
                gameOver = 0;
                pipeX = 800;
                score = 0;
                ballY = 300;
                pipe_num = rand() % 4;
            }
        }

    //everything from here on is simply unloading each texture and ending the program
        EndDrawing();
    }

    UnloadTexture(ball);
    UnloadTexture(background);
    UnloadTexture(pipe);
    UnloadTexture(upsidedown_pipe);

    CloseWindow();

    return 0;
}
