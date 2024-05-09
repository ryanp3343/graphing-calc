#include "shuntingyard.h"
#include "string"


void shuntingyard::userInput(std::string str) {

    //default string when graph runs
    if (str == "")
    {
        _expression = "x";
    }
    //when new string is entered
    else
    {
        _expression = str;
    }
}

Queue<Token*> shuntingyard::Tokenize()
{
    //Queue for token and chars
    Queue<Token*> tokens;
    Queue<char> chars;
    bool unary = false;

    //pushes string into queue
    for (int i = 0; i < _expression.size(); i++)
    {
        if (_expression.at(i) != ' ')
        {
            chars.push(_expression.at(i));
        }
    }

    Token* prev = nullptr;
    Token* function = nullptr;
    Token* unaryToken = nullptr;

    while (!chars.empty())
    {
        std::string str = "";
        //gets first charater of queue
        str += chars.pop();

        //if is a variable or trig function
        if (isalpha(str.at(0)))
        {
            if (prev != nullptr && prev->get_type() == TokenTypes::Integer)
            {
                //add * when there is a variable
                prev = new Operator('*');
                tokens.push(prev);
                //push closing paranthesis if unary is true
                if (unary)
                {
                    unaryToken = new Operator(')');
                    tokens.push(unaryToken);
                    unary = false;
                }
            }
            //if the char is a var or trig function
            if (chars.empty() || !isalpha(*chars.Begin()))
            {
                //add the variable
                function = new Var(str.at(0));
            }
            else
            {
                while (!chars.empty() && isalpha(*chars.Begin()))
                {
                    //add the trig fucntion
                    str += chars.pop();
                }
                function = new TrigFunction(str);
            }
            tokens.push(function);
            //push closing paranthesis if unary is true
            if (unary)
            {
                unaryToken = new Operator(')');
                tokens.push(unaryToken);
                unary = false;
            }
            prev = function;

        }
        //the char is a digit
        else if (isdigit(str.at(0)))
        {
            //checks if is a digit and if there is a . for decimals
            while (!chars.empty() && (isdigit(*chars.Begin()) || *chars.Begin() == '.'))
            {
                //adds the number to str
                str += chars.pop();
            }
            Token* num = new Integer(atof(str.c_str()));
            tokens.push(num);
            //push closing paranthesis if unary is true
            if (unary)
            {
                unaryToken = new Operator(')');
                tokens.push(unaryToken);
                unary = false;
            }
            prev = num;

        }
        //not a number or var or trig,adds a operator
        //if the prev token is not number or a var its negative
        else
        {
            if ((prev == nullptr || (prev->get_type() != TokenTypes::Integer && prev->get_type() != TokenTypes::Variable)) && str.at(0) == '-')
            {
                tokens.push(new Integer(-1));
                tokens.push(new Operator('*'));
                prev = new Operator('(');
                unary = true;
            }
            //else its minus
            else
            {
                prev = new Operator(str.at(0));
            }
            tokens.push(prev);
        }


    }
    return tokens;


}

Queue<Token*> shuntingyard::toPostFix(Queue<Token*> infix) {
    Queue<Token*> postfix;
    Stack<Token*> operStack;

    while (!infix.empty()) {
        Token* token = infix.pop();

        switch (token->get_type()) {
        case TokenTypes::Variable:
        case TokenTypes::Integer:
            // Directly add numbers and variables to the output queue
            postfix.push(token);
            break;

        case TokenTypes::Function:
            // Functions go directly onto the operator stack
            operStack.push(token);
            break;

        case TokenTypes::Operator: {
            Operator* oper = static_cast<Operator*>(token);

            if (oper->get_sym() == '(') {
                // Opening parenthesis goes onto the stack
                operStack.push(oper);
            }
            else if (oper->get_sym() == ')') {
                // Pop to postfix until we find the matching '('
                while (!operStack.empty() &&
                    static_cast<Operator*>(*operStack.begin())->get_sym() != '(') {
                    postfix.push(operStack.pop());
                }
                // Pop the '(' itself
                delete operStack.pop();

                // If there's a function on top of the stack, pop that too
                if (!operStack.empty() && (*operStack.begin())->get_type() == TokenTypes::Function) {
                    postfix.push(operStack.pop());
                }
            }
            else {
                // Handle other operators
                while (!operStack.empty() &&
                    (*operStack.begin())->get_type() == TokenTypes::Operator &&
                    static_cast<Operator*>(*operStack.begin())->prec() >= oper->prec()) {
                    postfix.push(operStack.pop());
                }
                operStack.push(oper);
            }
            break;
        }
        }
    }

    // Pop all remaining operators to the postfix queue
    while (!operStack.empty()) {
        Token* op = operStack.pop();
        if (op->get_sym() != '(' && op->get_sym() != ')') {
            postfix.push(op);
        }
        else {
            delete op; // Cleanup unmatched parentheses
        }
    }
    //std::cout << postfix << std::endl;
    return postfix;
}





double shuntingyard::Evaluate(Queue<Token*> postfix, double num) {
    Stack<Token*> resultStack;

    // Ensure that the postfix expression isn't empty before evaluating
    if (postfix.empty()) {
        std::cerr << "Evaluation Error: Postfix expression is empty." << std::endl;
        return 0; // Or a specific error value
    }

    try {
        while (!postfix.empty()) {
            Token* tok = postfix.pop();
            switch (tok->get_type()) {
            case TokenTypes::Operator: {
                Operator* operTok = static_cast<Operator*>(tok);

                // Make sure two values are available for the operation
                if (resultStack.empty()) {
                    std::cerr << "Evaluation Error: Missing operand for the operation." << std::endl;
                    return 0; // Error state
                }

                Integer* right = static_cast<Integer*>(resultStack.pop());

                if (resultStack.empty()) {
                    std::cerr << "Evaluation Error: Missing operand for the operation." << std::endl;
                    return 0; // Error state
                }

                Integer* left = static_cast<Integer*>(resultStack.pop());

                // Calculate the operation result
                resultStack.push(new Integer(operTok->calc_op(left->get_Num(), right->get_Num())));
                break;
            }

            case TokenTypes::Integer:
                resultStack.push(tok);
                break;

            case TokenTypes::Variable:
                resultStack.push(new Integer(num));
                break;

                // Example check within `TokenTypes::Function`:
            case TokenTypes::Function: {
                TrigFunction* funcTok = static_cast<TrigFunction*>(tok);
                if (resultStack.empty()) {
                    std::cerr << "Evaluation Error: Missing operand for the function." << std::endl;
                    return 0; // Error state
                }
                Integer* operand = static_cast<Integer*>(resultStack.pop());
                resultStack.push(new Integer(funcTok->doTrig(operand->get_Num())));
                delete operand;  // Avoid memory leak by deleting used operands
                break;
            }

            }
            //std::cout << resultStack << std::endl;
        }

        // Check if there are extra operands or if the result is missing
        if (resultStack.empty()) {
            std::cerr << "Evaluation Error: No result after evaluation." << std::endl;
            return 0; // Error state
        }

        Token* result = resultStack.pop();
        double resultNum = static_cast<Integer*>(result)->get_Num();
        delete result;

        //std::cout << resultNum << std::endl;
        return resultNum;
        
    }
    catch (const std::exception& e) {
        std::cerr << "Evaluation Error: " << e.what() << std::endl;
        return 0; // Error state
    }
}
