#include "test_runner.h"

#include <iostream>
#include <exception>
#include <functional>

float PeakFindImpl(int32_t begin, int32_t last, const std::function<float(int32_t)> &foo)
{
    if (begin == last){
        return foo(begin);
    }

    int32_t mid = (begin + last) / 2;

    float value_mid = foo(mid);
    float value_l, value_r;

    value_l = value_r = value_mid;

    // check left side
    int32_t left_idx = mid - 1;
    int32_t right_idx = mid + 1;

    if (begin <= left_idx){
        value_l = foo(left_idx);
    }

    if (right_idx <= last){
        value_r = foo(right_idx);
    }

    //std::cout << value_l << ' ' << value_r << std::endl;

    if (value_mid < value_r) { // 
        return PeakFindImpl(right_idx, last, foo);
    }

    if (value_l > value_mid) {
        return PeakFindImpl(begin, left_idx, foo);
    }

    return value_mid;
}


//
// [begin, last]

float PeakFind(int32_t begin, int32_t last, const std::function<float(int32_t)> &foo)
{
    if (last < begin) {
        std::runtime_error("error");
    }
    
    return PeakFindImpl(begin, last, foo);
}

void TestPeak()
{
    {
        std::vector<float> arr = {100.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[0]);
    }

    {
        std::vector<float> arr = {100.f, 200.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[1]);
    }

    {
        std::vector<float> arr = {100.f, 200.f, 300.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[2]);
    }

    {
        std::vector<float> arr = {100.f, 200.f, 300.f, 400.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[3]);
    }

    {
        std::vector<float> arr = {100.f, 200.f, 400.f, 300.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[2]);
    }

    {
        std::vector<float> arr = {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 6.f, 0.f, -1.f, -2.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[7]);
    }

    {
        std::vector<float> arr = {-100.f, -80.f, -70.f, -60.f, -50.f, -60.f, -70.f, -80.f, -100.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[4]);
    }

    {
        std::vector<float> arr = {0.f, 10.f, 20.f, 30.f, 40.f, 50.f, 60.f, 70.f, 80.f, 90.f, 100.f, 110.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[11]);
    }

    {
        std::vector<float> arr = {110.f, 100.f, 90.f, 80.f, 70.f, 60.f, 50.f, 40.f, 30.f, 20.f, 10.f, 0.f};
        ASSERT_EQUAL(PeakFind(0, arr.size() - 1, [&arr](int32_t idx) {
            return arr[idx];
        }), arr[0]);
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPeak);
  return 0;
}