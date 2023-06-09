//
// Created by ct_co on 05/01/2022.
//

#ifndef TOPOGRAPHY_PRIORITYQUEUE_H
#define TOPOGRAPHY_PRIORITYQUEUE_H


#include <queue>

template<typename T, typename priority_t>
class PriorityQueue {

    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
    std::greater<PQElement>> elements;

public:
    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }


};

#endif //TOPOGRAPHY_PRIORITYQUEUE_H
