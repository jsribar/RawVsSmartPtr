// RawVsSmartPtr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <iostream>

class StopWatch
{
public:
    StopWatch(std::ostream& os = std::cout) : m_os(os)
    {
        m_startPoint = std::chrono::high_resolution_clock::now();
    }

    std::chrono::duration<double> Stop()
    {
        auto endPoint = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<double>>(endPoint - m_startPoint);
    }

    ~StopWatch()
    {
        auto endPoint = Stop();
        m_os << endPoint.count() << std::endl;
    }

private:
    std::chrono::high_resolution_clock::time_point m_startPoint;
    std::ostream& m_os;
};

constexpr int count = 1000000;

int newFun()
{
    int result = 0;
    for (int i = 0; i < count; ++i)
    {
        int* p = new int(i);
        result += *p;
        delete p;
    }
    return result;
}

int unique_ptrFun()
{
    int result = 0;
    for (int i = 0; i < count; ++i)
    {
        auto p = std::make_unique<int>(i);
        result += *p;
    }
    return result;
}

int shared_ptrFun()
{
    int result = 0;
    for (int i = 0; i < count; ++i)
    {
        auto p = std::make_shared<int>(i);
        result += *p;
    }
    return result;
}

int main()
{
    std::cout << "With new-delete:\n";
    int sum = 0;
    {
        StopWatch sw;
        sum = newFun();
    }
    std::cout << sum << std::endl;

    std::cout << "With unique_ptr:\n";
    {
        StopWatch sw;
        sum = unique_ptrFun();
    }
    std::cout << sum << std::endl;

    std::cout << "With shared_ptr:\n";
    {
        StopWatch sw;
        sum = shared_ptrFun();
    }
    std::cout << sum << std::endl;
}

