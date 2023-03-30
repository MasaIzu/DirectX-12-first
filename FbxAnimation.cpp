#include "FbxAnimation.h"
#include <cassert>

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
const std::string FbxAnimation::baseDirectory = "Resources/";
const std::string FbxAnimation::defaultTextureFileName = "white1x1.png";

void FbxAnimation::Load(const std::string& failPath)
{

	// ���f���Ɠ������O�̃t�H���_����ǂݍ���
	const std::string directoryPath = baseDirectory + failPath + "/";
	// �g���q.fbx��t��
	const std::string fileName = failPath + ".fbx";
	// �A�����ăt���p�X�𓾂�
	const std::string fullpath = directoryPath + fileName;

	mScene = aiImportFile(fullpath.c_str(), flag);

	// �t�@�C�������w�肵��FBX�t�@�C����ǂݍ���
	if (!mScene) {
		assert(0);
	}

	modelAnimation = mScene->mAnimations[0];

}

aiAnimation* FbxAnimation::GetAnimation()
{

	return modelAnimation;
}
