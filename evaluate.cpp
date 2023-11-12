#include <iostream>
#include <math.h>
#include <cmath>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include "Evaluate.h"
using namespace std;
bool Evaluate::isOperator(string c) {
    return c == "+" || c == "-" || c =="*" || c == "/" || c == "%" || c == "^";
}
int Evaluate::getPrecedence(char op) {
    if (op == '^'){
        return 3;
    }

    else if (op == '*' || op == '/' || op == '%'){
        return 2;
    }

    else if (op == '+' || op == '-'){
        return 1;
    }
    else {
        return 0;
    }
}

double Evaluate::evaluateExpression(const vector<string>& expression) {
    stack<double> operands;
    stack<char> operators; // Initializes the two stacks one for the numbers and one for the operators (+,-, etc.)
    for (const string& val : expression) {
        if (!isOperator(val) && val[0]!= '(' && val[0]!=')') {
            double d1;
            stringstream(val) >> d1;
            operands.push(d1);
        }

        else if (val == "(") { // Comparing string to string so double quotes.
            operators.push('('); // Make it single quotes because it is a char.

        }
        else if (val == ")") {
            //Start evaluating until the ( parenthesis.
            while (!operators.empty() && operators.top() != '(') {
              char op = operators.top();
              operators.pop();
              double operand2 = operands.top();
              operands.pop();
              double operand1 = operands.top();
              operands.pop();




              if (op == '+')
                  operands.push(operand1 + operand2);
              else if (op == '-')
                  operands.push(operand1 - operand2);
              else if (op == '*')
                  operands.push(operand1 * operand2);
              else if (op == '/') {
                  double new_operand = operand2;
                  double result = operand1 / new_operand;
                  operands.push(result);
              }
              else if (op == '%') {
                long new_op1 =  operand1;
                long new_op2 = operand2;
                operands.push(new_op1 % new_op2);
              }
              else if (op == '^')
                  operands.push(pow(operand1,operand2));
          }
          operators.pop(); // Remove the '('
    }
    else if (isOperator(val)) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(val[0])) {
              char op = operators.top();
              operators.pop();
              double operand2 = operands.top();
              operands.pop();
              double operand1 = operands.top();
              operands.pop();




              if (op == '+')
                  operands.push(operand1 + operand2);
              else if (op == '-')
                  operands.push(operand1 - operand2);
              else if (op == '*')
                  operands.push(operand1 * operand2);
              else if (op == '/'){
                  double new_operand = operand2;
                  double result = operand1 / new_operand;
                  operands.push(result);
              }
              else if (op == '%'){
                long new_op1 =  operand1;
                long new_op2 = operand2;
                operands.push(new_op1 % new_op2);
              }
              else if (op == '^')
                  operands.push(pow(operand1,operand2));
          }
          operators.push(val[0]); // Pushes the new operator at the very end so that we can evaluate the one with precedence first.
    }
}
double result = evaluateRemainding(operands, operators);
return result;
}
double Evaluate::evaluateRemainding(stack<double> & operands, stack<char> & operators) {
    while (!operators.empty()) {
      char op = operators.top();
      operators.pop();
      double operand2 = operands.top();
      operands.pop();
      double operand1 = operands.top();
      operands.pop();
      if (op == '+')
          operands.push(operand1 + operand2);
      else if (op == '-')
          operands.push(operand1 - operand2);
      else if (op == '*')
          operands.push(operand1 * operand2);
      else if (op == '/'){
            double new_operand = operand2;
            double result = operand1 / new_operand;
            operands.push(result);
        }
      else if (op == '%'){
            long new_op1 =  operand1;
            long new_op2 = operand2;
            operands.push(new_op1 % new_op2);
              }
      else if (op == '^')
            operands.push(pow(operand1,operand2));
  }

  return operands.top(); // Ending of calculating expression.
}

int main() {
    // Example expression represented as an array of tokens
    //4 * (3 + 2) % 7 - 1
    // (((2 + 3))) + (((1 + 2)))
    // +(-2) * (-3) – ((-4) / (+5))
    // ((5 * 2) - ((3 / 1) + ((4 % 3))))
    vector<string> tokens = {"4", "*", "(", "3", "+", "2", ")", "%", "7", "-", "1"};
    vector<string> token2 = {"2", "^", "3"};
    vector<string> token3 = {"10", "*", "2", "/", "5"};
    vector<string> token4 = {"(", "(", "(", "2", "+", "3", ")", ")", ")", "+", "(",  "(", "(", "1", "+", "2", ")", ")", ")"};
    // This doesn't work. vector <string> token5 = {"+", "(", "-", "2", ")", "*", "(", "-", "3", ")", "-",  "(", "(", "-", "4", ")", "/", "(", "+", "5", ")", ")"};
    vector<string> token5 = {"-2", "+", "1"};
    vector <string> token6 = {"-2", "*", "-3", "-", "(", "-4", "/", "5", ")"};
    vector <string> token7 = {"(", "-2", ")", "*", "(", "-3", ")", "-",  "(", "(", "-4", ")", "/", "(", "+5", ")", ")"};
   //vector <string> token8 = {"-", "(", "+1", ")", "+", "(", "+2", ")"};
   vector <string> token8 = {"8", "-", "(", "5", "-", "2", ")"};
   vector <string> token9 = {"(", "(", "5", "*", "2", ")", "-", "(",  "(", "3", "/", "1", ")", "+", "(", "(", "4", "%", "3", ")", ")", ")", ")"};

  // Evaluate the expression
  Evaluate ex1;
  double result = ex1.evaluateExpression(tokens);
  double result2 = ex1.evaluateExpression(token2);
  double result3 = ex1.evaluateExpression(token3);
  double result4 = ex1.evaluateExpression(token4);
  double result5 = ex1.evaluateExpression(token5);
  double result6 = ex1.evaluateExpression(token6);
  double result7 = ex1.evaluateExpression(token7);
  double result8 = ex1.evaluateExpression(token8);
  double result9 = ex1.evaluateExpression(token9);
  // Output the result
  cout << result << endl;
  cout << result2 << endl;
  cout << result3 << endl;
  cout << result4 << endl;
  cout << result5 << endl;
  cout << result6 << endl;
  cout << result7 << endl;
  cout << result8 << endl;
  cout << result9 << endl;

  return 0;

}