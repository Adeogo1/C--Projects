#pragma once
#include "Vector2D.h"
#include "Constants.h"




class RigidBody
{
public:
	RigidBody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}
	//setters for gravity and mass
	inline void SetMass(float mass) { m_Mass = mass; }
	inline float GetMass() { return m_Mass; }
	//getters for gravity and mass
	inline void SetGravity(float gravity) { m_Gravity = gravity; }

	//Force
	inline void ApplyForce(Vector2D F) { m_Force = F; }
	inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
	inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
	inline void UnSetForce() { m_Force = Vector2D(0, 0); }	//unset the force if we dont need it 

	//Friction
	inline void ApplyFriction(Vector2D F) { m_Friction = F; }
	inline void UnSetFriction() { m_Friction = Vector2D(0, 0); }


	inline Vector2D Position() { return m_Position; }
	inline Vector2D Velocity() { return m_Velocity; }
	inline Vector2D Acceleration() { return m_accelaration; }



	void Update(float deltaTime);

	~RigidBody();

private:
	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;

	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_accelaration;

};

