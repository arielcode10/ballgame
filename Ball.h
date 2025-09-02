#pragma once
#include "raylib.h"

// Forward declaration
class Food;

class Ball {
protected:
    float ballRadius;
    float ballSpeed;
    Vector2 ballPosition;

public:
    Ball(float ballRadius, float ballSpeed, Vector2 ballPosition);

    void borderPlayer(void);
    bool tryGameAgain(void);
    bool winGame(void);
    void drawBall(Color color);
    bool gameLost(void);
    void shrinkBall(void);

    friend class Food; // allow Food to access protected members
};

class Food : public Ball {
private:
    bool eaten;

public:
    Food(float ballRadius, float ballSpeed, Vector2 ballPosition, bool eaten = false);

    void foodEat(Ball* player, int* score); 
    void moveFood(void);
};
