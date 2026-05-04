#include "Sort.h"
#include "SortVisualizer.h"

int main() {

  SortVisualizer instance(500, 2000, 1000);

  BubbleSort sort;

  instance.setSortType(&sort);
  instance.setFPS(1000);
  instance.main();

  return 0;
}
