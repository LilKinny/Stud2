#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	Reset();
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 20.f;
	static const float ZOOM_SPEED = 20.f;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	if (Application::IsKeyPressed(VK_LEFT))
	{
		float yaw = CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		up = rotation * up;
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		up = rotation * up;
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed('W'))
	{
		position = position + view * ZOOM_SPEED * static_cast<float>(dt);
		if (position.x > 445 || position.x < -445 || position.z > 445 || position.z < -445)
		{
			position -= view * ZOOM_SPEED * static_cast<float>(dt);
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		position = position - view * ZOOM_SPEED * static_cast<float>(dt);
		if (position.x > 445 || position.x < -445 || position.z > 445 || position.z < -445)
		{
			position += view * ZOOM_SPEED * static_cast<float>(dt);
		}
	}
	if (Application::IsKeyPressed('A'))
	{
		position = position - right * ZOOM_SPEED * static_cast<float>(dt);
		if (position.x > 445 || position.x < -445 || position.z > 445 || position.z < -445)
		{
			position += right * ZOOM_SPEED * static_cast<float>(dt);
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		position = position + right * ZOOM_SPEED * static_cast<float>(dt);
		if (position.x > 445 || position.x < -445 || position.z > 445 || position.z < -445)
		{
			position -= right * ZOOM_SPEED * static_cast<float>(dt);
		}
	}
	position.y = defaultPosition.y;
	target = position + view;


	if (Application::IsKeyPressed('Q'))
	{
		//std::cout << "\nUp:" << up.x << " " << up.y << " " << up.z << " " << "\n";
		//std::cout << "\nRight:" << right.x << " " << right.y << " " << right.z << " " << "\n";
		std::cout << "\nx: " << position.x << "   z: " << position.z;
	}


	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	TempPosition = position;
	target = defaultTarget;
	up = defaultUp;
}