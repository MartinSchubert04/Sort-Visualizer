
#include "SortVisualizer.h"

SortVisualizer::SortVisualizer(int size, int screenWidth, int screenHeight) :
    _width(screenWidth), _height(screenHeight), _size(size) {

  InitWindow(_width, _height, "Sort Visualizer");

  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  for (size_t i = 0; i < _size; i++) {
    _array.push_back(dist(rng));
  }
}

void SortVisualizer::main() {
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    SetWindowTitle(TextFormat("Sort Visualizer | FPS: %d", GetFPS()));

    _sortAlgorithm->sortStep(_array);

    BeginDrawing();

    ClearBackground(BLACK);

    if (IsKeyPressed(KEY_R)) {
      reset();
    }

    DrawText(_sortAlgorithm->sortName(), 160, 150, 20, LIGHTGRAY);
    DrawText(TextFormat("Array size: %d", _size), 160, 180, 20, LIGHTGRAY);
    DrawText(TextFormat("Time: %.3f", _sortAlgorithm->elapsed()), 160, 210, 20, LIGHTGRAY);

    drawArray(_array);

    EndDrawing();
  }
}

void SortVisualizer::drawArray(Array &arr) {
  float xStep = static_cast<float>(_width) / static_cast<float>(_size);

  for (size_t i{0}; i < arr.size(); i++) {
    float heightRec = arr[i] * _height * 0.8;

    bool isCompared = _sortAlgorithm->isCompared(i);
    auto color = _sortAlgorithm->isSorted() ? GREEN : isCompared ? RED : RAYWHITE;
    DrawRectangle(xStep * i, GetScreenHeight() - heightRec, xStep, heightRec, color);
  }
}

void SortVisualizer::reset() {
  _sortAlgorithm->reset();

  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for (size_t i = 0; i < _size; i++) {
    _array[i] = dist(rng);
  }
}

void SortVisualizer::setFPS(int fps) {
  SetTargetFPS(fps);
}
