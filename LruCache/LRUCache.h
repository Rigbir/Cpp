//
// Created by Marat on 4.10.25.
//

#pragma once
#include <list>
#include <unordered_map>

template <typename Key, typename Value>
class LRUCache {
private:
    const size_t capacity_;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> map_;
    std::list<std::pair<Key, Value>> list_;

public:
    explicit LRUCache(const size_t capacity): capacity_(capacity) {}

    void put(const Key& key, const Value& value) noexcept {
        if (map_.contains(key)) {
            list_.erase(map_[key]);
        }

        list_.emplace_front(key, value);
        map_[key] = list_.begin();
        evictIfNeeded();
    }

    Value get(const Key& key) noexcept {
        if (!map_.contains(key)) return {};

        list_.splice(list_.begin(), list_, map_[key]);
        return map_[key]->second;
    }

    bool size() const noexcept { return list_.size(); }
    bool empty() const noexcept { return list_.empty(); }

private:
    void evictIfNeeded() noexcept {
        if (list_.size() <= capacity_) return;

        auto& keyToRemove = list_.back();
        map_.erase(keyToRemove.first);
        list_.pop_back();
    }
};