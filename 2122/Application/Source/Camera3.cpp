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
	this->minigamestatus = false;
	this->EquipNum = 0;
	Reset();
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 100.f;
	static const float ZOOM_SPEED = 100.f;

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

	AbleStand = 0;
	if (Application::IsKeyPressed('W'))
	{
		position = position + view * ZOOM_SPEED * static_cast<float>(dt);
		BoundaryCheck(view, right, ZOOM_SPEED, dt, 'W');
	}
	DetectAbleStand();
	if (Application::IsKeyPressed('S'))
	{
		position = position - view * ZOOM_SPEED * static_cast<float>(dt);
		BoundaryCheck(view, right, ZOOM_SPEED, dt, 'S');
	}
	DetectAbleStand();
	if (Application::IsKeyPressed('A'))
	{
		position = position - right * ZOOM_SPEED * static_cast<float>(dt);
		BoundaryCheck(view, right, ZOOM_SPEED, dt, 'A');
	}
	DetectAbleStand();
	if (Application::IsKeyPressed('D'))
	{
		position = position + right * ZOOM_SPEED * static_cast<float>(dt);
		BoundaryCheck(view, right, ZOOM_SPEED, dt, 'D');
	}
	DetectAbleStand();
	target = position + view;

	if (Application::IsKeyPressed('Q'))
	{
		//std::cout << "\nUp:" << up.x << " " << up.y << " " << up.z << " " << "\n";
		//std::cout << "\nRight:" << right.x << " " << right.y << " " << right.z << " " << "\n";
		std::cout << "\nx: " << position.x << "   z: " << position.z;
	}
}

void Camera3::UpdateMini(double dt)
{

}

void Camera3::Reset()
{
	position = defaultPosition;
	TempPosition = position;
	target = defaultTarget;
	up = defaultUp;
}

bool Camera3::WorkStationBoundary()
{
	if (LevelNum <= 3 && LevelNum > 0)
		position.y = LevelNum * 50 - 20;
	else if(LevelNum >=4 && LevelNum <= 6)
		position.y = (LevelNum-3) * 50 - 36;
	//Boundary Checking for the table
	for (int i = 0; i < EquipNum; ++i)
	{
		if (( (position.x >= -60 && position.x <= -40) && LevelNum <= 3 ) || ( (position.x >= -60 && position.x <= -54) && LevelNum >= 4) ) 
		{
			if (i % 6 == 0 && (position.z >= 44 && position.z <= 63))
			{
				return true;
			}
			else if ( i % 6 == 1 && (position.z >= 25 && position.z <= 44) )
			{
				return true;
			}
			else if (i % 6 == 2 && (position.z >= 6 && position.z <= 25))
			{
				return true;
			}
			else if (i % 6 == 3 && (position.z <= -44 && position.z >= -63))
			{
				return true;
			}
			else if (i % 6 == 4 && (position.z <= -25 && position.z >= -44))
			{
				return true;
			}
			else if (i % 6 == 5 && (position.z <= -6 && position.z >= -25))
			{
				return true;
			}
		}
	}
	//Equipment Table
	if ((position.x > 39 && position.x < 63) && (position.y < 35 && position.y > 25))
	{
		if (position.z > 24 && position.z < 60)
		{
			return true;
		}
	}
	return false;
}

void Camera3::DetectAbleStand()
{
	//Boundary Checking for the table
	for (int i = 0; i < EquipNum; ++i)
	{
		//std::cout << "\ni%6:" << i % 6 << " EquipNum:" << EquipNum << " Ypos:" << position.y << " LevelNum:" << LevelNum;
		if (position.x >= -60 && position.x <= -40)
		{
			if (i % 6 == 0 && (position.z >= 44 && position.z <= 63))
			{
				AbleStand = 1;
			}
			else if (i % 6 == 1 && (position.z >= 25 && position.z <= 44))
			{
				AbleStand = 1;
			}
			else if (i % 6 == 2 && (position.z >= 6 && position.z <= 25))
			{
				AbleStand = 1;
			}
			else if (i % 6 == 3 && (position.z <= -44 && position.z >= -63))
			{
				AbleStand = 1;
			}
			else if (i % 6 == 4 && (position.z <= -25 && position.z >= -44))
			{
				AbleStand = 1;
			}
			else if (i % 6 == 5 && (position.z <= -6 && position.z >= -25))
			{
				AbleStand = 1;
			}
		}
	}
	if ((position.x > 39 && position.x < 63) && position.y < 35)
	{
		if (position.z > 24 && position.z < 60)
		{
			AbleStand = 1;
		}
	}
	if (AbleStand == 0)
	{
		AbleStand == 2;
	}
}

