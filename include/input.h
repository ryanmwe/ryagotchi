// input.h
#ifndef INPUT_H
#define INPUT_H

enum class InputType {
    ButtonPress,
    Touch,
    // Add other input types as needed
};

struct Input {
    InputType type;
    int value; // Can represent different things: button ID, touch coordinates, etc.

    Input(InputType type, int value) : type(type), value(value) {}
};

#endif
