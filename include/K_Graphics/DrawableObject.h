#pragma once
#include<unordered_map>
#include"SceneRenderer.h"

namespace K_Graphics {
	//描画オブジェクトを指す、3Dの描画基底クラス
	//MeshObjectに対して、こっちは描画の詳細情報が追加されている
	class DrawableObject {
	public:
		//コピー禁止
		DrawableObject(const DrawableObject&) = delete;
		void operator = (const DrawableObject&) = delete;

		DrawableObject();
		virtual ~DrawableObject();


		//独自の描画処理を継承で持つ、主に描画パス側が使う
		virtual void Draw() = 0;

		//描画パスの登録を全て消す
		virtual void RemoveDrawPassAll() final;
		//指定のIDの描画パスから外れる
		virtual void RemoveDrawPass(int passID) final;
		//指定した描画パスへ自分を描画するように登録
		virtual void AttachDrawPass(int passID) final;

		virtual void SetDrawPassManager(DrawPassManager* passManager) final;

		//描画パスを描画前にセットしておく
		virtual void SetCurrentDrawPass(DrawPass* currentPass) final;
		virtual DrawPass* GetCurrentDrawPass() final;

	private:
		//関数を呼び出す前に呼び出し元がわかるように登録させる
		DrawPass* currentPass;

		//パスへのアクセス
		DrawPassManager* passManager;
		//登録されている描画パスから与えられたIDを指す、登録解除は主にこれでアクセスする
		std::unordered_map<int, int> passList;
	};
}