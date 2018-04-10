#include <iostream> 
#include <cassert>
#include <utility>
#include <vector>
#include <stack>
#include <string>

using namespace std;
bool checkParenthesis(const string& input)
{
    stack<char> record;
    for (auto iter = input.cbegin(); iter != input.cend(); ++iter) {
        if (*iter == '(') {
            record.push(*iter);
        }
        else if (*iter == ')') {
            if (record.top() == '(')
                record.pop();
            else
                return false;
        }
    }
}

int main (int argc, char** argv) {
    
}
