#include"MyMathFanctions.h"

float K_Math::DegToRad(float deg) {
	return deg * (float)M_PI / 180.0f;
}
float K_Math::RadToDeg(float rad) {
	return rad * 180.0f / (float)M_PI;
}

void K_Math::MatrixPerspectiveLH(K_Math::Matrix4x4& result, float screenWidth, float screenHeight, float screenNear, float screenFar, float fieldOfView) {
	K_Math::Matrix4x4 mat;
	mat[0][0] = screenHeight / (screenWidth * tanf(fieldOfView * 0.5f));
	mat[0][1] = 0.0f;
	mat[0][2] = 0.0f;
	mat[0][3] = 0.0f;

	mat[1][0] = 0.0f;
	mat[1][1] = 1.0f / tanf(fieldOfView * 0.5f);
	mat[1][2] = 0.0f;
	mat[1][3] = 0.0f;

	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f;
	mat[2][2] = screenFar / (screenFar - screenNear);
	mat[2][3] = 1.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = screenFar * -screenNear / (screenFar - screenNear);
	mat[3][3] = 0.0f;
	result = mat;
}

void K_Math::MatrixPerspectiveRH(K_Math::Matrix4x4& result, float screenWidth, float screenHeight, float screenNear, float screenFar, float fieldOfView) {

}
void K_Math::MatrixOrthoLH(K_Math::Matrix4x4& result, float screenWidth, float screenHeight, float screenNear, float screenFar) {
	K_Math::Matrix4x4 mat;
	mat[0][0] = 2.0f / screenWidth;
	mat[0][1] = 0.0f;
	mat[0][2] = 0.0f;
	mat[0][3] = 0.0f;

	mat[1][0] = 0.0f;
	mat[1][1] = 2.0f / screenHeight;
	mat[1][2] = 0.0f;
	mat[1][3] = 0.0f;

	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f;
	mat[2][2] = 2.0f / (screenFar - screenNear);
	mat[2][3] = 0.0f;

	mat[3][3] = 0.0f;
	mat[3][3] = 0.0f;
	mat[3][3] = -(screenNear) / (screenFar - screenNear);
	mat[3][3] = 1.0f;

	result = mat;
}
void K_Math::MatrixOrthoRH(K_Math::Matrix4x4& result, float screenWidth, float screenHeight, float screenNear, float screenFar) {

}
void K_Math::MatrixLookAt(K_Math::Matrix4x4& result, K_Math::Vector3& position, K_Math::Vector3& lookAt, K_Math::Vector3& up) {
	K_Math::Vector3 zAxis, xAxis, yAxis;

	// zAxis = normal(lookAt - position)
	zAxis.x = lookAt.x - position.x;
	zAxis.y = lookAt.y - position.y;
	zAxis.z = lookAt.z - position.z;
	zAxis = glm::normalize(zAxis);

	// xAxis = normal(cross(up, zAxis))
	xAxis.x = (up.y * zAxis.z) - (up.z * zAxis.y);
	xAxis.y = (up.z * zAxis.x) - (up.x * zAxis.z);
	xAxis.z = (up.x * zAxis.y) - (up.y * zAxis.x);
	xAxis = glm::normalize(xAxis);

	// yAxis = cross(zAxis, xAxis)
	yAxis.x = (zAxis.y * xAxis.z) - (zAxis.z * xAxis.y);
	yAxis.y = (zAxis.z * xAxis.x) - (zAxis.x * xAxis.z);
	yAxis.z = (zAxis.x * xAxis.y) - (zAxis.y * xAxis.x);

	float result1, result2, result3;
	// -dot(xAxis, position)
	result1 = ((xAxis.x * position.x) + (xAxis.y * position.y) + (xAxis.z * position.z)) * -1.0f;
	// -dot(yaxis, eye)
	result2 = ((yAxis.x * position.x) + (yAxis.y * position.y) + (yAxis.z * position.z)) * -1.0f;
	// -dot(zaxis, eye)
	result3 = ((zAxis.x * position.x) + (zAxis.y * position.y) + (zAxis.z * position.z)) * -1.0f;

	// ビュー行列を作成
	K_Math::Matrix4x4 mat;
	mat[0][0] = xAxis.x;
	mat[1][0] = xAxis.y;
	mat[2][0] = xAxis.z;
	mat[3][0] = result1;

	mat[0][1] = yAxis.x;
	mat[1][1] = yAxis.y;
	mat[2][1] = yAxis.z;
	mat[3][1] = result2;

	mat[0][2] = zAxis.x;
	mat[1][2] = zAxis.y;
	mat[2][2] = zAxis.z;
	mat[3][2] = result3;

	mat[0][3] = 0.0f;
	mat[1][3] = 0.0f;
	mat[2][3] = 0.0f;
	mat[3][3] = 1.0f;

	result = mat;
}

