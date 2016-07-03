#pragma once

#include <Qt>
#include <QPoint>

//
// Idea originally by Trent Reed
// This class is based on the tutorial Qt5 OpenGL Part 3b: Camera Control
// Link: http://www.trentreed.net/blog/qt5-opengl-part-3b-camera-control/
// However no copy-paste was made and everything has been understood and is used in the project.
//

class InputManager
{
	public:

		// Possible key states
		enum InputState
		{
			InputInvalid,
			InputRegistered,
			InputUnregistered,
			InputTriggered,
			InputPressed,
			InputReleased
		};

		// State checking
		static InputState keyState(Qt::Key key);
		static bool keyTriggered(Qt::Key key);
		static bool keyPressed(Qt::Key key);
		static bool keyReleased(Qt::Key key);
		static InputState buttonState(Qt::MouseButton button);
		static bool buttonTriggered(Qt::MouseButton button);
		static bool buttonPressed(Qt::MouseButton button);
		static bool buttonReleased(Qt::MouseButton button);
		static QPoint mousePosition();
		static QPoint mouseDelta();

	private:

		// State updating
		static void update();
		static void registerKeyPress(int key);
		static void registerKeyRelease(int key);
		static void registerMousePress(Qt::MouseButton button);
		static void registerMouseRelease(Qt::MouseButton button);
		static void reset();
		friend class GLWidget;
};

inline bool InputManager::keyTriggered(Qt::Key key)
{
	return keyState(key) == InputTriggered;
}

inline bool InputManager::keyPressed(Qt::Key key)
{
	return keyState(key) == InputPressed;
}

inline bool InputManager::keyReleased(Qt::Key key)
{
	return keyState(key) == InputReleased;
}

inline bool InputManager::buttonTriggered(Qt::MouseButton button)
{
	return buttonState(button) == InputTriggered;
}

inline bool InputManager::buttonPressed(Qt::MouseButton button)
{
	return buttonState(button) == InputPressed;
}

inline bool InputManager::buttonReleased(Qt::MouseButton button)
{
	return buttonState(button) == InputReleased;
}
