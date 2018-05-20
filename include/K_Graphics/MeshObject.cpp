#include"MeshModel.h"

namespace K_Graphics {

	////////
	//public
	////

	MeshObject::MeshObject(MeshModel* model) {
		this->drawModel = nullptr;

		if (!Initialize(model)) {
			throw("modelData is nullptr");
		}
	}
	MeshObject::~MeshObject() {
		Finalize();
	}

	bool MeshObject::Initialize(MeshModel* model) {
		Finalize();
		if (model == nullptr) {
			return false;
		}
		this->drawModel = model;
		return true;
	}
	void MeshObject::Finalize() {
		if (this->drawModel != nullptr) {
			delete this->drawModel;
			this->drawModel = nullptr;
		}
	}

	void MeshObject::SetBoneAnimation(const std::string& animationName, bool playOnce, bool isLoop, int interpolationFrames) {
		this->drawModel->SetAnimation(animationName, playOnce, isLoop, interpolationFrames);
	}
	void MeshObject::SetSpeed(float speed) {
		this->drawModel->SetSpeed(speed);
	}

	void MeshObject::UpdateAnimation() {
		this->drawModel->UpdateAnimation();
	}

	void MeshObject::Draw(CameraClass* camera, ShaderClass* shader, const K_Math::Vector3& position, const K_Math::Vector3& rotation, const K_Math::Vector3& scale) {
		SetMatrix(camera, shader, position, rotation, scale);
		this->drawModel->Draw(shader);
	}
	void MeshObject::InstanceDraw(CameraClass* camera, ShaderClass* shader, int numDraw, const K_Math::Vector3& position, const K_Math::Vector3& rotation, const K_Math::Vector3& scale) {
		SetMatrix(camera, shader, position, rotation, scale);
		this->drawModel->InstanceDraw(numDraw, shader);
	}

	K_Math::Matrix4x4 MeshObject::CreateWorldMatrix(const K_Math::Vector3& position, const K_Math::Vector3& rotation, const K_Math::Vector3& scaling) {
		//移動
		K_Math::Translation trans = K_Math::Translation(position);
		//回転順はYXZ
		K_Math::Quaternion rot;
		rot = K_Math::AngleAxis(0, K_Math::Vector3::Zero());
		rot = rot * K_Math::AngleAxis(rotation.y(), K_Math::Vector3::UnitY());
		rot = rot * K_Math::AngleAxis(rotation.x(), K_Math::Vector3::UnitX());
		rot = rot * K_Math::AngleAxis(rotation.z(), K_Math::Vector3::UnitZ());
		//スケール
		K_Math::DiagonalMatrix scale = K_Math::DiagonalMatrix(K_Math::Vector3(-scaling.x(), scaling.y(), scaling.z()));

		K_Math::Affine3 world = trans * rot * scale;
		return world.matrix();
	}


	////////
	//protected
	////

	void MeshObject::SetMatrix(CameraClass* camera, ShaderClass* shader, const K_Math::Vector3& position, const K_Math::Vector3& rotation, const K_Math::Vector3& scaling) {

		K_Math::Matrix4x4 view = camera->GetViewMatrix();
		K_Math::Matrix4x4 projection = camera->GetProjectionMatrix();

		K_Math::Matrix4x4& world = CreateWorldMatrix(position, rotation, scaling);
		shader->SetMatrix(projection * view * world);
		shader->SetWorldMatrix(world.matrix());
	}

}
