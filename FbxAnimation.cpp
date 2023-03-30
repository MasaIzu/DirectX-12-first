#include "FbxAnimation.h"
#include <cassert>

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
const std::string FbxAnimation::baseDirectory = "Resources/";
const std::string FbxAnimation::defaultTextureFileName = "white1x1.png";

void FbxAnimation::Load(const std::string& failPath)
{

	// モデルと同じ名前のフォルダから読み込む
	const std::string directoryPath = baseDirectory + failPath + "/";
	// 拡張子.fbxを付加
	const std::string fileName = failPath + ".fbx";
	// 連結してフルパスを得る
	const std::string fullpath = directoryPath + fileName;

	mScene = aiImportFile(fullpath.c_str(), flag);

	// ファイル名を指定してFBXファイルを読み込む
	if (!mScene) {
		assert(0);
	}

	modelAnimation = mScene->mAnimations[0];

}

aiAnimation* FbxAnimation::GetAnimation()
{

	return modelAnimation;
}
