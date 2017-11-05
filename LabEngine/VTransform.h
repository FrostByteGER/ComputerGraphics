#pragma once

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

//
// Idea originally by Trent Reed
// This class is based on the tutorial Qt5 OpenGL Part 2: 3D Rendering
// Link: http://www.trentreed.net/blog/qt5-opengl-part-2-3d-rendering/
// However no copy-paste was made and everything has been understood and is used in the project.
//

class VTransform
{
	public:
		VTransform();

		static const QVector3D LocalForward;
		static const QVector3D LocalUp;
		static const QVector3D LocalRight;

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

		void setTranslation(const QVector3D& t);
		void setTranslation(const float& x, const float& y, const float& z);
		void setTranslationX(const float& x);
		void setTranslationY(const float& y);
		void setTranslationZ(const float& z);
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

		// Operators
		inline VTransform operator +(const VTransform& other){
			VTransform combined;
			combined.m_position = this->m_position + other.m_position;
			combined.m_rotation = this->m_rotation + other.m_rotation;
			combined.m_scale    = this->m_scale    + other.m_scale;
			combined.m_world    = this->m_world    + other.m_world;
			return combined;
		}

		inline VTransform operator -(const VTransform& other){
			VTransform combined;
			combined.m_position = this->m_position - other.m_position;
			combined.m_rotation = this->m_rotation - other.m_rotation;
			combined.m_scale    = this->m_scale    - other.m_scale;
			combined.m_world    = this->m_world    - other.m_world;
			return combined;
		}

		inline VTransform& operator +=(const VTransform& other){
			this->m_position += other.m_position;
			this->m_rotation += other.m_rotation;
			this->m_scale    += other.m_scale;
			this->m_world    += other.m_world;
			return *this;
		}

		inline VTransform& operator -=(const VTransform& other){
			this->m_position -= other.m_position;
			this->m_rotation -= other.m_rotation;
			this->m_scale    -= other.m_scale;
			this->m_world    -= other.m_world;
			return *this;
		}

		inline bool operator ==(const VTransform& other){
			if(this->m_position == other.m_position && this->m_rotation == other.m_rotation && this->m_scale == other.m_scale && this->m_world == other.m_world) return true;
			else return false;
		}

		inline bool operator !=(const VTransform& other){
			if(this->m_position != other.m_position || this->m_rotation != other.m_rotation || this->m_scale != other.m_scale || this->m_world != other.m_world) return true;
			else return false;
		}

	private:
		bool needsUpdate;
		QVector3D m_position;
		QVector3D m_scale;
		QQuaternion m_rotation;
		QMatrix4x4 m_world;
};

inline VTransform::VTransform() : needsUpdate(true), m_scale(1.0f, 1.0f, 1.0f) {}

inline void VTransform::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void VTransform::scale(float dx, float dy,float dz) { scale(QVector3D(dx, dy, dz)); }
inline void VTransform::scale(float factor) { scale(QVector3D(factor, factor, factor)); }
inline void VTransform::rotate(const float& angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void VTransform::rotate(const float& angle, const float& dx, const float& dy, const float& dz) { rotate(QQuaternion::fromAxisAndAngle(dx, dy, dz, angle)); }
inline void VTransform::rotate(const float& dyaw, const float& dpitch, const float& droll){ rotate(QQuaternion::fromEulerAngles(dyaw, dpitch, droll));}
inline void VTransform::rotate(const QVector3D& drotation) {rotate(QQuaternion::fromEulerAngles(drotation));}
inline void VTransform::grow(float dx, float dy, float dz) { grow(QVector3D(dx, dy, dz)); }
inline void VTransform::grow(float factor) { grow(QVector3D(factor, factor, factor)); }

inline void VTransform::setTranslation(const float& x, const float& y, const float& z) { setTranslation(QVector3D(x, y, z)); }
inline void VTransform::setTranslationX(const float& x) { setTranslation(QVector3D(x, m_position.y(), m_position.z())); }
inline void VTransform::setTranslationY(const float& y) { setTranslation(QVector3D(m_position.x(), y, m_position.z())); }
inline void VTransform::setTranslationZ(const float& z) { setTranslation(QVector3D(m_position.x(), m_position.y(), z)); }
inline void VTransform::setScale(const float& x, const float& y, const float& z) { setScale(QVector3D(x, y, z)); }
inline void VTransform::setScale(const float& k) { setScale(QVector3D(k, k, k)); }
inline void VTransform::setRotation(const float& angle, const QVector3D& axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void VTransform::setRotation(const float& angle, const float& ax, const float& ay, const float& az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }
inline void VTransform::setRotation(const float& x, const float& y, const float& z) { setRotation(QQuaternion::fromEulerAngles(x, y, z)); }
inline void VTransform::setRotation(const QVector3D& rotation) { setRotation(QQuaternion::fromEulerAngles(rotation)); }

inline const QVector3D& VTransform::translation() const { return m_position; }
inline const QVector3D& VTransform::scale() const { return m_scale; }
inline const QQuaternion& VTransform::rotation() const { return m_rotation; }
