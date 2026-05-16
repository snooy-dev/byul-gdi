// Copyright (c) 2026 snooy. All rights reserved.

module Input;

namespace byul {
void Input::ProcessInput(InputEvent event, Vector2D value)
{
	for (auto listener : m_listeners) {
		switch (event) {
			case InputEvent::kPressed: {
				listener->OnPressed();
				break;
			}
			case InputEvent::kReleased: {
				listener->OnReleased();
				break;
			}
			case InputEvent::kDoubleClick: {
				break;
			}
			case InputEvent::kHold: {
				listener->OnHold();
				break;
			}
			case InputEvent::kDrag: {
				listener->OnDrag(value);
				break;
			}
		}
	}
}
}	// namespace byul