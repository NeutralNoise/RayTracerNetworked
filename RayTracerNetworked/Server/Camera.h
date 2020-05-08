#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "Vector.h"

struct CameraRotation
{
	Vector CameraX;
	Vector CameraY;
	Vector CameraZ;
};

class Camera
{
public:
	Vector GetPosition() {
		return m_position;
	}

	void SetPosition(const Vector &v) {
		m_position = v;
	}

	void SetRotation(const CameraRotation &r) {
		//Just use this for now.
		m_rotation.CameraZ = m_position.Normalize();
		m_rotation.CameraX = m_rotation.CameraZ.CrossProduct(Vector(0.0f, 0.0f, 1.0f)).Normalize();
		m_rotation.CameraY = m_rotation.CameraZ.CrossProduct(m_rotation.CameraX).Normalize();
	}

	CameraRotation GetRotation() const {
		return m_rotation;
	}

	float GetFov() const {
		return m_fov;
	}

	void SetFov(const float &fov) {
		m_fov = fov;
	}

private:
	Vector m_position;
	CameraRotation m_rotation;
	float m_fov = 0;

};

#endif // !CAMERA_H_INCLUDED