void K_Math::CreateWorldMatrix(K_Math::Matrix4x4& out, const K_Math::Vector3& position, const K_Math::Vector3& rotation, const K_Math::Vector3& scaling) {
	//移動
	K_Math::Matrix4x4 transMat = glm::translate(out, position);
	//回転順はYXZ
	K_Math::Quaternion rot;
	rot = glm::angleAxis(0.0f, K_Math::Vector3(0.0f, 0.0f, 0.0f));
	rot = rot * glm::angleAxis(rotation.y, K_Math::Vector3(0.0f, 1.0f, 0.0f));
	rot = rot * glm::angleAxis(rotation.x, K_Math::Vector3(1.0f, 0.0f, 0.0f));
	rot = rot * glm::angleAxis(rotation.z, K_Math::Vector3(0.0f, 0.0f, 1.0f));
	K_Math::Matrix4x4 rotMat = glm::toMat4(rot);

	//スケール
	K_Math::Matrix4x4 scaleMat = glm::scale(out, K_Math::Vector3(scaling.x, scaling.y, scaling.z));

	out = transMat * rotMat * scaleMat;
}
void K_Math::CreateWorldMatrix(K_Math::Matrix4x4& out, const K_Math::Vector3& position, const K_Math::Quaternion& rotation, const K_Math::Vector3& scaling) {
	//移動
	//クォータニオンによる回転
	//スケール
	out = glm::translate(out, position) * glm::toMat4(rotation) *  glm::scale(out, scaling);
}


//平行移動前オフセット付き
void K_Math::CreateWorldMatrix(K_Math::Matrix4x4 & out,
	const K_Math::Vector3 & offset,
	const K_Math::Vector3 & position, const K_Math::Quaternion & rotation, const K_Math::Vector3 & scaling) {
	//行列作成
	CreateWorldMatrix(out, position, rotation, scaling);
	//平行移動する場合は平行移動を追加
	if (K_Math::Norm(offset) > 0.0f) {
		out = out * glm::translate(K_Math::Matrix4x4(), offset);
	}
}

//ビルボード機能と平行移動前オフセット付き
void K_Math::CreateWorldMatrix(K_Math::Matrix4x4 & out,
	const K_Math::Matrix4x4 & viewMat,
	const K_Math::Vector3 & offset,
	const K_Math::Vector3 & position, const K_Math::Quaternion & rotation, const K_Math::Vector3 & scaling) {
	//カメラ行列をコピー
	K_Math::Matrix4x4 cameraMat = viewMat;
	//平行移動打ち消し
	cameraMat[3][0] = 0.0f;
	cameraMat[3][1] = 0.0f;
	cameraMat[3][2] = 0.0f;

	//カメラに向く回転を加えて行列作成
	out = glm::translate(out, position) * cameraMat * glm::toMat4(rotation) *  glm::scale(out, scaling);

	//平行移動する場合は平行移動を追加
	if (K_Math::Norm(offset) > 0.0f) {
		out = out * glm::translate(K_Math::Matrix4x4(), offset);
	}
}


K_Math::Box2D::Box2D() : x(0), y(0), w(0), h(0) {
}
K_Math::Box2D::Box2D(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
}
K_Math::Box2D& K_Math::Box2D::operator =(const Box2D& box) {
	this->x = box.x; this->y = box.y; this->w = box.w; this->h = box.h; return *this;
}
void K_Math::Box2D::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}
void K_Math::Box2D::SetWH(int w, int h) {
	this->w = w;
	this->h = h;
}
void K_Math::Box2D::Offset(int addX, int addY) {
	this->x += addX;
	this->y += addY;
}

