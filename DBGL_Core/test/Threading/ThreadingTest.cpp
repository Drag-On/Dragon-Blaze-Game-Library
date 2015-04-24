//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Threading/ThreadPool.h"
#include "DBGL/Core/Test/Test.h"

#include <chrono>

using namespace dbgl;
using namespace std;

pair<int, bool> isPrime(int n)
{
    for (int i = 2; i <= std::sqrt(n); i++)
        if (n % i == 0)
            return make_pair(n, false);
    return make_pair(n, true);
}

TEST(ThreadPool, default)
{
    ThreadPool pool(4);
    auto fut1 = pool.enqueue([]() { return 42; });
    fut1.wait();
    ASSERT_EQ(fut1.get(), 42);
    auto fut2 = pool.enqueue([](int i) { return i; }, 42);
    fut2.wait();
    ASSERT_EQ(fut2.get(), 42);
    auto fut3 = pool.enqueue([]() { throw "Bug!!!"; });
    fut3.wait();

    std::future<void> futures[10];
    int maxTime = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        maxTime += i * 10;
        futures[i] = pool.enqueue(
                [](int i) { std::this_thread::sleep_for(std::chrono::milliseconds(i * 10)); }, i);
    }

    for (auto& fut : futures)
        fut.wait();
    auto end = std::chrono::high_resolution_clock::now();
    auto took = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    ASSERT(took.count() <= maxTime);

    std::vector<future<pair<int, bool>>> results;
    for (int i = 2; i < 10000; i++)
    {
        // Add a task to the queue.
        results.push_back(pool.enqueue(isPrime, i));
    }
    for (auto& fut : results)
        fut.wait();

    ASSERT_EQ(results[9973 - 2].get().second, true);

//    for (auto i = results.begin(); i != results.end(); i++)
//    {
//        pair<int, bool> result = i->get();
//        cout << result.first << ": " << (result.second ? "is prime" : "is composite") << endl;
//    }
}
