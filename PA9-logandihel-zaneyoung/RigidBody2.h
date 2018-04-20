#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>

class RigidBody2 : public sf::RectangleShape {
public:
	RigidBody2(sf::Vector2f &size, sf::Vector2f &pos=sf::Vector2f(0.f, 0.f))
		: sf::RectangleShape(size)
	{
		// set the origin to the exact
		// center of the rigid body
		// (assuming uniform density)
		setOrigin(size / 2.f);
		setPosition(pos);

		// rendering properties
		setOutlineColor(sf::Color::Green);
		setOutlineThickness(2.f);
		setFillColor(sf::Color::Transparent);

		up = sf::Vector2f(0, -1);
		right = sf::Vector2f(1, 0);

		forwards = up;
		sideways = right;

		acceleration = sf::Vector2f(0.f, 0.f);
		velocity = sf::Vector2f(0.f, 0.f);
		force = sf::Vector2f(0.f, 0.f);

		updateUnitVectors();

		mass = 1.5E4; // 3000 kg
		inv_mass = 1 / mass;

		angV = 0;
		torque = 0;
	}

	void updatePhysics(float dt);

	/*
		The force vector is defined as F = <Fup, Fright>
		where Fup and Fright are floats.

		So calling addForce( <5, 0> )
		would accelerate the car forwards
	*/
	void addForce(sf::Vector2f &force);

	/*
		In 2D space, we define torque as a scalar rather
		than a vector. Torque is the rotational equivalent
		of force, and inertia is the rotational equivalent
		of mass. Angles increase in a clockwise manner with
		theta = 0 in the upwards direction.
	*/
	void addTorque(float torque);

private:
	/*
		Sets the unit vectors back to
		vel_up		<sin(x), cos(x)>
		vel_right	<cos(x), sin(x)>
	*/
	void updateUnitVectors();

private:
	/*
	Linear Movement
			^
			|
		---------
		|		|
		|		|
		|		|	----> (side force used for drifting)
		|		|
		|		|
		---------

		Note that the velocities and acceleration vectors
		will change on a rotation because they are 
		relative to the world.

		up		<sin(x), cos(x)>
		right	<cos(x), sin(x)>

		The force vector is defined as F = <Fup, Fright>
		where Fup and Fright are floats.
	*/
	sf::Vector2f up;
	sf::Vector2f right;

	sf::Vector2f forwards;
	sf::Vector2f sideways;
	
	/* 
		A = <Aup, Aright>
		V = <Vup, Vright>
	*/
	sf::Vector2f acceleration;
	sf::Vector2f velocity;

	// cumulative forces applied over frame
	// are in the same direction as velocitiy vectors
	// F = <Fup, Fright>
	sf::Vector2f force;
	float mass;
	float inv_mass;

	/*
	Rotational Movement
	*/
	float torque;
	float angV;
};