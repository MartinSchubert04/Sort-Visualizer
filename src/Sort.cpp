#include "Sort.h"

// ---- Merge Sort --------------------

void MergeSort::sort(Array &arr) {
  if (arr.size() == 1)
    return;

  int half = arr.size() / 2;

  Array left(arr.begin(), arr.begin() + half);
  Array right(arr.begin() + half, arr.end());

  sort(left);
  sort(right);

  merge(left, right, arr);
}

void MergeSort::merge(Array &left, Array &right, Array &arr) {
  size_t i = 0, j = 0, k = 0;

  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j])
      arr[k++] = left[i++];
    else
      arr[k++] = right[j++];
  }

  while (i < left.size())
    arr[k++] = left[i++];
  while (j < right.size())
    arr[k++] = right[j++];
}

void MergeSort::sortStep(Array &arr) {
  if (_sorted)
    return;

  if (!_started) {
    begin();
  }

  size_t mid = std::min(_left + _width, arr.size());
  size_t right = std::min(_left + _width * 2, arr.size());

  mergeSubarray(arr, _left, mid, right);

  _left += _width * 2;

  if (_left >= arr.size()) {
    _width *= 2;
    _left = 0;

    if (_width >= arr.size())
      end();
  }
}

void MergeSort::mergeSubarray(Array &arr, size_t left, size_t mid, size_t right) {
  _compared.clear();

  Array temp(arr.begin() + left, arr.begin() + right);

  size_t i = 0;
  size_t j = mid - left;
  size_t k = left;

  while (i < mid - left && j < right - left) {
    _compared.emplace(i);
    if (temp[i] <= temp[j])
      arr[k++] = temp[i++];
    else
      arr[k++] = temp[j++];
  }

  while (i < mid - left)
    arr[k++] = temp[i++];
  while (j < right - left)
    arr[k++] = temp[j++];
}

void MergeSort::reset() {
  _width = 1;
  _left = 0;
  _sorted = false;
  _elapsedTime = 0;
  _startTime = GetTime();
  _started = false;
}

bool MergeSort::isSorted() {
  return _sorted;
}

// ---- Bubble Sort --------------------

void BubbleSort::sort(Array &arr) {}

void BubbleSort::sortStep(Array &arr) {
  if (_sorted)
    return;

  if (!_started) {
    begin();
  }

  _compared.clear();
  if (arr[_j] > arr[_j + 1]) {
    std::swap(arr[_j], arr[_j + 1]);

    _compared.emplace(_j);
    _compared.emplace(_j + 1);

    _noSwaps = false;
  }

  _j++;

  if (_j >= arr.size() - _i - 1) {
    if (_noSwaps)
      end();
    _j = 0;
    _i++;
    _noSwaps = true;
  }
}

void BubbleSort::reset() {
  _i = 0;
  _j = 0;
  _sorted = false;
  _noSwaps = true;
  _compared.clear();
  _elapsedTime = 0;
  _startTime = GetTime();
}

// ---- Quick Sort --------------------

void QuickSort::sortStep(Array &arr) {
  if (_sorted)
    return;

  if (!_initialized) {
    _stack.push({0, (int)arr.size() - 1});
    _initialized = true;
    begin();
  }

  if (_stack.empty()) {
    end();
    return;
  }

  auto [low, high] = _stack.top();
  _stack.pop();

  if (low < high) {
    int p = partition(arr, low, high);

    _stack.push({low, p - 1});
    _stack.push({p + 1, high});
  }
}

int QuickSort::partition(Array &arr, int low, int high) {
  _compared.clear();
  for (int i = low; i <= high; i++)
    _compared.insert(i);

  float pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }

  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

void QuickSort::reset() {
  while (!_stack.empty())
    _stack.pop();
  _initialized = false;
  _sorted = false;
  _started = false;
  _compared.clear();
}

void QuickSort::sort(Array &arr) {
  // no se usa, todo va por sortStep
}
