#include <iostream>
#include <stdexcept>

using std::cout, std::cin, std::cerr, std::invalid_argument, std::out_of_range, std::exception;

template <typename T, size_t N>
class Stack {
private:
    T *top;
    T items[N] = {};
public:
    Stack();
    ~Stack() = default;

    bool isEmpty();

    void push(T x);
    void pop();
    T get_top();
};

template<typename T, size_t N>
Stack<T, N>::Stack() : top(items-1) {}

template<typename T, size_t N>
bool Stack<T, N>::isEmpty() {
    return (top == items-1);
}

template<typename T, size_t N>
void Stack<T, N>::push(T x) {
    if (top == &items[N-1]) throw invalid_argument("Can't push element, stack is full");
    top++;
    items[top-items] = x;
}

template<typename T, size_t N>
void Stack<T, N>::pop() {
    if (top == items-1) throw invalid_argument("Can't pop element, stack is empty");
    items[top-items] = 0;
    top--;
}

template<typename T, size_t N>
T Stack<T, N>::get_top() {
    if (top == items-1) throw out_of_range("Can't get top of stack, stack is empty");
    return items[top-items];
}

void test_stack() {
    const int n = 3;
    Stack<int, n> stack;


    if (stack.isEmpty()) {
        cout << "Test passed: stack created.\n";
    } else {
        cerr << "Test failed: stack wasn't created.\n";
    }

    // push()
    int items[] = {-3, 0, 2};
    try {
        stack.push(items[0]);
        if (!stack.isEmpty() && stack.get_top() == items[0]) {
            cout << "Test passed: push().\n";
        }
        else {
            cerr << "Test failed: item was pushed incorrectly.\n";
        }
    }
    catch (exception& ex) {
        cerr << "Error during push() test.\n";
        cerr << ex.what();
    }

    stack.push(items[1]);
    stack.push(items[2]);
    try {
        stack.push(1);
        cerr << "Test failed: item was pushed to the full stack.\n";
    } catch (exception& ex) {
        cout << "Test passed: pushing element to the full stack. (what(): "
             << ex.what() << ")\n";
    }

    // pop()
    try {
        stack.pop();
        if (stack.get_top() == items[1]) {
            cout << "Test passed: pop().\n";
        }
        else {
            cerr << "Test failed: item was popped incorrectly.\n";
        }
    } catch (exception& ex) {
        cerr << "Error during pop() test.\n";
        cerr << ex.what();
    }

    stack.pop();
    stack.pop();
    try {
        stack.pop();
        cerr << "Test failed: item was popped from empty stack.\n";
    } catch (exception& ex) {
        cout << "Test passed: popping element from the empty stack. (what(): "
             << ex.what() << ")\n";
    }

    // get_top()
    try {
        stack.push(items[0]);
        stack.get_top();
        if (stack.get_top() == items[0]) {
            cout << "Test passed: get_top().\n";
        }
        else {
            cerr << "Test failed: top item gotten incorrectly.\n";
        }
    } catch (exception& ex) {
        cerr << "Error during get_top() test.\n";
        cerr << ex.what();
    }
    stack.pop();
    try {
        stack.get_top();
        cerr << "Test failed: got top element from empty stack.\n";
    } catch (exception& ex) {
        cout << "Test passed: getting top element from the empty stack. (what(): "
             << ex.what() << ")\n";
    }
}

int main() {
    test_stack();
    return 0;
}
