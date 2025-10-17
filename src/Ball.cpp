#include "Ball.h"
#include <cstdlib> // for rand()
#include <ctime>

// ========== Ball methods ==========
Ball::Ball(float ballRadius, float ballSpeed, Vector2 ballPosition)
    : ballRadius(ballRadius), ballSpeed(ballSpeed), ballPosition(ballPosition) {}

void Ball::borderPlayer(void) {
    if (ballPosition.y >= 450 - ballRadius) ballPosition.y = ballRadius + 10;
    if (ballPosition.x >= 800 - ballRadius) ballPosition.x = ballRadius + 10;
    if (ballPosition.y <= ballRadius) ballPosition.y = 450 - ballRadius;
    if (ballPosition.x <= ballRadius) ballPosition.x = 800 - ballRadius;
}

bool Ball::tryGameAgain(void) {
    Rectangle button = { (800 - 120) / 2, 450 / 2 + 20, 120, 50 };
    Vector2 mousePos = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mousePos, button);
    bool clicked = hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    DrawRectangleRec(button, hovering ? LIGHTGRAY : GRAY);
    DrawRectangleLines(button.x, button.y, button.width, button.height, BLACK);
    DrawText("Try again!", button.x + 10, button.y + 15, 20, BLACK);

    if (clicked) {
        ballRadius = 20.0f; // START_BALL_SIZE
        return true;
    }
    return false;
}

bool Ball::winGame(void) {
    return ballRadius >= 800; // screenWidth
}

void Ball::drawBall(Color color, Texture2D texture) {
    Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dest = { ballPosition.x, ballPosition.y, ballRadius * 2, ballRadius * 2 };
    Vector2 origin = { ballRadius, ballRadius };
    DrawTexturePro(texture, src, dest, origin, 0.0f, WHITE);
}


bool Ball::gameLost(void) {
    if (ballRadius <= 0) {
        ballPosition = {400.0f, 225.0f}; // center
        return true;
    }
    return false;
}

void Ball::shrinkBall(void) {
    ballRadius -= 0.1f;
}

// ========== Food methods ==========
Food::Food(float ballRadius, float ballSpeed, Vector2 ballPosition, bool eaten)
    : Ball(ballRadius, ballSpeed, ballPosition), eaten(eaten) {}

void Food::foodEat(Ball* player, int* score) {
    if (!eaten) {
        ballPosition.x = static_cast<float>(rand() % 800); // screenWidth
        ballPosition.y = static_cast<float>(rand() % 450); // screenHeight
        eaten = true;
    }

    if (CheckCollisionCircles(ballPosition, ballRadius,
                              player->ballPosition, player->ballRadius)) {
        (*score)++;
        eaten = false;
        player->ballRadius += 12; // POS_RATE
    }
}

void Food::moveFood(void) {
    if (IsKeyDown(KEY_RIGHT)) ballPosition.x -= ballSpeed * GetFrameTime();
    if (IsKeyDown(KEY_LEFT))  ballPosition.x += ballSpeed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN))  ballPosition.y -= ballSpeed * GetFrameTime();
    if (IsKeyDown(KEY_UP))    ballPosition.y += ballSpeed * GetFrameTime();
}
