#pragma once
#include <cstddef>
#include <vector>
#include <random>
#include "../include/raylib.h"
#include "Sort.h"

using Array = std::vector<float>;

class SortVisualizer {
public:
  SortVisualizer(int size = 100, int screenWidth = 1000, int screenHeight = 800);
  void main();
  void drawArray(Array &arr);
  void reset();
  void setArray(Array arr) { _array = arr; }
  void setSortType(Sort *s) { _sortAlgorithm = s; }
  void setFPS(int fps);

private:
  double _startTime = 0;
  double _elapsedTime = 0;
  bool _started = false;

  Sort *_sortAlgorithm;

  int _height;
  int _width;
  const int _size;
  Array _array;
};
