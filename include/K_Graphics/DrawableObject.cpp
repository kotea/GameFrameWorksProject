#include"DrawableObject.h"
#include"SceneRenderer.h"

namespace K_Graphics {

	//値として描画パスの管理クラスが必須になる、SetDrawPassManager()でセットしなくてはならない
	DrawableObject::DrawableObject() {
		this->passManager = nullptr;
	}

	DrawableObject::~DrawableObject(){
		RemoveDrawPassAll();
	}

	void DrawableObject::RemoveDrawPass(int drawPassID) {
		//一度も登録されていないと、描画パス管理クラスがnullになっている
		if (this->passManager == nullptr) {
			throw new std::runtime_error("nobody attach DrawPass : RemoveDrawPass()");
		}

		this->passManager->RemoveDrawableObject(drawPassID, this->passList[drawPassID]);
		this->passList.erase(drawPassID);
	}



	void DrawableObject::RemoveDrawPassAll() {
		//一度も登録されていないと、描画パス管理クラスがnullになっている
		if (this->passManager == nullptr) {
			throw new std::runtime_error("nobody attach DrawPass : RemoveDrawPassAll()");
		}

		//全ての描画パスへの登録を解除
		int count = 0;
		for (auto id : this->passList) {
			this->passManager->RemoveDrawableObject(id.first, id.second);
		}
		this->passList.clear();
	}

	void DrawableObject::AttachDrawPass(int passID) {
		//一度も登録されていないと、描画パス管理クラスがnullになっている
		if (this->passManager == nullptr) {
			throw new std::runtime_error("nobody attach DrawPass : AttachDrawPass()");
		}

		//重複チェック
		if (this->passList.find(passID) != this->passList.end()) {
			return;
		}

		//登録
		int objId = this->passManager->JoinDrawableObject(passID, this);
		this->passList[passID] = objId;
	}

	void DrawableObject::SetDrawPassManager(DrawPassManager * passManager){
		//多重登録の禁止
		if (this->passManager != nullptr) {
			throw new std::runtime_error("already set DrawPassManager: SetDrawPassManager()");
		}
		this->passManager = passManager;
	}

	//描画前の情報登録
	void DrawableObject::SetCurrentDrawPass(DrawPass * currentPass){
		this->currentPass = currentPass;
	}
	DrawPass * DrawableObject::GetCurrentDrawPass()
	{
		return this->currentPass;
	}
}