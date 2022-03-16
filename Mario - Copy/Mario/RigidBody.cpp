#include "RigidBody.h"










void RigidBody::Update(float deltaTime) {
	m_accelaration.X = (m_Force.X + m_Friction.X) / m_Mass; //force = mass * acceleration and total force is applied force - friction so basically (acceleration = (force / mass)) the reason why its + instead of - is because we dont have the applied 
	m_accelaration.Y = m_Gravity + m_Force.Y/m_Mass;
	m_Velocity = m_accelaration * deltaTime;
	m_Position = m_Velocity * deltaTime;
}


RigidBody::~RigidBody()
{
}

