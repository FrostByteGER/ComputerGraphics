#pragma once


#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform3D
{
	public:
		// Constructors
		Transform3D();

		// Constants
		static const QVector3D LocalForward;
		static const QVector3D LocalUp;
		static const QVector3D LocalRight;

		// Transform By (Add/Scale)
		void translate(const QVector3D &dt);
		void translate(float dx, float dy, float dz);
		void scale(const QVector3D &ds);
		void scale(float dx, float dy, float dz);
		void scale(float factor);
		void rotate(const QQuaternion& dr);
		void rotate(const float& angle, const QVector3D& axis);
		void rotate(const float& angle, const float& dx, const float& dy, const float& dz);
		void rotate(const float& dyaw, const float& dpitch, const float& droll);
		void rotate(const QVector3D& drotation);
		void grow(const QVector3D &ds);
		void grow(float dx, float dy, float dz);
		void grow(float factor);

		// Transform To (Setters)
		void setTranslation(const QVector3D& t);
		void setTranslation(const float& x, const float& y, const float& z);
		void setScale(const QVector3D& s);
		void setScale(const float& x, const float& y, const float& z);
		void setScale(const float& k);
		void setRotation(const QQuaternion& r);
		void setRotation(const float& angle, const QVector3D& axis);
		void setRotation(const float& angle, const float& ax, const float& ay, const float& az);
		void setRotation(const float& x, const float& y, const float& z);
		void setRotation(const QVector3D& rotation);

		// Accessors
		const QVector3D& translation() const;
		const QVector3D& scale() const;
		const QQuaternion& rotation() const;
		const QMatrix4x4& toMatrix();

		// Queries
		QVector3D forward() const;
		QVector3D up() const;
		QVector3D right() const;

	private:
		bool needsUpdate;
		QVector3D m_position;
		QVector3D m_scale;
		QQuaternion m_rotation;
		QMatrix4x4 m_world;

#ifndef QT_NO_DATASTREAM
		friend QDataStream &operator<<(QDataStream &out, const Transform3D &transform);
		friend QDataStream &operator>>(QDataStream &in, Transform3D &transform);
#endif
};

Q_DECLARE_TYPEINFO(Transform3D, Q_MOVABLE_TYPE);

inline Transform3D::Transform3D() : needsUpdate(true), m_scale(1.0f, 1.0f, 1.0f) {}

// Transform By (Add/Scale)
inline void Transform3D::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Transform3D::scale(float dx, float dy,float dz) { scale(QVector3D(dx, dy, dz)); }
inline void Transform3D::scale(float factor) { scale(QVector3D(factor, factor, factor)); }
inline void Transform3D::rotate(const float& angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3D::rotate(const float& angle, const float& dx, const float& dy, const float& dz) { rotate(QQuaternion::fromAxisAndAngle(dx, dy, dz, angle)); }
inline void Transform3D::rotate(const float& dyaw, const float& dpitch, const float& droll){ rotate(QQuaternion::fromEulerAngles(dyaw, dpitch, droll));}
inline void Transform3D::rotate(const QVector3D& drotation) {rotate(QQuaternion::fromEulerAngles(drotation));}
inline void Transform3D::grow(float dx, float dy, float dz) { grow(QVector3D(dx, dy, dz)); }
inline void Transform3D::grow(float factor) { grow(QVector3D(factor, factor, factor)); }

// Transform To (Setters)
inline void Transform3D::setTranslation(const float& x, const float& y, const float& z) { setTranslation(QVector3D(x, y, z)); }
inline void Transform3D::setScale(const float& x, const float& y, const float& z) { setScale(QVector3D(x, y, z)); }
inline void Transform3D::setScale(const float& k) { setScale(QVector3D(k, k, k)); }
inline void Transform3D::setRotation(const float& angle, const QVector3D& axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3D::setRotation(const float& angle, const float& ax, const float& ay, const float& az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }
inline void Transform3D::setRotation(const float& x, const float& y, const float& z) { setRotation(QQuaternion::fromEulerAngles(x, y, z)); }
inline void Transform3D::setRotation(const QVector3D& rotation) { setRotation(QQuaternion::fromEulerAngles(rotation)); }

// Accessors
inline const QVector3D& Transform3D::translation() const { return m_position; }
inline const QVector3D& Transform3D::scale() const { return m_scale; }
inline const QQuaternion& Transform3D::rotation() const { return m_rotation; }

// Qt Streams
#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Transform3D &transform);
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const Transform3D &transform);
QDataStream &operator>>(QDataStream &in, Transform3D &transform);
#endif
