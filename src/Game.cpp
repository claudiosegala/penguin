#include <SDL_Include.h>
#include <Resources.h>
#include <InputManager.h>
#include <Game.h>
#include <Logger.h>
#include <iostream>

Game* Game::instance;

Game::Game(const std::string &title, int width, int height) {
    if (this->instance != nullptr) {
        throw std::runtime_error("There should be only one instance!");
    }

    this->instance = this;

    Init_SDL();
    Init_IMG();
    Init_MIX();
    Init_WDW(title, width, height);
    Init_RDR();
    Init_STS();

    Logger::Info("Created the game instance");
}

Game::~Game() {
    delete this->state;

    Resources::ClearImages();

    Resources::ClearMusics();
    
    Resources::ClearSounds();

    Logger::Info("Destroying Renderer");
    SDL_DestroyRenderer(this->renderer);
    
    Logger::Info("Destroying Window");
    SDL_DestroyWindow(this->window);
    
    Logger::Info("Quiting SDL Mix Audio");
    Mix_CloseAudio();
    
    Logger::Info("Quiting SDL Mixer");
    while(Mix_Init(0)) Mix_Quit(); // That is the only way to make sure of quitting accordingly to documentation
    
    Logger::Info("Quiting SDL Image");
    IMG_Quit();
    
    Logger::Info("Quiting SDL");
    SDL_Quit();
}

void Game::Run() {
    Logger::Info("Started Game");

    auto& in = InputManager::GetInstance();

    while(!this->state->QuitRequested()) {
        in.Update();

        this->state->Update(1.0);
        this->state->Render();

        SDL_RenderPresent(this->renderer);
        SDL_Delay(33);
    }

    Logger::Info("Ended Game");
}

Game* Game::GetInstance () {
    if (Game::instance != nullptr) {
        return Game::instance;
    }
    
    return Game::instance = new Game("ClaudioSegala_150032552", 1024, 600);
}

State* Game::GetState () {
    return this->state;
}

SDL_Renderer* Game::GetRenderer () {
    return this->renderer;
}

void Game::Init_STS () {
    this->state = new State();
}

void Game::Init_RDR () {
    auto index = -1; // SDL will choose the best for us

    /*
        Available flags:
        SDL_RENDERER_SOFTWARE
        SDL_RENDERER_PRESENTVSYNC
        SDL_RENDERER_ACCELERATED
        SDL_RENDERER_TARGETTEXTURE
    */
    uint32_t flags = (
        SDL_RENDERER_ACCELERATED
    );
    
    Logger::Info("Creating Renderer");
    this->renderer = SDL_CreateRenderer(this->window, index, flags);

    if (this->renderer == nullptr) {
        SDL_GetNumRenderDrivers();

        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }
}

void Game::Init_WDW (const std::string &title, int width, int height) {
    auto pos = SDL_WINDOWPOS_CENTERED;
    uint32_t flags = 0;
    
    Logger::Info("Creating Window");
    this->window = SDL_CreateWindow(title.c_str(), (int) pos, (int) pos, width, height, flags);

    if (this->window == nullptr) {
        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }
}

void Game::Init_MIX () {
    /*
        Available Flags:
        MIX_INIT_FLAC
        MIX_INIT_MP3
        MIX_INIT_OGG
        MIX_INIT_MOD
        MIX_INIT_FLUIDSYNTH
        MIX_INIT_MODPLUG
    */
    auto flags = (
        MIX_INIT_OGG
    );
    
    Logger::Info("Initing Mixer");
    auto res = Mix_Init(flags);

    if (res != flags) {
        auto mix_msg = "MixError: " + std::string(Mix_GetError()) + "\n";
        auto msg = "The flag sent was " + std::to_string(flags) + ", but the result of initing mixer was " + std::to_string(res) + "\n";
        throw std::runtime_error(mix_msg + msg);
    }

    Logger::Info("Configuring Audio");
    res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    if (res < 0) {
        auto mix_msg = Mix_GetError();
        throw std::runtime_error(mix_msg);
    }
    
    Logger::Info("Allocating Channels");
    res = Mix_AllocateChannels(32);

    if (res < 0) {
        auto mix_msg = Mix_GetError();
        throw std::runtime_error(mix_msg);
    }
}

void Game::Init_IMG () {
    /*
        Available Flags:
        IMG_INIT_JPG
        IMG_INIT_PNG
        IMG_INIT_TIF
    */
    auto flags = (
        IMG_INIT_JPG |
        IMG_INIT_PNG
    );
    
    Logger::Info("Initing SDL Image");
    auto res = IMG_Init(flags);

    if (res != flags) {
        auto img_msg = "ImageError: " + std::string(IMG_GetError())  + "\n";
        auto msg = "The flag sent was " + std::to_string(flags) + ", but the result of initing image was " + std::to_string(res) + "\n";
        throw std::runtime_error(img_msg + msg);
    }
}

void Game::Init_SDL () {
    /* 
        Available Flags:
        SDL_INIT_TIMER
        SDL_INIT_GAMECONTROLLER
        SDL_INIT_AUDIO
        SDL_INIT_EVENTS
        SDL_INIT_VIDEO
        SDL_INIT_EVERYTHING
        SDL_INIT_JOYSTICK
        SDL_INIT_NOPARACHUTE
        SDL_INIT_HAPTIC
    */
    auto flags = (
        SDL_INIT_VIDEO |
        SDL_INIT_AUDIO |
        SDL_INIT_TIMER
    );
    
    Logger::Info("Initing SDL");
    auto err = SDL_Init(flags);

    if (err < 0) {
        auto sdl_msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
        throw std::runtime_error(sdl_msg);
    }
}