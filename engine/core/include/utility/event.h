#ifndef SHIROIENGINE_EVENT_H
#define SHIROIENGINE_EVENT_H

#include <functional>
#include <vector>

template<typename ...T>
class Event {
public:
    typedef std::function<void(T...)> EventListener;
private:
    std::vector<EventListener *> listeners;
public:
    void operator+=(EventListener &listener) {
        operator+=(&listener);
    }

    void operator+=(EventListener *listener) {
        listeners.push_back(listener);
    }

    void operator-=(EventListener &listener) {
        operator-=(&listener);
    }

    void operator-=(EventListener *listener) {
        listeners.erase(listener);
    }

    void operator()(T... arguments) {
        for (auto listener : listeners) {
            listener(arguments...);
        }
    }
};

#endif
