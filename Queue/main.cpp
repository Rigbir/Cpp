#include "Queue.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>

void test_assert(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << std::endl;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        assert(false);
    }
}

void test_basic_operations() {
    std::cout << "\n=== Test 1: Basic operations ===" << std::endl;
    
    Queue<int> q;
    test_assert(q.empty(), "Queue is empty after creation");
    test_assert(q.size() == 0, "Empty queue size is 0");
    
    q.push(1);
    test_assert(!q.empty(), "Queue is not empty after push");
    test_assert(q.size() == 1, "Queue size is 1");
    test_assert(q.top() == 1, "First element is 1");
    
    q.push(2);
    test_assert(q.size() == 2, "Queue size is 2");
    test_assert(q.top() == 1, "First element remains 1 (FIFO)");
    
    q.push(3);
    test_assert(q.size() == 3, "Queue size is 3");
    test_assert(q.top() == 1, "First element remains 1");
}

void test_pop() {
    std::cout << "\n=== Test 2: Pop operation ===" << std::endl;
    
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    
    test_assert(q.top() == 1, "Before pop first element is 1");
    q.pop();
    test_assert(q.size() == 2, "Size after pop is 2");
    test_assert(q.top() == 2, "After pop first element is 2");
    
    q.pop();
    test_assert(q.size() == 1, "Size after second pop is 1");
    test_assert(q.top() == 3, "After second pop first element is 3");
    
    q.pop();
    test_assert(q.empty(), "Queue is empty after all pops");
    test_assert(q.size() == 0, "Size is 0");
}

void test_exceptions() {
    std::cout << "\n=== Test 3: Exception handling ===" << std::endl;
    
    Queue<int> q;
    
    bool exception_thrown = false;
    try {
        q.pop();
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
        test_assert(std::string(e.what()) == "Queue is empty", "Correct error message for pop");
    }
    test_assert(exception_thrown, "Exception thrown on pop from empty queue");
    
    exception_thrown = false;
    try {
        q.top();
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
        test_assert(std::string(e.what()) == "Queue is empty", "Correct error message for top");
    }
    test_assert(exception_thrown, "Exception thrown on top from empty queue");
}

void test_move_semantics() {
    std::cout << "\n=== Test 4: Move semantics ===" << std::endl;
    
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    Queue<int> q2(std::move(q1));
    test_assert(q2.size() == 3, "Size after move constructor is 3");
    test_assert(q2.top() == 1, "First element after move is 1");
    test_assert(q1.empty(), "Source queue is empty after move");
    
    Queue<int> q3;
    q3 = std::move(q2);
    test_assert(q3.size() == 3, "Size after move assignment is 3");
    test_assert(q3.top() == 1, "First element after move assignment is 1");
    test_assert(q2.empty(), "Source queue is empty after move assignment");
}

void test_copy_semantics() {
    std::cout << "\n=== Test 5: Copy semantics ===" << std::endl;
    
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    Queue<int> q2(q1);
    test_assert(q1.size() == 3, "Source queue size remains 3");
    test_assert(q2.size() == 3, "Copy size is 3");
    test_assert(q1.top() == 1, "Source queue first element is 1");
    test_assert(q2.top() == 1, "Copy first element is 1");
    
    q1.pop();
    test_assert(q1.size() == 2, "Source queue size after pop is 2");
    test_assert(q2.size() == 3, "Copy size remains 3 (independence)");
    
    Queue<int> q3;
    q3 = q2;
    test_assert(q3.size() == 3, "Size after copy assignment is 3");
    test_assert(q2.size() == 3, "Source queue size remains 3");
    
    q3.pop();
    test_assert(q2.size() == 3, "Source queue size did not change");
}

void test_emplace() {
    std::cout << "\n=== Test 6: Emplace ===" << std::endl;
    
    Queue<std::string> q;
    q.emplace("hello");
    test_assert(q.size() == 1, "Size after emplace is 1");
    test_assert(q.top() == "hello", "Element after emplace is 'hello'");
    
    q.emplace(5, 'x');  
    test_assert(q.size() == 2, "Size after second emplace is 2");
    test_assert(q.top() == "hello", "First element remains 'hello'");
    
    q.pop();
    test_assert(q.top() == "xxxxx", "After pop first element is 'xxxxx'");
}

void test_swap() {
    std::cout << "\n=== Test 7: Swap ===" << std::endl;
    
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    
    Queue<int> q2;
    q2.push(10);
    q2.push(20);
    q2.push(30);
    
    q1.swap(q2);
    
    test_assert(q1.size() == 3, "q1 size after swap is 3");
    test_assert(q1.top() == 10, "q1 first element after swap is 10");
    test_assert(q2.size() == 2, "q2 size after swap is 2");
    test_assert(q2.top() == 1, "q2 first element after swap is 1");
}

void test_const_correctness() {
    std::cout << "\n=== Test 8: Const correctness ===" << std::endl;
    
    Queue<int> q;
    q.push(42);
    q.push(100);
    
    const Queue<int>& const_q = q;
    test_assert(const_q.top() == 42, "Const top returns correct value");
    test_assert(const_q.size() == 2, "Const size returns correct value");
    test_assert(!const_q.empty(), "Const empty returns correct value");
}

void test_move_push() {
    std::cout << "\n=== Test 9: Move push ===" << std::endl;
    
    Queue<std::string> q;
    std::string str = "test";
    q.push(std::move(str));
    
    test_assert(q.size() == 1, "Size after move push is 1");
    test_assert(q.top() == "test", "Element after move push is 'test'");
    test_assert(str.empty(), "Source string is empty after move");
}

void test_large_queue() {
    std::cout << "\n=== Test 10: Large queue ===" << std::endl;
    
    Queue<int> q;
    const size_t count = 1000;
    
    for (size_t i = 0; i < count; ++i) {
        q.push(static_cast<int>(i));
    }
    
    test_assert(q.size() == count, "Large queue size is correct");
    test_assert(q.top() == 0, "Large queue first element is correct");
    
    for (size_t i = 0; i < count; ++i) {
        test_assert(q.top() == static_cast<int>(i), "Element " + std::to_string(i) + " is correct");
        q.pop();
    }
    
    test_assert(q.empty(), "Queue is empty after all operations");
}

void test_self_assignment() {
    std::cout << "\n=== Test 11: Self assignment ===" << std::endl;
    
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    
    q = q;  
    
    test_assert(q.size() == 3, "Size after self assignment remains 3");
    test_assert(q.top() == 1, "First element after self assignment remains 1");
}

int main() {
    std::cout << "=== Running Queue autotests ===" << std::endl;
    
    try {
        test_basic_operations();
        test_pop();
        test_exceptions();
        test_move_semantics();
        test_copy_semantics();
        test_emplace();
        test_swap();
        test_const_correctness();
        test_move_push();
        test_large_queue();
        test_self_assignment();
        
        std::cout << "\n=== All tests passed successfully! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] Unexpected exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n[ERROR] Unknown exception" << std::endl;
        return 1;
    }
}
