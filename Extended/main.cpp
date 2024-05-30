#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

// precedence checking
int pre(char ch)
{
    switch (ch)
    {
    case '-':
    case '+':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '(':
    case ')':
        return 4;
    default:
        return -1;
    }
}

// calculate
float calculate(char op, float num1, float num2)
{
    if (op == '+')
        return num1 + num2;

    if (op == '-')
        return num1 - num2;

    if (op == '*')
        return num1 * num2;

    if (op == '/')
    {
        if (num2 != 0)
        {
            return num1 / num2;
        }
        return 0;
    }
    if (op == '^')
        return pow(num1, num2);

    return -1;
}
int main()
{
    string math = "";
    cout << "Nhap bieu thuc: ";
    getline(cin, math);
    stack<char> ops;
    stack<float> nums;
    float sign = 1;

    int i = 0;
    while (i < math.size())

    {
        if (math[i] == '(')
        {
            ops.push('(');
            i++;
        }
        else if (math[i] == ')')
        {
            while (ops.top() != '(')
            {
                float num2 = nums.top();
                nums.pop();
                float num1 = nums.top();
                nums.pop();
                float res = calculate(ops.top(), num1, num2);
                nums.push(res);
                ops.pop();
            }
            ops.pop();
            i++;
        }
        else if (math[i] == '-' && (i == 0 || math[i - 1] == '^' || math[i - 1] == '*' || math[i - 1] == '/'))
        {
            sign = -1;
            i++;
            goto negav;
        }
        else if (math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/' || math[i] == '^')
        {
            int pre_cur = pre(math[i]);
            while (!ops.empty() && pre(ops.top()) >= pre_cur)
            {
                float num2 = nums.top();
                nums.pop();
                float num1 = nums.top();
                nums.pop();
                float res = calculate(ops.top(), num1, num2);
                nums.push(res);
                ops.pop();
            }
            ops.push(math[i]);
            i++;
        }

        else
        {
        negav:
            int len = 0;
            while (isdigit(math[i]) || math[i] == '.')
            {
                i++;
                len++;
            }
            string temp = math.substr(i - len, len);
            nums.push(stof(temp) * sign);
            sign = 1;
        }
    }
    while (!ops.empty())
    {
        float num2 = nums.top();
        nums.pop();
        float num1 = nums.top();
        nums.pop();
        float res = calculate(ops.top(), num1, num2);
        nums.push(res);
        ops.pop();
    }

    cout << "Ket qua: " << nums.top() << endl;
    return 0;
}