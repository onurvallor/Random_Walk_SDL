#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>
#include <string>

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

bool init();

bool loadMedia();

void close();

SDL_Window *gWindow{nullptr};

// SDL_Surface *gScreenSurface{nullptr};

// SDL_Surface *gHelloWorld{nullptr};

SDL_Renderer *gRenderer{nullptr};

bool init() {
  bool success{true};

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    success = false;
  } else {
    if (gWindow =
            SDL_CreateWindow("SDL3 Tutorial", kScreenWidth, kScreenHeight, 0);
        gWindow == nullptr) {
      SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
      success = false;
      //} else {
      // gScreenSurface = SDL_GetWindowSurface(gWindow);
      // gRenderer = SDL_GetRenderer(gWindow);
    }
    if (gRenderer = SDL_CreateRenderer(gWindow, nullptr);
        gRenderer == nullptr) {
      SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_GetRenderer(gWindow);
    }
  }
  return success;
}

void close() {

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;

  SDL_Quit();
}

int main() {
  int exitCode{0};

  if (init() == false) {
    SDL_Log("Unable to initialize program!\n");
    exitCode = 1;
  } else {
    SDL_Event e{};
    bool isRunning{1};

    while (isRunning) {
      while (SDL_PollEvent(&e)) {

        if (e.key.scancode == SDL_SCANCODE_Q) {
          isRunning = 0;
        }
      }
      SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
      SDL_RenderClear(gRenderer);

      SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
      SDL_RenderLine(gRenderer, 40.0f, 40.0f, 60.0f, 85.0f);

      SDL_RenderPresent(gRenderer);
    }
  }

  close();

  return exitCode;
}