void Camera3::BoundaryCheck(Vector3 view, Vector3 right, const float ZOOM_SPEED, double dt, char KeyPressed)
{
	static bool InvalidMovement = false;

	//Map Boundary
	if (position.x > 445 || position.x < -445 || position.z > 445 || position.z < -445)
	{
		InvalidMovement = true;
	}
	// right wall
	if (position.x < 75 && position.x > 62)
	{
		if (position.z < 75 && position.z > -85)
		{
			InvalidMovement = true;
		}
	}

	// right entrance wall
	if (position.x < 75 && position.x > 18)
	{
		if (position.z < 75 && position.z > 60)
		{
			InvalidMovement = true;
		}
	}

	// left wall
	if (position.x < -57 && position.x > -70)
	{
		if (position.z < 78 && position.z > -70)
		{
			InvalidMovement = true;
		}
	}

	// left entrance wall
	if (position.x < -17 && position.x > -58)
	{
		if (position.z < 70 && position.z > 60)
		{
			InvalidMovement = true;
		}
	}

	// back wall
	if (position.x < 70 && position.x > -76)
	{
		if (position.z < -60 && position.z > -70)
		{
			InvalidMovement = true;
		}
	}

	//Front Wall for 2nd lvl and 3rd lvl
	if (position.x < 75 && position.x > -58 && position.y > 31)
	{
		if (position.z < 70 && position.z > 60)
		{
			InvalidMovement = true;
		}
	}

	//Buildings
	{
		//Left Building
		if (position.x > -185 && position.x < 185)
		{
			if (position.z > -413 && position.z < -186)
			{
				InvalidMovement = true;
			}
		}

		//Back Left Building
		if (position.x > -397 && position.x < -240)
		{
			if (position.z > -125 && position.z < 125)
			{
				InvalidMovement = true;
			}
		}

		//Middle Building
		if (position.x > -377 && position.x < -221)
		{
			if (position.z > -378 && position.z < -222)
			{
				InvalidMovement = true;
			}
		}

		//Right Building
		{
			if (position.x > 206 && position.x < 433)
			{
				if (position.z > 100 && position.z < 185)
				{
					InvalidMovement = true;
				}
			}

			if (position.x > 224 && position.x < 415)
			{
				if (position.z > 32 && position.z < 110)
				{
					InvalidMovement = true;
				}
			}

			if (position.x > 206 && position.x < 433)
			{
				if (position.z > -43 && position.z < 42)
				{
					InvalidMovement = true;
				}
			}

			if (position.x > 224 && position.x < 415)
			{
				if (position.z > -113 && position.z < -33)
				{
					InvalidMovement = true;
				}
			}

			if (position.x > 206 && position.x < 433)
			{
				if (position.z > -183 && position.z < -103)
				{
					InvalidMovement = true;
				}
			}
		}

		//Back Right Building
		{
			if (position.x > 245 && position.x < 415)
			{
				if (position.z > -386 && position.z < -215)
				{
					InvalidMovement = true;
				}
			}
			if (position.x > 228 && position.x < 247)
			{
				if (position.z > -389 && position.z < -294)
				{
					InvalidMovement = true;
				}
			}
		}
	}

	//Street Lights
	{
		//Grass Side
		if (position.z > 284 && position.z < 294)
		{
			if (position.x > -404 && position.x < -394)
			{
				InvalidMovement = true;
			}
			if (position.x > -104 && position.x < -94)
			{
				InvalidMovement = true;
			}
			if (position.x > 196 && position.x < 206)
			{
				InvalidMovement = true;
			}
		}
		//Building Side
		if (position.z > 205 && position.z < 215)
		{
			if (position.x > -256 && position.x < -246)
			{
				InvalidMovement = true;
			}
			if (position.x > 45 && position.x < 55)
			{
				InvalidMovement = true;
			}
			if (position.x > 345 && position.x < 355)
			{
				InvalidMovement = true;
			}
		}
	}


	if (WorkStationBoundary() == true)
	{
		InvalidMovement = true;
	}

	if (InvalidMovement == true)
	{
		if (KeyPressed == 'W')
		{
			position = position - view * ZOOM_SPEED * static_cast<float>(dt);
		}
		if (KeyPressed == 'S')
		{
			position = position + view * ZOOM_SPEED * static_cast<float>(dt);
		}
		if (KeyPressed == 'A')
		{
			position = position + right * ZOOM_SPEED * static_cast<float>(dt);
		}
		if (KeyPressed == 'D')
		{
			position = position - right * ZOOM_SPEED * static_cast<float>(dt);
		}
		InvalidMovement = false;
	}

}

