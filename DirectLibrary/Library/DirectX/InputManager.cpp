#include "InputManager.h"

#include <windows.h>
#pragma comment(lib,"winmm.lib")

bool InputManager::prevState[] = {};
bool InputManager::keyState[] = {};

int KeyTypeToVirtualKeyCode(KeyType keyType)
{
	switch (keyType)
	{
	case KeyType::A: return 0x41;
	case KeyType::B: return 0x42;
	case KeyType::C: return 0x43;
	case KeyType::D: return 0x44;
	case KeyType::E: return 0x45;
	case KeyType::F: return 0x46;
	case KeyType::G: return 0x47;
	case KeyType::H: return 0x48;
	case KeyType::I: return 0x49;
	case KeyType::J: return 0x4A;
	case KeyType::K: return 0x4B;
	case KeyType::L: return 0x4C;
	case KeyType::M: return 0x4D;
	case KeyType::N: return 0x4E;
	case KeyType::O: return 0x4F;
	case KeyType::P: return 0x50;
	case KeyType::Q: return 0x51;
	case KeyType::R: return 0x52;
	case KeyType::S: return 0x53;
	case KeyType::T: return 0x54;
	case KeyType::U: return 0x55;
	case KeyType::V: return 0x56;
	case KeyType::W: return 0x57;
	case KeyType::X: return 0x58;
	case KeyType::Y: return 0x59;
	case KeyType::Z: return 0x5A;
	case KeyType::Left: return VK_LEFT;
	case KeyType::Right: return VK_RIGHT;
	case KeyType::Up: return VK_UP;
	case KeyType::Down: return VK_DOWN;
	case KeyType::Enter: return VK_RETURN;
	case KeyType::Space: return VK_SPACE;
	case KeyType::Escape: return VK_ESCAPE;
	case KeyType::_0: return 0x30;
	case KeyType::_1: return 0x31;
	case KeyType::_2: return 0x32;
	case KeyType::_3: return 0x33;
	case KeyType::_4: return 0x34;
	case KeyType::_5: return 0x35;
	case KeyType::_6: return 0x36;
	case KeyType::_7: return 0x37;
	case KeyType::_8: return 0x38;
	case KeyType::_9: return 0x39;
	case KeyType::Shift: return VK_LSHIFT;
	case KeyType::Alt: return VK_MENU;
	case KeyType::Ctrl: return VK_CONTROL;
	default: return 0;
	}

	return 0;
}

void InputManager::Update()
{
	//ÉLÅ[ÇÃèÛë‘ÇëOâÒÇÃèÛë‘Ç÷ê›íËÇ∑ÇÈ
	for (int i = 0; i <(int)KeyType::_MAX; ++i)
	{
		prevState[i] = keyState[i];
	}

	//ç°âÒÇÃèÛë‘ÇéÊìæÇ∑ÇÈ
	for (int i = 0; i < (int)KeyType::_MAX; ++i)
	{
		int keycode = KeyTypeToVirtualKeyCode((KeyType)i);
		auto test = GetAsyncKeyState(keycode);
		keyState[i] = test != 0;
	}

}


bool InputManager::On(KeyType keyType)
{
	return keyState[(int)keyType];
}

bool InputManager::Trg(KeyType keyType)
{
	return !prevState[(int)keyType] && keyState[(int)keyType];
}

bool InputManager::Rel(KeyType keyType)
{
	return prevState[(int)keyType] && !keyState[(int)keyType];
}
