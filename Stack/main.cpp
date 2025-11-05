#include "Stack.h"
#include <iostream>
#include <cassert>
#include <vector>

void test_basic_operations() {
    std::cout << "=== Test 1: Basic Operations ===" << std::endl;
    
    Stack<int> stack;
    assert(stack.empty());
    assert(stack.size() == 0);
    
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    assert(!stack.empty());
    assert(stack.size() == 3);
    assert(stack.top() == 30);
    
    std::cout << "After push(10), push(20), push(30):" << std::endl;
    std::cout << "  size = " << stack.size() << std::endl;
    std::cout << "  top = " << stack.top() << std::endl;
    
    stack.pop();
    assert(stack.size() == 2);
    assert(stack.top() == 20);
    std::cout << "After pop(): top = " << stack.top() << std::endl;
    
    stack.pop();
    assert(stack.size() == 1);
    assert(stack.top() == 10);
    std::cout << "After pop(): top = " << stack.top() << std::endl;
    
    stack.pop();
    assert(stack.empty());
    assert(stack.size() == 0);
    std::cout << "After pop(): empty = " << stack.empty() << std::endl;
    
    std::cout << "✓ Basic operations test passed\n" << std::endl;
}

void test_copy_constructor() {
    std::cout << "=== Test 2: Copy Constructor ===" << std::endl;
    
    Stack<int> original;
    original.push(100);
    original.push(200);
    original.push(300);
    
    Stack<int> copied(original);
    
    assert(copied.size() == 3);
    assert(copied.top() == 300);
    
    std::cout << "Original stack: size = " << original.size() << ", top = " << original.top() << std::endl;
    std::cout << "Copied stack: size = " << copied.size() << ", top = " << copied.top() << std::endl;
    
    original.pop();
    assert(original.size() == 2);
    assert(copied.size() == 3);
    
    std::cout << "After modifying original:" << std::endl;
    std::cout << "  Original size = " << original.size() << std::endl;
    std::cout << "  Copied size = " << copied.size() << " (unchanged)" << std::endl;
    
    assert(copied.top() == 300);
    copied.pop();
    assert(copied.top() == 200);
    copied.pop();
    assert(copied.top() == 100);
    
    std::cout << "✓ Copy constructor test passed\n" << std::endl;
}

void test_move_constructor() {
    std::cout << "=== Test 3: Move Constructor ===" << std::endl;
    
    Stack<int> original;
    original.push(42);
    original.push(84);
    
    size_t original_size = original.size();
    
    Stack<int> moved(std::move(original));
    
    assert(moved.size() == original_size);
    assert(moved.top() == 84);
    assert(original.empty());
    
    std::cout << "Moved stack: size = " << moved.size() << ", top = " << moved.top() << std::endl;
    std::cout << "Original stack (after move): empty = " << original.empty() << std::endl;
    
    std::cout << "✓ Move constructor test passed\n" << std::endl;
}

void test_copy_assignment() {
    std::cout << "=== Test 4: Copy Assignment ===" << std::endl;
    
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    
    Stack<int> stack2;
    stack2.push(10);
    stack2.push(20);
    stack2.push(30);
    
    std::cout << "Before assignment:" << std::endl;
    std::cout << "  stack1: size = " << stack1.size() << ", top = " << stack1.top() << std::endl;
    std::cout << "  stack2: size = " << stack2.size() << ", top = " << stack2.top() << std::endl;
    
    stack1 = stack2;
    
    assert(stack1.size() == stack2.size());
    assert(stack1.top() == stack2.top());
    
    std::cout << "After stack1 = stack2:" << std::endl;
    std::cout << "  stack1: size = " << stack1.size() << ", top = " << stack1.top() << std::endl;
    std::cout << "  stack2: size = " << stack2.size() << ", top = " << stack2.top() << std::endl;
    
    stack1 = stack1;
    assert(stack1.size() == 3);
    
    std::cout << "✓ Copy assignment test passed\n" << std::endl;
}

void test_move_assignment() {
    std::cout << "=== Test 5: Move Assignment ===" << std::endl;
    
    Stack<int> stack1;
    stack1.push(100);
    
    Stack<int> stack2;
    stack2.push(200);
    stack2.push(300);
    
    std::cout << "Before move assignment:" << std::endl;
    std::cout << "  stack1: size = " << stack1.size() << std::endl;
    std::cout << "  stack2: size = " << stack2.size() << std::endl;
    
    stack1 = std::move(stack2);
    
    assert(stack1.size() == 2);
    assert(stack1.top() == 300);
    assert(stack2.empty());
    
    std::cout << "After stack1 = std::move(stack2):" << std::endl;
    std::cout << "  stack1: size = " << stack1.size() << ", top = " << stack1.top() << std::endl;
    std::cout << "  stack2: empty = " << stack2.empty() << std::endl;
    
    std::cout << "✓ Move assignment test passed\n" << std::endl;
}

void test_exceptions() {
    std::cout << "=== Test 6: Exception Handling ===" << std::endl;
    
    Stack<int> empty_stack;
    
    try {
        empty_stack.top();
        std::cout << "✗ ERROR: top() should throw on empty stack!" << std::endl;
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "  top() on empty stack: " << e.what() << std::endl;
    }
    
    try {
        empty_stack.pop();
        std::cout << "✗ ERROR: pop() should throw on empty stack!" << std::endl;
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "  pop() on empty stack: " << e.what() << std::endl;
    }
    
    std::cout << "✓ Exception handling test passed\n" << std::endl;
}

void test_custom_allocator() {
    std::cout << "=== Test 7: Custom Allocator ===" << std::endl;
    
    std::allocator<int> alloc;
    Stack<int, std::allocator<int>> stack(alloc);
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    assert(stack.size() == 3);
    std::cout << "Stack with custom allocator: size = " << stack.size() << std::endl;
    
    std::cout << "✓ Custom allocator test passed\n" << std::endl;
}


int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Stack Container Tests" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    try {
        test_basic_operations();
        test_copy_constructor();
        test_move_constructor();
        test_copy_assignment();
        test_move_assignment();
        test_exceptions();
        test_custom_allocator();

        std::cout << "========================================" << std::endl;
        std::cout << "   All tests passed! ✓" << std::endl;
        std::cout << "========================================" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
    }
}