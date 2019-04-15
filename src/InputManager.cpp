#include <InputManager.h>
#include <Util.h>

InputManager& InputManager::GetInstance() {
    static InputManager instance;

    return instance;
}

InputManager::InputManager() : mouseState { 0, 0, 0, 0, 0, 0 }, mouseUpdate { 0, 0, 0, 0, 0, 0} {
    this->quitRequested = false;
    this->updateCounter = 0;
    this->mouseX = 0;
    this->mouseY = 0;
}

InputManager::~InputManager() {}

void InputManager::Update() {
    Setup();
    GetMouse();

    SDL_Event event;
    // TODO: discover if it should be if or while
    while (SDL_PollEvent(&event)) {
        TreatEvent(event);
    }
}

void InputManager::Setup() {
    this->quitRequested = false;
    this->updateCounter++;
}

void InputManager::GetMouse() {
    SDL_GetMouseState(&this->mouseX, &this->mouseY);
}

void InputManager::TreatEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT: {
            this->quitRequested = true;
            break;
        }
        case SDL_KEYDOWN: {
            auto isRepeated = event.key.repeat == 1;

            if (isRepeated) {
                auto key = event.key.keysym.sym;

                this->keyState[key] = true;
                this->keyUpdate[key] = this->updateCounter;
            }
            break;
        }
        case SDL_KEYUP: {
            auto isRepeated = event.key.repeat == 1;

            if (isRepeated) {
                auto key = event.key.keysym.sym;

                this->keyState[key] = false;
                this->keyUpdate[key] = this->updateCounter;
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            auto idx = event.button.button;
            this->mouseState[idx] = true;
            this->mouseUpdate[idx] = this->updateCounter;
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            auto idx = event.button.button;
            this->mouseState[idx] = false;
            this->mouseUpdate[idx] = this->updateCounter;
            break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return this->keyState[key];
}

bool InputManager::MousePress(int button) {
    return this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::MouseRelease(int button) {
    return !this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return this->mouseState[button];
}

int InputManager::GetMouseX() {
    return this->mouseX;
}

int InputManager::GetMouseY() {
    return this->mouseY;
}

bool InputManager::QuitRequested () {
    return this->quitRequested;
}
