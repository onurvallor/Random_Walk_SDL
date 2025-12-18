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
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

constexpr int halfScreenWidth = kScreenWidth / 2;
constexpr int halfScreenHeight = kScreenHeight / 2;

constexpr int kNumberOfWalks{150};

bool init();

bool loadMedia();

void close();

SDL_Window *gWindow{nullptr};

SDL_Renderer *gRenderer{nullptr};

struct WalkStruct {
  std::vector<std::pair<float, float>> points = {
      std::make_pair(::halfScreenWidth, ::halfScreenHeight)};

  float cx = points.at(0).first;
  float cy = points.at(0).second;

  const float radius = 25.0f;
  float theta{};

  float x{};
  float y{};
  WalkStruct() {
    points.reserve(kNumberOfWalks + 1); // make space to avoid extra
                                        // allocations.
    points.emplace_back(halfScreenWidth, halfScreenHeight);
  }
};

struct ColorStruct {
  int r{};
  int g{};
  int b{};
  int a{255}; // fully visible by default
};

void drawLines(WalkStruct &walk, ColorStruct &color);

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

    WalkStruct walk{};
    WalkStruct walkTwo{};

    ColorStruct blue{0, 0, 255, 255};
    ColorStruct red{255, 0, 0, 255};

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    while (isRunning) {
      while (SDL_PollEvent(&e)) {

        if (e.key.scancode == SDL_SCANCODE_Q) {
          isRunning = 0;
        }
      }

      SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
      SDL_RenderClear(gRenderer);

      drawLines(walk, blue);
      drawLines(walkTwo, red);

      SDL_RenderPresent(gRenderer);
    }
  }

  close();

  return exitCode;
}

void drawLines(WalkStruct &walk, ColorStruct &color) {
  SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
  int i{0};

  for (i = 0; i < kNumberOfWalks; i++) {
    std::pair<float, float> current_pair = walk.points.back();

    walk.theta = static_cast<float>(std::rand()) / RAND_MAX * (2.0f * M_PI);
    walk.x = current_pair.first + walk.radius * std::cos(walk.theta);
    walk.y = current_pair.second + walk.radius * std::sin(walk.theta);

    walk.x = std::clamp(walk.x, 0.0f, static_cast<float>(kScreenWidth));
    walk.y = std::clamp(walk.y, 0.0f, static_cast<float>(kScreenHeight));

    SDL_RenderLine(gRenderer, current_pair.first, current_pair.second, walk.x,
                   walk.y);
    walk.points.emplace_back(std::make_pair(walk.x, walk.y));

    SDL_Delay(10);
  }
}
