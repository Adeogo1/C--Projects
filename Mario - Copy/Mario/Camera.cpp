#include "Camera.h"





Camera* Camera::s_Instance = nullptr;

void Camera::Update(float deltaTime) {
	if (m_Target != nullptr)// we want to make sure that this target exists
	{
		cameraRect.x = m_Target->X - SCREEN_WIDTH / 2;
		cameraRect.y = m_Target->Y - SCREEN_HEIGHT / 2;

		if (cameraRect.x < 0)
		{
			cameraRect.x = 0;
		}
		if (cameraRect.y < 0)
		{
			cameraRect.y = 0;
		}
		//					how widde the map is
		if (cameraRect.x > (10 * SCREEN_WIDTH - cameraRect.w))// basically if the camera/player goes past the middle of screen it scrolls along with it
		{
			cameraRect.x = (10 * SCREEN_WIDTH - cameraRect.w);
		}
		if (cameraRect.y > (SCREEN_HEIGHT - cameraRect.h))
		{
			cameraRect.y = (SCREEN_HEIGHT - cameraRect.h);
		}
		m_Position = Vector2D(cameraRect.x, cameraRect.y);
	}
}


Camera::~Camera()
{
	delete s_Instance;
	s_Instance = nullptr;
	delete m_Target;
	m_Target = nullptr;
}