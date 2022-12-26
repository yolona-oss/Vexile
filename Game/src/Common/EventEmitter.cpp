#include "Vexile/Core/System/EventEmitter.hpp"

#include <climits>

template<typename T, typename... U>
static size_t getAddress(std::function<T(U...)> f) {
        typedef T(fnType)(U...);
        fnType ** fnPointer = f.template target<fnType*>();
        return (size_t) *fnPointer;
}

namespace Vexile {

int EventEmitter::addListner(const std::string& eventName, EventHandler handler) {
        std::lock_guard<std::mutex> lock(_mtx);
        _listners[eventName].push_back({_lastId, handler});
        _lastId++; 
        return _lastId-1;
}

bool EventEmitter::removeListner(int id) {
        std::lock_guard<std::mutex> lock(_mtx);

        for (auto& evListners : _listners) {
                for (int i = 0; i < evListners.second.size(); i++) {
                        auto listner = evListners.second[i];
                        if (listner.id == id) {
                                if (evListners.second.size() == 1) {
                                        std::swap(evListners.second[i], evListners.second[evListners.second.size() - 1]);
                                }
                                evListners.second.pop_back();

                                if (_lastId == id) {
                                        _lastId--;
                                }

                                return true;
                        }
                }
        }

        return false;
}

void EventEmitter::notifyListners(const std::string& eventName, void * userData) {
        auto listners = _listners.find(eventName);
        if (listners != _listners.end()) {
                for (auto &i : listners->second) {
                        i.handler(userData);
                }
        }
}

}
