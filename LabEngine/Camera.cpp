#include "Camera.h"
#include <QDebug>

//
// Idea originally by Trent Reed
// This class is based on the tutorial Qt5 OpenGL Part 3b: Camera Control
// Link: http://www.trentreed.net/blog/qt5-opengl-part-3b-camera-control/
// However no copy-paste was made and everything has been understood and is used in the project.
//

const QVector3D Camera::LocalForward(0.0f, 0.0f, -1.0f);
const QVector3D Camera::LocalUp(0.0f, 1.0f, 0.0f);
const QVector3D Camera::LocalRight(1.0f, 0.0f, 0.0f);

void Camera::translate(const QVector3D &dt)
{
	needsUpdate = true;
	m_translation += dt;
}

void Camera::rotate(const QQuaternion &dr)
{
	needsUpdate = true;
	m_rotation = dr * m_rotation;
}

void Camera::setTranslation(const QVector3D &t)
{
	needsUpdate = true;
	m_translation = t;
}

void Camera::setRotation(const QQuaternion &r)
{
	needsUpdate = true;
	m_rotation = r;
}

const QMatrix4x4& Camera::toMatrix()
{
	if (needsUpdate)
	{
		needsUpdate = false;
		m_world.setToIdentity();
		m_world.rotate(m_rotation.conjugate());
		m_world.translate(-m_translation);
	}
	return m_world;
}

QVector3D Camera::forward() const
{
	return m_rotation.rotatedVector(LocalForward);
}

QVector3D Camera::right() const
{
	return m_rotation.rotatedVector(LocalRight);
}

QVector3D Camera::up() const
{
	return m_rotation.rotatedVector(LocalUp);
}
