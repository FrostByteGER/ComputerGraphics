#include "VTransform.h"
#include <QDebug>

const QVector3D VTransform::LocalForward(0.0f, 0.0f, 1.0f);
const QVector3D VTransform::LocalUp(0.0f, 1.0f, 0.0f);
const QVector3D VTransform::LocalRight(1.0f, 0.0f, 0.0f);

// Transform By (Add/Scale)
void VTransform::translate(const QVector3D &dt)
{
	needsUpdate = true;
	m_position += dt;
}

void VTransform::scale(const QVector3D &ds)
{
	needsUpdate = true;
	m_scale *= ds;
}

void VTransform::rotate(const QQuaternion &dr)
{
	needsUpdate = true;
	m_rotation = dr * m_rotation;
}

void VTransform::grow(const QVector3D &ds)
{
	needsUpdate = true;
	m_scale += ds;
}

// Transform To (Setters)
void VTransform::setTranslation(const QVector3D& t)
{
	needsUpdate = true;
	m_position = t;
}

void VTransform::setScale(const QVector3D& s)
{
	needsUpdate = true;
	m_scale = s;
}

void VTransform::setRotation(const QQuaternion& r)
{
	needsUpdate = true;
	m_rotation = r;
}

// Accessors
const QMatrix4x4 &VTransform::toMatrix()
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
QVector3D VTransform::forward() const
{
	return m_rotation.rotatedVector(LocalForward);
}

QVector3D VTransform::up() const
{
	return m_rotation.rotatedVector(LocalUp);
}

QVector3D VTransform::right() const
{
	return m_rotation.rotatedVector(LocalRight);
}

// Qt Streams
QDebug operator<<(QDebug dbg, const VTransform &transform)
{
	dbg << "Transform3D\n{\n";
	dbg << "Position: <" << transform.translation().x() << ", " << transform.translation().y() << ", " << transform.translation().z() << ">\n";
	dbg << "Rotation: <" << transform.rotation().x() << ", " << transform.rotation().y() << ", " << transform.rotation().z() << " | " << transform.rotation().scalar() << ">\n";
	dbg << "Scale: <" << transform.scale().x() << ", " << transform.scale().y() << ", " << transform.scale().z() << ">\n}";
	return dbg;
}

QDataStream &operator<<(QDataStream &out, const VTransform &transform)
{
	out << transform.translation();
	out << transform.rotation();
	out << transform.scale();
	return out;
}

QDataStream &operator>>(QDataStream &in, VTransform &transform)
{
	QVector3D position;
	QVector3D rotation;
	QVector3D scale;
	in >> position;
	in >> rotation;
	in >> scale;
	transform.setTranslation(position);
	transform.setRotation(rotation);
	transform.setScale(scale);
	return in;
}
