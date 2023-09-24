#include <iostream>
#include <string>
#include <vector>
using namespace std;

// optimizations -std=C++__ &  -O_

//  Thông thường, trình biên dịch, ngay cả khi đã bật tất cả các tối ưu hóa, -O3, -Ofast
//  không bắt buộc phải sử dụng RVO/NRVO mà chỉ có quyền làm như vậy.
//  RVO in C ++ 17, nó đã trở thành một "tối ưu hóa" bắt buộc.
//  Trình biên dịch có quyền sử dụng chúng ngay cả trong tiêu chuẩn C++98

// tot nhat khong nen return bien phuc tap !!
// khong nen viet
uint64_t fffffffff()
{
    uint64_t local_variable = 0;
    // Действия с local_variable
    return std::move(local_variable); // Так писать не стоит
}
// RVO khong hoat dong, vi vay return luon cham !!!! (ngoai tru nhung bien don gian)


void func_1()
{
    std::vector<int> a(2<<20);
    for(std::size_t i = 0; i != 1000; ++i) {
        std::vector<int> b(2<<20);
        a = b;
    }
}

void func_2()
{
    std::vector<int> a(2<<20);
    for(std::size_t i = 0; i != 1000; ++i) {
        std::vector<int> b(2<<20);
        a = std::move(b);
    }
}
// func_2 nhanh hon


// exp
constexpr size_t LOOP = 1000000000;

std::vector<int> foo() { return {1, 2, 3, 4, 5}; }

void foo_optimized(vector<int> &output)
{
    constexpr static int values[] = {1, 2, 3, 4, 5};
    output.assign(&values[0], &values[0] + 5);
}

int not_main(int argc, char **argv)
{
    string type = string(argv[1]);
    if (type == "original")
    {

        std::vector<int> f;
        for (size_t i = 0; i < LOOP; ++i)
            f = foo();
    }
    else if (type == "RVO")
    {

        for (size_t i = 0; i < LOOP; ++i)
            auto f = foo();
    }
    else if (type == "optimized")
    {

        std::vector<int> f;
        for (size_t i = 0; i < LOOP; ++i)
            foo_optimized(f);
    }

    return 0;
}

// $ g++ a.cpp -O3
// $ time ./a.out original && time ./a.out RVO && time ./a.out optimized

// real    0m11.671s
// user    0m11.662s
// sys     0m0.000s

// real    0m15.012s
// user    0m15.011s
// sys     0m0.000s

// real    0m0.767s
// user    0m0.759s
// sys     0m0.000s

// For -O2, the result is:

// original - 14.221s
// RVO - 14.993s
// optimized - 4.483s