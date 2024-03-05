#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main()
{
    stack<int> intStack;

    intStack.push(5);
    intStack.push(10);
    intStack.push(15);
    intStack.push(20);
    intStack.push(25);

    queue<int> intQueue;

    cout << "Popping from stack: ";

    while (!intStack.empty())
    {
        int num = intStack.top();
        intQueue.push(num);
        cout << num << " ";
        intStack.pop();
    }

    cout << endl << "Popping from queue: ";

    while (!intQueue.empty())
    {
        int num = intQueue.front();
        cout << num << " ";
        intQueue.pop();
    }

}