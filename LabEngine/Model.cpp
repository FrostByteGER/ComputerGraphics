#include <QOpenGLTexture>
#include <memory>
#include "Model.h"
#include "Models.h"

Model::Model(const std::string& path, ShaderManager* sm, PhysicsThread* physicsSimulation, CollisionType collisionType, ModelType type) : shaderManager(sm), colliderType(collisionType)
{
	this->name = QString::fromStdString(path.substr(path.find_last_of('/') + 1,std::string::npos));
	qDebug() << "CREATING NEW MODEL:" << name;
	shaderID = shaderManager->loadShader();
	qDebug() << "SHADERID: " <<shaderID;
	switch (collisionType) {
		case COLLISION_SPHERE:
			this->collider = new PhysicsSphere(physicsSimulation, this, &(this->transform));
			qDebug() << "CREATING NEW PHYSICS SPHERE";
			break;
		case COLLISION_BOX:
			this->collider = new PhysicsBox(physicsSimulation, this, &(this->transform));
			qDebug() << "CREATING NEW PHYSICS BOX";
			break;
		default:
			this->collider = new PhysicsSphere(physicsSimulation, this, &(this->transform));
			qDebug() << "CREATING NEW PHYSICS SPHERE";
			break;
	}

	this->loadModel(path, type);
}

Model::Model(const std::string& path, const QString& name, ShaderManager* sm, PhysicsThread* physicsSimulation, CollisionType collisionType, ModelType type) : name(name), shaderManager(sm), colliderType(collisionType)
{
	qDebug() << "CREATING NEW MODEL:" << this->name;
	shaderID = shaderManager->loadShader();
	qDebug() << "SHADERID: " <<shaderID;
	switch (collisionType) {
		case COLLISION_SPHERE:
			this->collider = new PhysicsSphere(physicsSimulation, this, &(this->transform));
			qDebug() << "CREATING NEW PHYSICS SPHERE";
			break;
		case COLLISION_BOX:
			this->collider = new PhysicsBox(physicsSimulation, this, &(this->transform));
			qDebug() << "CREATING NEW PHYSICS BOX";
			break;
		default:
			this->collider = new PhysicsSphere(physicsSimulation, this, &(this->transform));
			qDebug() << "CREATING NEW PHYSICS SPHERE";
			break;
	}

	this->loadModel(path, type);
}

Model::~Model(){
	std::for_each(meshes.begin(), meshes.end(), std::default_delete<Mesh>());
	qDebug() << "DELETING MODEL" << this->name;
	delete collider;
}

void Model::DrawModel(){
	Shader* shader = shaderManager->getShader(shaderID);
	// If we don't have a shader, do NOT draw!
	if(!shader){
		return;
	}
	for(Mesh* m : meshes){
		m->DrawMesh(shader);
	}
}

void Model::loadModel(const std::string& path, const ModelType& type){
	this->directory = path.substr(0,path.find_last_of('/'));
	std::vector<QOpenGLTexture*> textures;
	Shader* shader = shaderManager->getShader(shaderID);
	if(!shader){
		qWarning() << "SHADER NOT FOUND";
	}
	switch(type){
		case MODEL_BOX:
			textures.push_back(loadTextureFromFile(crateTexturePath));
			this->meshes.push_back(new Mesh(Models::box_vertices, Models::box_normals, Models::box_uvs, Models::box_indices, textures, shader, this));
			break;
		case MODEL_SPHERE:
			this->meshes.push_back(new Mesh(Models::sphere_vertices, Models::sphere_normals, Models::sphere_uvs, Models::sphere_indices, textures, shader, this));
			break;
		case MODEL_FLOOR:
			this->meshes.push_back(new Mesh(Models::floor_vertices, Models::floor_normals, Models::floor_uvs, Models::floor_indices, textures, shader, this));
			break;
	}
}

QOpenGLTexture* Model::loadTextureFromFile(const std::string& path){
	QOpenGLTexture* tex = new QOpenGLTexture(QImage(QString::fromStdString(path)).mirrored());
	tex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	tex->setMagnificationFilter(QOpenGLTexture::Linear);
	return tex;
}

const Transform3D& Model::getTransform() const
{
	return transform;
}

void Model::setTransform(const Transform3D& value)
{
	transform = value;
}

const QVector3D& Model::getLocation() const
{
	return transform.translation();
}

void Model::setLocation(const QVector3D& location)
{
	transform.setTranslation(location);
}

void Model::setLocation(const float& x, const float& y, const float& z)
{
	transform.setTranslation(x, y, z);
}

const QVector3D& Model::getScale() const
{
	return transform.scale();
}

void Model::setScale(const QVector3D& scale)
{
	transform.setScale(scale);
}

void Model::setScale(const float& x, const float& y, const float& z)
{
	transform.setScale(x, y, z);
}

const QQuaternion& Model::getRotation() const
{
	return transform.rotation();
}

void Model::setRotation(const QQuaternion& rotation)
{
	transform.setRotation(rotation);
}

void Model::setRotation(const QVector3D& rotation)
{
	transform.setRotation(rotation);
}

void Model::setRotation(const float& x, const float& y, const float& z)
{
	transform.setRotation(x, y, z);
}

void Model::translate(const float& dx, const float& dy, const float& dz){
	transform.translate(dx, dy, dz);
}

void Model::translate(const QVector3D& translation){
	transform.translate(translation);
}

void Model::scale(const float& dx, const float& dy, const float& dz){
	transform.scale(dx, dy, dz);
}

void Model::scale(const float& uniformFactor){
	transform.scale(QVector3D(uniformFactor, uniformFactor, uniformFactor));
}

void Model::scale(const QVector3D& scale){
	transform.scale(scale);
}

void Model::rotate(const float& dyaw, const float& dpitch, const float& droll){
	transform.rotate(dyaw, dpitch, droll);
}

void Model::rotate(const float& angle, const QVector3D& axis){
	transform.rotate(angle, axis);
}

void Model::rotate(const float& angle, const float& dyaw, const float& dpitch, const float& droll){
	transform.rotate(angle, dyaw, dpitch, droll);
}

void Model::rotate(const QVector3D& drotation){
	transform.rotate(drotation);
}

void Model::rotate(const QQuaternion& drotation){
	transform.rotate(drotation);
}

QMatrix4x4 Model::toMatrix(){
	return transform.toMatrix();
}

QColor Model::getModelColor() const
{
	return modelColor;
}

void Model::setModelColor(const QColor& value)
{
	modelColor = value;
	for(Mesh* m : meshes){
		m->setMeshColor(value);
	}
}

void Model::setForceColorOnly(const bool& value)
{
	for(Mesh* m : meshes){
		m->setForceColorOnly(value);
	}
}

void Model::setColliderID(const int& id)
{
	collider->setID(id);
}

PhysicsObject* Model::getCollider() const
{
	return collider;
}

void Model::setCollider(PhysicsObject* value)
{
	collider = value;
}

bool Model::isValid() const
{
	return valid;
}

QString Model::getName() const
{
	return name;
}