//!@brief 回転成分からクォータニオンを作成する(Y軸→X軸→Z軸)
K_Math::Quaternion K_Math::RotationToQuaternion(const K_Math::Vector3& rotation) {
	//回転順はYXZ
	K_Math::Quaternion rot;
	rot = rot * glm::angleAxis(rotation.y, K_Math::Vector3(0.0f, 1.0f, 0.0f));
	rot = rot * glm::angleAxis(rotation.x, K_Math::Vector3(1.0f, 0.0f, 0.0f));
	rot = rot * glm::angleAxis(rotation.z, K_Math::Vector3(0.0f, 0.0f, 1.0f));
	return rot;
}
//!@brief クォータニオンから回転成分を作成する(Y軸→X軸→Z軸)
K_Math::Vector3 K_Math::QuaternionToRotation(const K_Math::Quaternion& quaternion) {
	K_Math::Vector3 rot = glm::eulerAngles(quaternion);
	return rot;
}

void K_Math::PickUp(const Vector4& vector, Vector4& result, bool xPickUp, bool yPickUp, bool zPickUp, bool wPickUp) {
	result.x = xPickUp ? vector.x : 0.0f;
	result.y = yPickUp ? vector.y : 0.0f;
	result.z = zPickUp ? vector.z : 0.0f;
	result.w = wPickUp ? vector.w : 0.0f;
}

void K_Math::PickUp(const Vector3& vector, Vector3& result, bool xPickUp, bool yPickUp, bool zPickUp) {
	result.x = xPickUp ? vector.x : 0.0f;
	result.y = yPickUp ? vector.y : 0.0f;
	result.z = zPickUp ? vector.z : 0.0f;
}

void K_Math::PickUp(const Vector2& vector, Vector2& result, bool xPickUp, bool yPickUp) {
	result.x = xPickUp ? vector.x : 0.0f;
	result.y = yPickUp ? vector.y : 0.0f;
}

void K_Math::Normalize(Vector2& vector) {
	vector = glm::normalize(vector);
}
void K_Math::Normalize(Vector3& vector) {
	vector = glm::normalize(vector);
}

K_Math::Vector2 K_Math::Normalized(const Vector2& vector) {
	if (K_Math::Norm(vector) < 0.001f) {
		return K_Math::Vector2(0.0f, 0.0f);
	}
	return glm::normalize(vector);
}
K_Math::Vector3 K_Math::Normalized(const Vector3& vector) {
	if (K_Math::Norm(vector) < 0.001f) {
		return K_Math::Vector3(0.0f, 0.0f, 0.0f);
	}
	return glm::normalize(vector);
}

float K_Math::Norm(const K_Math::Vector2& vector) {
	return glm::length(vector);
}
float K_Math::Norm(const K_Math::Vector3& vector) {
	return glm::length(vector);
}
float K_Math::Norm(const K_Math::Vector4& vector) {
	return glm::length(vector);
}

float K_Math::Cross(const K_Math::Vector2& vector1, const K_Math::Vector2& vector2) {
	return (vector1.x * vector2.y - vector1.y * vector2.x);
}
K_Math::Vector3 K_Math::Cross(const K_Math::Vector3& vector1, const K_Math::Vector3& vector2) {
	return glm::cross(vector1, vector2);
}

float K_Math::Dot(const K_Math::Vector2& vector1, const K_Math::Vector2& vector2) {
	return glm::dot(vector1, vector2);
}
float K_Math::Dot(const K_Math::Vector3& vector1, const K_Math::Vector3& vector2) {
	return glm::dot(vector1, vector2);
}

K_Math::Quaternion K_Math::Slerp(const Quaternion& from, const Quaternion& to, float t) {
	return glm::slerp(from, to, t);
}

K_Math::Quaternion K_Math::AngleAxis(float angle, const Vector3& axis) {
	return glm::angleAxis(angle, axis);
}
K_Math::Quaternion K_Math::LookAt(const Vector3& vec1, const Vector3& vec2) {
	return glm::rotation(vec1, vec2);
}

float K_Math::Angle(const Vector3& vec1, const Vector3& vec2) {
	return glm::angle(vec1, vec2);
}
float K_Math::Angle(const Vector3& vec1, const Vector3& vec2, const Vector3& ref) {
	return glm::orientedAngle(vec1, vec2, ref);
}

