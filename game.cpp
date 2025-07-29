#include "raylib.h"

// WINDOW size
const int screenWidth = 800;
const int screenHeight = 450;

void borderPlayer(Vector2 *ballPos, float ballRad, float ballSpd);

int main()
{
    InitWindow(screenWidth, screenHeight, "Raylib Example - Moving Ball");

    // Set the ball's initial position
    Vector2 ballPosition = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
    float ballRadius = 20.0f;
    float ballSpeed = 200.0f;

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose())
    {
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
