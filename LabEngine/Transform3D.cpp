#include "Transform3D.h"
#include <QDebug>

const QVector3D Transform3D::LocalForward(0.0f, 0.0f, 1.0f);
const QVector3D Transform3D::LocalUp(0.0f, 1.0f, 0.0f);
const QVector3D Transform3D::LocalRight(1.0f, 0.0f, 0.0f);

// Transform By (Add/Scale)
void Transform3D::translate(const QVector3D &dt)
{
	needsUpdate = true;
	m_position += dt;
}

void Transform3D::scale(const QVector3D &ds)
{
	needsUpdate = true;
	m_scale *= ds;
}

void Transform3D::rotate(const QQuaternion &dr)
{
	needsUpdate = true;
	m_rotation = dr * m_rotation;
}

void Transform3D::grow(const QVector3D &ds)
{
	needsUpdate = true;
	m_scale += ds;
}

// Transform To (Setters)
void Transform3D::setTranslation(const QVector3D& t)
{
	needsUpdate = true;
	m_position = t;
}

void Transform3D::setScale(const QVector3D& s)
{
	needsUpdate = true;
	m_scale = s;
}

void Transform3D::setRotation(const QQuaternion& r)
{
	needsUpdate = true;
	m_rotation = r;
}

// Accessors
const QMatrix4x4 &Transform3D::toMatrix()
{
	if (needsUpdate)
	{
		needsUpdate = false;
		m_world.setToIdentity();
		m_world.translate(m_position);
		m_world.rotate(m_rotation);
		m_world.scale(m_scale);
	}
	return m_world;
}

// Queries
QVector3D Transform3D::forward() const
{
	return m_rotation.rotatedVector(LocalForward);
}

QVector3D Transform3D::up() const
{
	return m_rotation.rotatedVector(LocalUp);
}

QVector3D Transform3D::right() const
{
	return m_rotation.rotatedVector(LocalRight);
}
