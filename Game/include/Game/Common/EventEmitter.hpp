#pragma once

#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <mutex>

namespace Vexile {

class EventEmitter final {
public:
        using EventHandler = void(*)(void*);

        // return id of mapped listner
        int addListner(const std::string& eventName, EventHandler);
        // return true if removed, false if handler not mapped
        bool removeListner(int id);
        void notifyListners(const std::string& eventName, void * userData);

private:
        struct Listner {
                uint64_t id;
                EventHandler handler;
        };
        using Listners = std::vector<Listner>;
        using NamedListners = std::map<std::string, Listners>;

        NamedListners _listners;
        uint64_t _lastId{0};
        std::mutex _mtx;

};

}
