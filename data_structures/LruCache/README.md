# LRUCache

`LRUCache` is a **Least Recently Used (LRU) cache** template class. It stores key-value pairs with a limited capacity and supports **O(1) insertion and retrieval operations**.

## Methods

### Modifiers

- `void put(const Key& key, const Value& value) noexcept`  
  Adds or updates a `<key, value>` pair in the cache:
    - If the key exists — removes the old value.
    - Inserts the new element at the front of the list (MRU).
    - If the cache exceeds `capacity_` — removes the LRU element from the back.

### Observers

- `Value get(const Key& key) noexcept`  
  Returns the value associated with the key:
    - If the key exists — moves it to the front (MRU) and returns the value.
    - If the key does not exist — returns a default-constructed `Value` (`Value{}`).

---
