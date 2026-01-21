#pragma once

class Input {

private:

    // Specify which Keys are pressed or lifted
    char m_keyUp;
    char m_keyDown;

    // Specify if a Keys is pressed
    bool m_isKeyPressed;
    bool m_isXClicked;

    bool m_isLeftButtonClicked;
    bool m_isRightButtonClicked;
    bool m_isMiddleButtonClicked;

    int m_mouseMotionX;
    int m_mouseMotionY;

    int m_mousePositionX;
    int m_mousePositionY;

private:

    Input();
    Input(const Input&);
    Input& operator=(Input&);


public:

    static Input* Instance();

public:

    bool IsXClicked();
    bool IsKeyPressed();

    char GetKeyUp();
    char GetKeyDown();

    bool IsLeftButtonClicked();
    bool IsRightButtonClicked();
    bool IsMiddleButtonClicked();

    int GetMousePositionX();
    int GetMousePositionY();

    int GetMouseMotionX();
    int GetMouseMotionY();

public:

    void Update();


};