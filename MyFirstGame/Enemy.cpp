#include "Unit.h"

using namespace sf;

class Enemy : public Unit
{
public:
    Enemy(RectangleShape b) : Unit(0.05f, 10, 1.0f, b) {
    }
};

