#include"ModelData.h"

namespace K_Graphics {
	////////
	//public
	////

	ModelDatas::ModelDatas() {
		this->vertexBuffer = nullptr;
		this->material = nullptr;
		this->bone = nullptr;
		this->animation = nullptr;
	}
	ModelDatas::~ModelDatas() {
		if (this->vertexBuffer != nullptr) {
			delete this->vertexBuffer;
		}
		if (this->material != nullptr) {
			delete this->material;
		}
		if (this->bone != nullptr) {
			delete this->bone;
		}
		if (this->animation != nullptr) {
			delete this->animation;
		}
	}
}
