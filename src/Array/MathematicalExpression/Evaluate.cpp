//
// Created by Olcay Taner YILDIZ on 22.03.2023.
//

#include "Element.h"
#include "Stack.h"
#include <iostream>

using namespace std;

void infixToPostFix(Element *infixExpression, int size) {
    Token e1;
    Stack c = Stack(100);
    for (int i = 0; i < size; i++) {
        Token e = infixExpression[i].getData();
        if (e.getType() == TokenType::OPERAND) {
            cout << e.getOperand() << " ";
        } else {
            if (e.getOperand() == '(') {
                c.push(infixExpression[i]);
            } else {
                if (e.getOperand() == ')') {
                    e1 = c.pop().getData();
                    while (e1.getOperator() != '(') {
                        cout << e1.getOperator() << " ";
                        e1 = c.pop().getData();
                    }
                } else {
                    while (!c.isEmpty() && e.getPrecedence() <= c.peek().getData().getPrecedence()) {
                        e1 = c.pop().getData();
                        cout << e1.getOperator() << " ";
                    }
                    c.push(infixExpression[i]);
                }
            }
        }
    }
    while (!c.isEmpty()) {
        e1 = c.pop().getData();
        cout << e1.getOperator() << " ";
    }
}

Element eval(char ch, int operand1, int operand2) {
    int result = 0;
    switch (ch) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
    }
    return Element(Token(result));
}

int evaluate(Element *postfixExpression, int size) {
    Stack c = Stack(100);
    for (int i = 0; i < size; i++) {
        Token e = postfixExpression[i].getData();
        switch (e.getType()) {
            case OPERAND:
                c.push(postfixExpression[i]);
                break;
            case OPERATOR:
                Element e2 = c.pop();
                Element e1 = c.pop();
                Element result = eval(e.getOperator(),
                                      e1.getData().getOperand(), e2.getData().getOperand());
                c.push(result);
                break;
        }
    }
    Element e = c.pop();
    return e.getData().getOperand();
}