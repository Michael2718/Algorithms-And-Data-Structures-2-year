#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <cmath>

using std::string, std::stack, std::cout, std::cin, std::endl, std::vector, std::isdigit, std::stoi;

int operation_priority(const string& str) {
    if (str == "abs" || str == "fact") return 3;
    else if (str == "/" || str == "*") return 2;
    else if (str == "+" || str == "-") return 1;
    else return 0;
}

bool is_number(const string& str) {
    for (char c: str) if (!isdigit(c)) return false;
    return true;
}

vector<string> split(const string& str) {
    vector<string> lexemes;
    string lexeme;
    for (char x: string(str + " ")) {
        if (x == ' ') {
            lexemes.push_back(lexeme);
            lexeme = "";
        } else {
            lexeme += x;
        }
    }
    return lexemes;
}

vector<string> infix_to_postfix(const string& str) {
    stack<string> operations;
    vector<string> result;

    vector<string> lexemes = split(str);
    for (const string& l : lexemes) {
        if (is_number(l)) {
            result.push_back(l);
        } else if (l == "(") {
            operations.push("(");
        } else if (l == ")") {
            while (operations.top() != "(") {
                result.push_back(operations.top());
                operations.pop();
            }
            operations.pop();
        } else {
            while (!operations.empty() && operation_priority(l) <= operation_priority(operations.top())) {
                result.push_back(operations.top());
                operations.pop();
            }
            operations.push(l);
        }
    }

    while (!operations.empty()) {
        result.push_back(operations.top());
        operations.pop();
    }

    return result;
}

int fact(int n) {
    if (n == 0 || n == 1) return 1;
    else return n * fact(n-1);
}

int calculate_postfix(const vector<string>& exp) {
    stack<int> stack;
    int op1;
    for (const string& x : exp) {
        if(is_number(x)) {
            stack.push(stoi(x));
        } else if (x == "abs") {
            op1 = abs(stack.top());
            stack.pop();
            stack.push(op1);
        } else if (x == "fact") {
            op1 = fact(stack.top());
            stack.pop();
            stack.push(op1);
        } else {
            op1 = stack.top();
            stack.pop();
            if (x == "+") {
                op1 += stack.top();
                stack.pop();
                stack.push(op1);
            } else if (x == "-") {
                op1 = stack.top() - op1;
                stack.pop();
                stack.push(op1);
            } else if (x == "/") {
                op1 = (int) stack.top() / op1;
                stack.pop();
                stack.push(op1);
            } else if (x == "*") {
                op1 *= stack.top();
                stack.pop();
                stack.push(op1);
            }
        }
    }
    return stack.top();
}

int main() {
    cout << "Enter expression in infix notation. Use spaces between all lexemes(available operations: +,-,*,/,abs,fact):\n";
    string expression; // Test with all operations: abs ( 4 - 6 ) + fact ( 12 / 2 ) * 5
    getline(cin, expression);
    vector<string> postfix = infix_to_postfix(expression);
    cout << "Expression in postfix notation: ";
    for (const auto& x: postfix) cout << x << " ";
    cout << "\n";
    cout << "Result: " << calculate_postfix(postfix);
    return 0;
}