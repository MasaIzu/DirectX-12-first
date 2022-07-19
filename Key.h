#pragma once
#include <dinput.h>
#include <cassert>


class Key {
public:
	void KeyInitializ(WNDCLASSEX w);
	void KeyUpdata();

	BYTE KeyGet();
private:
	//DirectInput�̏�����
	IDirectInput8* directInput = nullptr;
	//�L�[�{�[�h�f�o�C�X�̐���
	IDirectInputDevice8* keyboard = nullptr;

	// �S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256] = {};

};