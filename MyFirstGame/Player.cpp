#include <corecrt_math_defines.h>
#include <SFML/Window.hpp>
#include "Unit.h"

using namespace sf;

class Player : public Unit
{
public:
    Player(RectangleShape b) : Unit(0.5f, 100, 1.0f, b) {
    }

    void faceCursor(Vector2i& mousePosition) {
        Vector2f playerPosition = body.getPosition();

        float directionVectorX = (playerPosition.x - mousePosition.x) * 100.0f;
        float directionVectorY = (playerPosition.y - mousePosition.y) * 100.0f;

        float angle = static_cast<float>(atan2(directionVectorY, directionVectorX) * (180.0f / M_PI));

        body.setRotation(angle + 180);
    }
};

