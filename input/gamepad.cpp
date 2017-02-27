#include <iostream>
#include "gamepad.h"

void GamepadButton::addDownHandler(ButtonCommand &down) {
    downHandler = &down;
}

void GamepadButton::addUpHandler(ButtonCommand &up) {
    upHandler = &up;
}

void GamepadButton::removeDownHandler() {
    downHandler = &empty;
}

void GamepadButton::removeUpHandler() {
    upHandler = &empty;
}

void GamepadButton::notifyDownHandlers() {
    downHandler->buttonAction();
}

void GamepadButton::notifyUpHandlers() {
    upHandler->buttonAction();
}

GamepadButton::GamepadButton() : downHandler{&empty}, upHandler{&empty} {

}

ButtonCommandLambda::ButtonCommandLambda(std::unique_ptr<std::function<void()>> &&handler) : actionHandler{std::move(handler)} {

}

void ButtonCommandLambda::buttonAction() {
    (*actionHandler)();
}

