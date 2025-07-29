#include "raylib.h"
#include <random>
#include <time.h>

// WINDOW size
const int screenWidth = 800;
const int screenHeight = 450;

#define FOOD_BALL_SIZE 15.0f
#define NEG_RATE 8

void borderPlayer(Vector2 *ballPos, float ballRad, float ballSpd);
void foodEat(bool *eaten, Vector2 *randPos, Vector2 ballPos, float *ballRad);

int main()
{
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Raylib Example - Moving Ball");

    // Set the ball's initial position
    Vector2 ballPosition = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
    Vector2 randPos = {0, 0};
    float ballRadius = 20.0f;
    float ballSpeed = 200.0f;
    bool foodEaten = false;

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose())
    {
        ballRadius += 0.1;
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

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Move the ball with arrow keys", 10, 10, 20, DARKGRAY);
        DrawCircleV(ballPosition, ballRadius, MAROON);

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
        (*ballRad) -= NEG_RATE; // grow smaller
    }
    // draw food onto screen
    DrawCircleV(*randPos, FOOD_BALL_SIZE, GREEN);
}