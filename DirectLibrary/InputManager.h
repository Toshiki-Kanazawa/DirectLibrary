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

	static bool prevState[(int)KeyType::_MAX];	//前回の状態
	static bool keyState[(int)KeyType::_MAX];	//今回の状態

	//キーの状態を更新する
	static void Update();

	//キーが押されているか取得する
	static bool On(KeyType keyType);

	//キーが押された瞬間を取得する
	static bool Trg(KeyType keyType);

	//キーが離された瞬間を取得する
	static bool Rel(KeyType keyType);
};