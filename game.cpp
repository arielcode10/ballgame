#include "raylib.h"
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include "Ball.h"

// WINDOW size
const int screenWidth = 800;
const int screenHeight = 450;

int score = 0;

#define FOOD_BALL_SIZE 15.0f
#define MAX_FOOD 5
#define START_BALL_SIZE 20.0f
#define POS_RATE 12
#define MAX_SCORE 32


int main()
{
    // Build full path to image based on exe location
    std::string food_path = std::string(GetApplicationDirectory()) + "Images/large_green-monster.png";
     std::string player_path = std::string(GetApplicationDirectory()) + "Images/monster-player.png";
    
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Raylib Example - Moving Ball");
    // Set the ball's initial position
    Vector2 ballPosition = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
    float ballRadius = START_BALL_SIZE;
    float ballSpeed = 200.0f;
    bool foodEaten = false;
    bool gameOver = false;
    char str_score[MAX_SCORE] = "";
    Ball *player = new Ball(ballRadius, ballSpeed, ballPosition);
    // Food *food = new Food(ballRadius, ballSpeed, ballPosition, foodEaten);
    std::vector<Food*> foods;

    // Image 
    Image img = LoadImage(player_path.c_str());

    if (img.data == NULL) {
    printf("Failed to load image!\n");
    }

    Texture2D player_texture = LoadTextureFromImage(img);

    img = LoadImage(food_path.c_str());
    if (img.data == NULL) {
    printf("Failed to load image!\n");
    }

    Texture2D food_texture = LoadTextureFromImage(img);
    UnloadImage(img);

    // set foods
    for (int i = 0; i < MAX_FOOD; i++)
    {
        foods.push_back(new Food(ballRadius, ballSpeed, ballPosition, foodEaten));
    }

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (!gameOver)
        {
            ClearBackground(RAYWHITE);
            player->shrinkBall(); // shrink ball
            
            for (unsigned int i = 0; i < foods.size(); i++)
            {
                foods[i]->foodEat(player, &score); // player eat food
            }
            
            for (unsigned int i = 0; i < foods.size(); i++)
            {
                foods[i]->moveFood(); // player move to food
            }

            // if game over
            gameOver = player->gameLost() || player->winGame();

            for (unsigned int i = 0; i < foods.size(); i++)
            {
                foods[i]->drawBall(GREEN, food_texture);
            }
            
            player->drawBall(MAROON, player_texture);
            // draw score
            sprintf(str_score, "%d", score);
            DrawText("Score: ", 10, 10, 20, DARKGRAY);
            DrawText(str_score, 80, 10, 20, DARKGRAY);
        }
        else
        {
            if (player->winGame())
            {
                // Game Won text
                int fontSize = 50;
                int wonTextWidth = MeasureText("You won!", fontSize);
                int scoreTextWidth = MeasureText("Score!", fontSize);
                int posX = (screenWidth - wonTextWidth) / 2;
                int posY = (screenHeight - fontSize) / 2 - 60;
                DrawText("You won!", posX, posY - 20, fontSize, WHITE);
                DrawText("Score: ", posX, posY + 40, fontSize, WHITE);
                DrawText(str_score, posX + scoreTextWidth + 20, posY + 40, fontSize, WHITE);
                // reset score
                score = 0;
            }
            else
            {
                // Game Over text
                int fontSize = 50;
                int overTextWidth = MeasureText("Game Over!", fontSize);
                int posX = (screenWidth - overTextWidth) / 2;
                int posY = (screenHeight - fontSize) / 2 - 60;
                DrawText("Game Over!", posX, posY, fontSize, DARKGRAY);
                // reset score
                score = 0;
            }
            foodEaten = false;
            // Try Again button logic and drawing
            gameOver = !player->tryGameAgain();
        }

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(food_texture);
    UnloadTexture(player_texture);
    CloseWindow();

    return 0;
}

