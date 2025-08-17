#include "raylib.h"
#include <string>
#include <random>
#include <time.h>
#include <thread>

// WINDOW size
const int screenWidth = 800;
const int screenHeight = 450;

int score = 0;

#define FOOD_BALL_SIZE 15.0f
#define START_BALL_SIZE 20.0f
#define POS_RATE 12
#define MAX_SCORE 32

void borderPlayer(Vector2 *ballPos, float ballRad, float ballSpd);
void foodEat(bool *eaten, Vector2 *randPos, Vector2 ballPos, float *ballRad);
bool tryGameAgain(float *ballRadius);
void winGame();

int main()
{
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Raylib Example - Moving Ball");

    // Set the ball's initial position
    Vector2 ballPosition = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
    Vector2 randPos = {0, 0};
    float ballRadius = START_BALL_SIZE;
    float ballSpeed = 200.0f;
    bool foodEaten = false;
    bool gameOver = false;
    char str_score[MAX_SCORE] = "";

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver)
        {
            ballRadius -= 0.1;

            // Move
            if (IsKeyDown(KEY_RIGHT))
                ballPosition.x += ballSpeed * GetFrameTime();
            if (IsKeyDown(KEY_LEFT))
                ballPosition.x -= ballSpeed * GetFrameTime();
            if (IsKeyDown(KEY_DOWN))
                ballPosition.y += ballSpeed * GetFrameTime();
            if (IsKeyDown(KEY_UP))
                ballPosition.y -= ballSpeed * GetFrameTime();

            borderPlayer(&ballPosition, ballRadius, ballSpeed);
            foodEat(&foodEaten, &randPos, ballPosition, &ballRadius);

            if (ballRadius <= 0)
            {
                gameOver = true;
                // reset ball position
                ballPosition = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
            }

            sprintf(str_score, "%d", score);
            DrawText("Score: ", 10, 10, 20, DARKGRAY);
            DrawText(str_score, 80, 10, 20, DARKGRAY);
            DrawCircleV(ballPosition, ballRadius, MAROON);
        }
        else
        {
            // Game Over text
            int fontSize = 50;
            int overTextWidth = MeasureText("Game Over!", fontSize);
            int posX = (screenWidth - overTextWidth) / 2;
            int posY = (screenHeight - fontSize) / 2 - 60;
            DrawText("Game Over!", posX, posY, fontSize, DARKGRAY);

            // Try Again button logic and drawing
            gameOver = !tryGameAgain(&ballRadius);
        }

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}

/***********/
// Function adds border logic into window.
// INPUT: ballPos - the position of the ball,
// ballRad - the radius of the ball,
// ballSpd - the speed of the ball.
// OUTPUT: None
/***********/
void borderPlayer(Vector2 *ballPos, float ballRad, float ballSpd)
{
    if (ballPos->y >= screenHeight - ballRad) // if hit bottom
    {
        ballPos->y -= ballSpd * GetFrameTime();
    }
    if (ballPos->x >= screenWidth - ballRad) // if hit right side
    {
        ballPos->x -= ballSpd * GetFrameTime();
    }
    if (ballPos->y <= ballRad) // if hit top
    {
        ballPos->y += ballSpd * GetFrameTime();
    }
    if (ballPos->x <= ballRad) // if hit left side
    {
        ballPos->x += ballSpd * GetFrameTime();
    }
}

/***********/
// Function adds food and eating to make ball smaller.
// INPUT: ballPos - the position of the ball,
// eaten - check if food was eaten
// ballRad - the radius of the ball,
// randPos - the random position of the food.
// OUTPUT: None
/***********/
void foodEat(bool *eaten, Vector2 *randPos, Vector2 ballPos, float *ballRad)
{
    if (!*eaten) // if food eaten
    {
        // get random pos
        randPos->x = static_cast<float>(rand() % screenWidth);
        randPos->y = static_cast<float>(rand() % screenHeight);
        *eaten = true;
    }

    if (CheckCollisionPointCircle(*randPos, ballPos, *ballRad)) // if eating food
    {
        *eaten = false;
        (*ballRad) += POS_RATE; // grow smaller
        // increment score
        score++;
    }
    
    // draw food onto screen
    DrawCircleV(*randPos, FOOD_BALL_SIZE, GREEN);
}

bool tryGameAgain(float *ballRadius)
{
    Rectangle button = { (screenWidth - 120) / 2, screenHeight / 2 + 20, 120, 50 };
    Vector2 mousePos = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mousePos, button);
    bool clicked = hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    DrawRectangleRec(button, hovering ? LIGHTGRAY : GRAY);
    DrawRectangleLines(button.x, button.y, button.width, button.height, BLACK);
    DrawText("Try again!", button.x + 10, button.y + 15, 20, BLACK);

    if (clicked)
    {
        *ballRadius = START_BALL_SIZE;
        return true;
    }

    return false;
}

// TODO - win condition 
/*
the ball gets to it's biggest size display win screen,
show score and give an option to play again.
*/
void winGame()
{
    // TODO
}