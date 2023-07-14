//
// Created by Administrator on 2023/5/22.
//

#include <Camera.h>

Camera::Camera(glm::vec3 position,
               glm::vec3 up,
               float yaw,
               float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                              MovementSpeed(SPEED),
                              MouseSensitivity(SENSITIVITY),
                              Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

[[maybe_unused]]
Camera::Camera(float posX, float posY, float posZ,
               float upX, float upY, float upZ,
               float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                         MovementSpeed(SPEED),
                                         MouseSensitivity(SENSITIVITY),
                                         Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

[[nodiscard]]
glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	auto velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
		case FORWARD:
			Position += Front * velocity;
			break;
		case BACKWARD:
			Position -= Front * velocity;
			break;
		case LEFT:
			Position -= Right * velocity;
			break;
		case RIGHT:
			Position += Right * velocity;
			break;
		default:
			break;
	}
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		Pitch = Pitch > 89.0f ? 89.0f : Pitch;
		Pitch = Pitch < -89.0f ? -89.0f : Pitch;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	Zoom -= static_cast<float>(yOffset);
	Zoom = Zoom < 1.0f ? 1.0f : Zoom;
	Zoom = Zoom > 45.0f ? 45.0f : Zoom;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front{cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
	                sin(glm::radians(Pitch)),
	                sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))};
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}