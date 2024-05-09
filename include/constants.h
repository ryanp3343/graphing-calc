#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace TokenTypes {
    // Token types
    constexpr int Integer = 1;
    constexpr int Function = 2;
    constexpr int Operator = 3;
    constexpr int Variable = 4;
    constexpr int Token = 5;
}

namespace Precedence {
    // Operator precedence values
    constexpr int Subtract = 1;
    constexpr int Add = 1;
    constexpr int Divide = 2;
    constexpr int Multiply = 2;
    constexpr int Exponent = 3;
    constexpr int TrigFunction = 4;
}

namespace Commands {
    // Commands for event processing
    constexpr int GoRight = 6;
    constexpr int GoLeft = 7;
    constexpr int GoUp = 8;
    constexpr int GoDown = 9;
    constexpr int ZoomIn = 10;
    constexpr int ZoomOut = 11;
    constexpr int Reset = 12;
    constexpr int New = 13;
    constexpr int Delete = 14;
    constexpr int IDK = 15; // Should be replaced with a meaningful name
    constexpr int IDK2 = 16; // Should be replaced with a meaningful name
}

namespace SFMLWindow {
    // Window properties
    constexpr int ScreenWidth = 2400;
    constexpr int ScreenHeight = 1350;
    constexpr float GraphPanel = (ScreenWidth * 2.8f / 5) + 700;
    constexpr float SideBar = ScreenWidth * 2.2f / 5;
}

#endif // CONSTANTS_H
