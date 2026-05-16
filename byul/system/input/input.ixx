// Copyright (c) 2026 snooy. All rights reserved.

export module Input;

import std;
import Core;

export namespace byul {
enum class InputEvent {
	kPressed,
	kReleased,
	kDoubleClick,
	kHold,
	kDrag
};

enum class InputKey {
	kKeyBoard,
	kMouse
};

class IInput {
public:
	virtual void OnPressed() = 0;
	virtual void OnReleased() = 0;
	virtual void OnHold() = 0;
	virtual void OnDrag(Vector2D value) = 0;
};

class Input {
public:
	void ProcessInput(InputEvent event, Vector2D value = {});

private:
	std::vector<IInput*> m_listeners;

};
}	// namespace byul