#include <cstdint>
#include <iostream>
#include <random>

#include <omp.h>

int64_t MultiThread(const std::vector<int>& first_array,
                    const std::vector<int>& second_array) {
  uint64_t result = 0;
  size_t i = 0;
  size_t size = first_array.size();

#pragma omp parallel for  private(i) schedule(static) reduction(+:result)
  for (i = 0; i < size; ++i) {
    result += (first_array[i] * second_array[i]);
  }

  return result;
}

int64_t SingleThread(const std::vector<int>& first_array,
                     const std::vector<int>& second_array) {
  uint64_t result = 0;
  size_t i = 0;
  size_t size = first_array.size();
  for (i = 0; i < size; i++) {
    result += (first_array[i] * second_array[i]);
  }
  return result;
}

signed main() {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, 10000);

  size_t size = 200000000;
  std::cout << "Size: " << size << std::endl;

  std::vector<int> first_array(size);
  std::vector<int> second_array(size);
  for (int i = 0; i < size; ++i) {
    first_array[i] = distribution(generator);
    second_array[i] = distribution(generator);
  }

  double start_time = omp_get_wtime();
  uint64_t multi_thread_result = MultiThread(first_array, second_array);
  double end_time = omp_get_wtime();

  std::cout << "Multi thread time = " << end_time - start_time << std::endl;
  std::cout << "Multi thread result = " << multi_thread_result << std::endl;

  start_time = omp_get_wtime();
  uint64_t single_thread_result = SingleThread(first_array, second_array);
  end_time = omp_get_wtime();

  std::cout << "Single thread time = " << end_time - start_time << std::endl;
  std::cout << "Single thread result = " << single_thread_result << std::endl;

  return 0;
}
