#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits>
#include <time.h>

template <typename T>
void generateRandomNumbers(std::vector<T> &data, const uint32_t &nrand,
                           bool max_limit = false) {
  srand((unsigned int)time(NULL));
  T a = T(5.0);
  if (max_limit) {
    a = std::numeric_limits<T>::max();
  }
  for (uint32_t i = 0; i < nrand; i++) {
    T tmp = T(((double)(rand()) / (double)(RAND_MAX)) * a);
    data.push_back(tmp);
  }
}


int main()
{
  const uint32_t graphInSize = 10;
  std::vector<float> data;
  generateRandomNumbers<float>(data, graphInSize);

  std::cout << "rand: ";

  for (int i = 0;i<data.size();i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
