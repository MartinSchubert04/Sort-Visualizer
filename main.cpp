#include <cstddef>
#include <vector>
#include <random>
#include <set>
#include "include/raylib.h"

using Array = std::vector<float>;

class SortVisualizer {
public:
  SortVisualizer(int maxSize = 100, int screenWidth = 1000, int screenHeight = 800) :
      _width(screenWidth), _height(screenHeight), _maxSize(maxSize) {

    InitWindow(_width, _height, "Sort Visualizer");

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (size_t i = 0; i < _maxSize; i++) {
      _array.push_back(dist(rng));
    }

    // SetTargetFPS(120);
  }

  void main() {
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
      SetWindowTitle(TextFormat("Sort Visualizer | FPS: %d", GetFPS()));

      bubbleSortStep(_array);

      BeginDrawing();

      ClearBackground(BLACK);

      DrawText("Bubble Sort", 190, 150, 20, LIGHTGRAY);

      drawArray(_array);

      EndDrawing();
    }
  }

  void drawArray(Array &arr) {
    float xStep = static_cast<float>(_width) / static_cast<float>(_maxSize);

    for (size_t i{0}; i < arr.size(); i++) {
      float heightRec = arr[i] * _height * 0.8;

      bool isCompared = _compared.find(i) != _compared.end();
      auto color = _sorted ? GREEN : isCompared ? RED : RAYWHITE;
      DrawRectangle(xStep * i, GetScreenHeight() - heightRec, xStep, heightRec, color);
    }
  }

  void bubbleSortStep(Array &arr) {
    _compared.clear();
    if (_sorted)
      return;

    if (arr[_j] > arr[_j + 1]) {
      std::swap(arr[_j], arr[_j + 1]);

      _compared.emplace(_j);
      _compared.emplace(_j + 1);

      _noSwaps = false;
    }

    _j++;

    if (_j >= arr.size() - _i - 1) {
      if (_noSwaps)
        _sorted = true;  // no swaps, end sorting
      _j = 0;
      _i++;
      _noSwaps = true;
    }
  }

  void setArray(Array arr) { _array = arr; }

private:
  size_t _i = 0;
  size_t _j = 0;
  bool _noSwaps = true;
  bool _sorted = false;
  std::set<size_t> _compared;

  int _height;
  int _width;
  const int _maxSize;
  Array _array;
};

int main() {

  SortVisualizer instance;

  instance.main();

  return 0;
}
