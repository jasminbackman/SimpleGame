#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class Unit
{
protected:
	int health;
	float speed;
	float damage;
	RectangleShape body;

	Unit(float speed, int health, float damage, RectangleShape body) {
		Unit::health = health;
		Unit::damage = damage;
		Unit::speed = speed;
		Unit::body = body;
		Vector2f size = body.getSize();
		Unit::body.setOrigin(static_cast<float>(size.x * 0.5), static_cast<float>(size.y * 0.5));
	}

public:
	void move(Vector2f& movement, float& delta_time) {
		body.move(movement.x * speed * delta_time, movement.y * speed * delta_time);
	}

	float& getSpeed() {
		return speed;
	}

	float& getDamage() {
		return damage;
	}

	RectangleShape& getBody() {
		return body;
	}
};

