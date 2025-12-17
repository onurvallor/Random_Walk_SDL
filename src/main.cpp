#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
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

SDL_Surface *gScreenSurface{nullptr};

SDL_Surface *gHelloWorld{nullptr};

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
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
    if (gRenderer = SDL_CreateRenderer(gWindow, nullptr);
        gRenderer == nullptr) {
      SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
  }
  return success;
}

bool loadMedia() {
  bool success{true};

  std::string imagePath{"./snail.bmp"};

  if (gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr) {
    SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(),
            SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_DestroySurface(gHelloWorld);
  gHelloWorld = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;
  gScreenSurface = nullptr;

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
    if (loadMedia() == false) {
      SDL_Log("Unable to load media!\n");
      exitCode = 2;
    } else {
      bool quit{false};

      SDL_Event e;
      SDL_zero(e);

      while (quit == false) {
        while (SDL_PollEvent(&e) == true) {
          if (e.type == SDL_EVENT_QUIT) {
            quit = true;
          }
        }
        SDL_FillSurfaceRect(
            gScreenSurface, nullptr,
            SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

        SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

        SDL_SetRenderDrawColor(gRenderer, 0xF0, 0xF0, 0xF0, 0xFF);
        SDL_RenderLine(gRenderer, 20.0f, 20.0f, 40.0f, 70.0f);

        SDL_UpdateWindowSurface(gWindow);
      }
    }
    close();

    return exitCode;
  }

  return 0;
}
