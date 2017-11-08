#pragma once

#include <assimp/scene.h>
#include <vector>
#include "Mesh.h"
#include "ShaderManager.h"
#include "PhysicsObject.h"
#include "PhysicsThread.h"

enum CollisionType {
	COLLISION_BOX,
	COLLISION_SPHERE
};

class Model
{
	public:
		Model(const std::string& path, ShaderManager* sm, PhysicsThread* physicsSimulation, CollisionType collisionType = COLLISION_SPHERE);
		~Model();
		void DrawModel();

		const Transform3D& getTransform() const;
		void setTransform(const Transform3D& value);
		const QVector3D& getLocation() const;
		void setLocation(const QVector3D& location);
		void setLocation(const float& x, const float& y, const float& z);
		const QVector3D& getScale() const;
		void setScale(const QVector3D& scale);
		void setScale(const float& x, const float& y, const float& z);
		const QQuaternion& getRotation() const;
		void setRotation(const QQuaternion& rotation);
		void setRotation(const QVector3D& rotation);
		void setRotation(const float& x, const float& y, const float& z);

		void translate(const QVector3D& translation);
		void translate(const float& dx, const float& dy, const float& dz);
		void scale(const QVector3D& scale);
		void scale(const float& uniformFactor);
		void scale(const float& dx, const float& dy, const float& dz);
		void rotate(const float& angle, const float& dyaw, const float& dpitch, const float& droll);
		void rotate(const QVector3D& drotation);
		void rotate(const QQuaternion& drotation);
		void rotate(const float& angle, const QVector3D& axis);
		void rotate(const float& dyaw, const float& dpitch, const float& droll);
		void setForceColorOnly(const bool& value);
		void setColliderID(const int& id);

		QMatrix4x4 toMatrix();

		QColor getModelColor() const;
		void setModelColor(const QColor& value);

		PhysicsObject* getCollider() const;
		void setCollider(PhysicsObject* value);

		bool isValid() const;

		QString getName() const;

	private:
		QString name;
		size_t shaderID;
		ShaderManager* shaderManager;
		//TODO: Maybe change to smartpointer!
		std::vector<Mesh*> meshes;
		std::string directory;
		Transform3D transform;
		QColor modelColor;
		PhysicsObject* collider;
		CollisionType colliderType;
		bool valid = true;
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<QOpenGLTexture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		QOpenGLTexture* loadTextureFromFile(const std::string& name, const std::string& directory);
};

