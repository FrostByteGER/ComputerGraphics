#pragma once

#include "VTransform.h"

class Camera
{
	public:

		// Constants
		static const QVector3D LocalForward;
		static const QVector3D LocalUp;
		static const QVector3D LocalRight;

		Camera();

		// Transform By (Add/Scale)
		void translate(const QVector3D &dt);
		void translate(float dx, float dy, float dz);
		void rotate(const QQuaternion &dr);
		void rotate(float angle, const QVector3D &axis);
		void rotate(float angle, float ax, float ay, float az);

		// Transform To (Setters)
		void setTranslation(const QVector3D &t);
		void setTranslation(float x, float y, float z);
		void setRotation(const QQuaternion &r);
		void setRotation(float angle, const QVector3D &axis);
		void setRotation(float angle, float ax, float ay, float az);

		// Accessors
		const QVector3D& translation() const;
		const QQuaternion& rotation() const;
		const QMatrix4x4& toMatrix();

		// Queries
		QVector3D forward() const;
		QVector3D right() const;
		QVector3D up() const;

	private:
		bool needsUpdate;
		QVector3D m_translation;
		QQuaternion m_rotation;
		QMatrix4x4 m_world;

#ifndef QT_NO_DATASTREAM
		friend QDataStream &operator<<(QDataStream &out, const Camera &transform);
		friend QDataStream &operator>>(QDataStream &in, Camera &transform);
#endif
};


Q_DECLARE_TYPEINFO(Camera, Q_MOVABLE_TYPE);

// Constructors
inline Camera::Camera() : needsUpdate(true) {}

// Transform By (Add/Scale)
inline void Camera::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Camera::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Camera::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Transform To (Setters)
inline void Camera::setTranslation(float x, float y, float z) { setTranslation(QVector3D(x, y, z)); }
inline void Camera::setRotation(float angle, const QVector3D &axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Camera::setRotation(float angle, float ax, float ay, float az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Accessors
inline const QVector3D& Camera::translation() const { return m_translation; }
inline const QQuaternion& Camera::rotation() const { return m_rotation; }

// Qt Streams
#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Camera &transform);
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const Camera &transform);
QDataStream &operator>>(QDataStream &in, Camera &transform);
#endif
