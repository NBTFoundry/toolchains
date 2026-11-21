// SPDX-License-Identifier: MPL-2.0
// The QNX 6.5 target's run-time check: C++ exceptions, RTTI, threads,
// mutexes and condition variables, thread_local, static constructors, the
// C library through the car's libc.so.3 (stdio, errno, time, files) and libm.
// Prints "qnx-probe: PASS" when every check holds; run it in the QNX 6.5 VM
// (or on the car).
#include <cerrno>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <vector>

namespace {

int failures = 0;

void check(bool ok, const char* what) {
    std::printf("%s %s\n", ok ? "ok  " : "FAIL", what);
    if (!ok)
        ++failures;
}

struct Constructed {
    int value = 0;
    Constructed() { value = 42; }
};
Constructed constructed;

thread_local int per_thread = 1;

struct Base {
    virtual ~Base() = default;
};
struct Derived : Base {};

}  // namespace

int main(int argc, char** argv) {
    check(argc >= 1 && argv[0] != nullptr, "arguments");
    check(constructed.value == 42, "static constructor ran");

    bool caught = false;
    try {
        throw std::runtime_error("thrown");
    } catch (const std::exception& e) {
        caught = std::strcmp(e.what(), "thrown") == 0;
    }
    check(caught, "exception caught with its message");

    Base* b = new Derived;
    check(dynamic_cast<Derived*>(b) != nullptr, "dynamic_cast");
    delete b;

    std::map<std::string, std::vector<int>> m;
    for (int i = 0; i < 100; ++i)
        m["k" + std::to_string(i % 7)].push_back(i);
    check(m.size() == 7 && m["k3"].size() == 14, "map, string, vector");

    std::mutex mu;
    std::condition_variable cv;
    int counter = 0;
    std::vector<std::thread> threads;
    for (int t = 0; t < 4; ++t)
        threads.emplace_back([&] {
            per_thread = 7;
            for (int i = 0; i < 1000; ++i) {
                std::lock_guard<std::mutex> lock(mu);
                ++counter;
            }
            cv.notify_all();
        });
    {
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock, [&] { return counter == 4000; });
    }
    for (auto& t : threads)
        t.join();
    check(counter == 4000, "threads, mutex, condition variable");
    check(per_thread == 1, "thread_local per thread");

    errno = 0;
    check(open("/nonexistent/file", O_RDONLY) == -1 && errno == ENOENT, "errno from the C library");

    struct timespec ts {};
    check(clock_gettime(CLOCK_MONOTONIC, &ts) == 0 && (ts.tv_sec > 0 || ts.tv_nsec > 0), "clock_gettime");

    struct stat st {};
    check(stat("/", &st) == 0 && S_ISDIR(st.st_mode), "stat");

    check(std::fabs(std::sqrt(2.0) * std::sqrt(2.0) - 2.0) < 1e-12 && std::fabs(std::sin(0.0)) < 1e-12, "libm");

    char buf[32];
    std::snprintf(buf, sizeof buf, "%d %s %.2f", 7, "x", 1.5);
    check(std::strcmp(buf, "7 x 1.50") == 0, "snprintf");

    std::printf("qnx-probe: %s\n", failures == 0 ? "PASS" : "FAIL");
    return failures == 0 ? 0 : 1;
}
