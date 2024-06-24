#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

std::mutex coutMutex;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 100);

void moveCars(int id, int V, int startY)
{
    for (int x = 0; x <= 100; ++x)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / V));
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Car " << id << " at (" << x << ", " << startY << ")" << std::endl;
    }
}

void moveMotorcycles(int id, int V, int startX)
{
    for (int y = 0; y <= 100; ++y)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / V));
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Motorcycle " << id << " at (" << startX << ", " << y << ")" << std::endl;
    }
}

int main()
{
    int V;
    std::cout << "Enter speed (V): ";
    std::cin >> V;

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        int startY = dis(gen);
        threads.emplace_back(moveCars, i, V, startY);

        int startX = dis(gen);
        threads.emplace_back(moveMotorcycles, i, V, startX);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}
