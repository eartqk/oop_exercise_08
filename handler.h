#pragma once

#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <list>
#include <functional>
#include <atomic>
#include <vector>
#include <iostream>

class Handler {
    using TFig = std::shared_ptr<Figure>;
    std::mutex mutex;
    std::thread thread;
    std::condition_variable cv;
    std::list<TFig> figures;
    std::vector<std::function<void(std::list<TFig>&)>> handlers;
    size_t max = 0;

public:
    bool running;

    Handler(size_t size) {
        this->max = size;
        running = true;
        thread = std::thread(Printing, this);
    };

    ~Handler() {
        running = false;
        cv.notify_one();
        thread.join();
    }

    void Functions(std::function<void(const std::list<TFig>&)>&& func) {
        handlers.push_back(func);
    }

    void Push(TFig el) {
        std::unique_lock<std::mutex> lk(mutex);
        figures.push_back(el);
        if (Full()) {
            cv.notify_one();
            cv.wait(lk, [this]() {
                return figures.empty();
            });
        }
    }

    bool Full() {
        return figures.size() == max;
    }

    static void Printing(Handler* t) {
        while (t->running) {
            std::unique_lock<std::mutex> lock(t->mutex);
            t->cv.wait(lock, [t]() {
                return t->Full()||!t->running;
            });
            for (auto& item : t->handlers) {
                item(t->figures);
            }

            t->figures.clear();
            lock.unlock();
            t->cv.notify_one();
        }
    }

};