#include <iostream>
#include <stdexcept>

using std::cout, std::cin, std::invalid_argument, std::out_of_range;

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

int main() {
    Stack<int, 3> stack;
    cout << "Stack is " << (stack.isEmpty() ? "" : "not ") << "empty\n";
    cout << "Adding element\n";
    stack.push(-1);
    cout << "Stack is " << (stack.isEmpty() ? "" : "not ") << "empty\n";
    cout << "Top of stack: " << stack.get_top() << "\n";
    cout << "Deleting top element\n";
    stack.pop();
    cout << "Stack is " << (stack.isEmpty() ? "" : "not ") << "empty\n";
    return 0;
}
