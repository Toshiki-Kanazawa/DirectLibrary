#pragma once

enum class KeyType
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Left,
	Right,
	Up,
	Down,
	Enter,
	Space,
	Escape,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	_0,
	Shift,
	Alt,
	Ctrl,

	_MAX,
};

class InputManager
{
public:

	static bool prevState[(int)KeyType::_MAX];	//�O��̏��
	static bool keyState[(int)KeyType::_MAX];	//����̏��

	//�L�[�̏�Ԃ��X�V����
	static void Update();

	//�L�[��������Ă��邩�擾����
	static bool On(KeyType keyType);

	//�L�[�������ꂽ�u�Ԃ��擾����
	static bool Trg(KeyType keyType);

	//�L�[�������ꂽ�u�Ԃ��擾����
	static bool Rel(KeyType keyType);
};