#include <iostream>
#include <vector>

using std::cout, std::cin;

template <typename T, size_t N>
class Stack {
private:
    T *top;
    T items[N];
public:
    Stack();
    ~Stack() = default;

    bool isEmpty();

    void push(T x);
    T pop();
    T get_top();
};

template<typename T, size_t N>
Stack<T, N>::Stack() : top(items) {}

template<typename T, size_t N>
bool Stack<T, N>::isEmpty() {
    return false;
}


int main() {
    //Stack<int> a(5);
    const int N = 4;
    int a[N] = {-1, -2, -3, -4};
    //Stack<int, 5> stack;
    int *p = a;
    p++;
    p++;
    p++;
    cout << (p == &a[N-1]);
    //a[] = 23;
    //cout << (p == a);
    return 0;
}
