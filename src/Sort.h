#pragma once

#include <vector>
#include <set>
#include <string>
#include <stack>
#include "../include/raylib.h"

using Array = std::vector<float>;

class Sort {
public:
  virtual void sort(Array &arr) = 0;
  virtual void sortStep(Array &arr) = 0;
  virtual bool isSorted() = 0;
  virtual void reset() = 0;
  virtual bool isCompared(int index) = 0;

  virtual const char *sortName() = 0;

  void begin() {
    _startTime = GetTime();
    _started = true;
  }
  double elapsed() {
    if (_sorted)
      return _elapsedTime;

    return _started ? GetTime() - _startTime : 0.0;
  }

  void end() {
    _elapsedTime = elapsed();
    _sorted = true;
    _compared.clear();
  }

protected:
  double _startTime = 0;
  double _elapsedTime = 0;
  bool _started = false;
  bool _sorted = false;
  std::set<size_t> _compared;
};

class MergeSort : public Sort {
public:
  void sort(Array &arr) override;
  void sortStep(Array &arr) override;
  void reset() override;
  bool isSorted() override;

  bool isCompared(int index) override { return _compared.find(index) != _compared.end(); }
  const char *sortName() override { return "Merge Sort"; }

private:
  void merge(Array &left, Array &right, Array &arr);

  void mergeSubarray(Array &arr, size_t left, size_t mid, size_t right);

  size_t _width = 1;
  size_t _left = 0;
};

class BubbleSort : public Sort {
public:
  void sort(Array &arr) override;
  void sortStep(Array &arr) override;
  bool isSorted() override { return _sorted; };
  void reset() override;

  bool isCompared(int index) override { return _compared.find(index) != _compared.end(); }
  const char *sortName() override { return "Bubble  Sort"; }

private:
  size_t _i = 0;
  size_t _j = 0;
  bool _noSwaps = true;
};

class QuickSort : public Sort {
public:
  void sort(Array &arr) override;
  void sortStep(Array &arr) override;
  bool isSorted() override { return _sorted; }
  void reset() override;
  bool isCompared(int index) override { return _compared.find(index) != _compared.end(); }
  const char *sortName() override { return "Quick Sort"; }

private:
  int partition(Array &arr, int low, int high);

  std::stack<std::pair<int, int>> _stack;  // rangos pendientes
  bool _initialized = false;
};
