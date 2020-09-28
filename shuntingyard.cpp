#include "shuntingyard.h"
#include "string"


void shuntingyard::userInput(string str){

        //default string when graph runs
        if(str=="")
        {
            _expression="x";
        }
        //when new string is entered
        else
        {
            _expression=str;
        }
}

Queue<Token*> shuntingyard::Tokenize()
{
    //Queue for token and chars
    Queue<Token*> tokens;
    Queue<char> chars;
    bool unary=false;

    //pushes string into queue
    for(int i=0; i<_expression.size(); i++)
    {
        if(_expression.at(i) != ' ')
        {
            chars.push(_expression.at(i));
        }
    }

    Token* prev=nullptr;
    Token* function=nullptr;
    Token* unaryToken=nullptr;

    while(!chars.empty())
    {
        string str="";
        //gets first charater of queue
        str+=chars.pop();

        //if is a variable or trig function
        if(isalpha(str.at(0)))
        {
            if(prev !=nullptr && prev->get_type()==_int)
            {
                //add * when there is a variable
                prev=new Operator('*');
                tokens.push(prev);
                //push closing paranthesis if unary is true
                if(unary)
                {
                   unaryToken=new Operator(')');
                   tokens.push(unaryToken);
                   unary=false;
                }
            }
            //if the char is a var or trig function
            if(chars.empty() || !isalpha(*chars.Begin()))
            {
                //add the variable
                function=new var(str.at(0));
            }
            else
            {
                while(!chars.empty() && isalpha(*chars.Begin()))
                {
                    //add the trig fucntion
                    str+=chars.pop();
                }
                function=new TrigFunction(str);
            }
            tokens.push(function);
            //push closing paranthesis if unary is true
            if(unary)
            {
               unaryToken=new Operator(')');
               tokens.push(unaryToken);
               unary=false;
            }
            prev=function;

        }
        //the char is a digit
        else if(isdigit(str.at(0)))
        {
            //checks if is a digit and if there is a . for decimals
            while(!chars.empty() && (isdigit(*chars.Begin()) || *chars.Begin()=='.'))
            {
                //adds the number to str
                str+= chars.pop();
            }
            Token* num= new Integer(atof(str.c_str()));
            tokens.push(num);
            //push closing paranthesis if unary is true
            if(unary)
            {
               unaryToken=new Operator(')');
               tokens.push(unaryToken);
               unary=false;
            }
            prev=num;

        }
        //not a number or var or trig,adds a operator
        //if the prev token is not number or a var its negative
        else
        {
            if((prev==nullptr || (prev->get_type() != _int && prev->get_type() != _variable)) && str.at(0)=='-')
            {
                tokens.push(new Integer(-1));
                tokens.push(new Operator('*'));
                prev=new Operator('(');
                unary=true;
            }
            //else its minus
            else
            {
                prev=new Operator(str.at(0));
            }
            tokens.push(prev);
        }


    }
    return tokens;


}

Queue<Token*> shuntingyard::toPostFix(Queue<Token *> infix)
{
    //queue for final postfix and stack for temporary operators
    Queue<Token*> postfix;
    Stack<Token*> operStack;


    while(!infix.empty())
    {
        //takes first token from infix queue
        Token* token=infix.pop();


        switch(token->get_type())
        {
            case _variable:
                //type is variable always push to queue
                postfix.push(token);


            break;

            case _int:
                //type is a number always push to queue
                postfix.push(token);


            break;

            case _function:
                //type is a function always push to stack
                operStack.push(token);
            break;

            case _operator:
                //type is operator compare precedence
                Operator* oper= static_cast<Operator*>(token);

                //default value of -1 means its a parenthesis
                if(oper->prec()==-1)
                {
                    //operator is a parenthesis push to stack
                    operStack.push(oper);
                }
                else if(!operStack.empty())
                {
                    Token * topOf = *(operStack.begin());
                    //while the top of the stacks value is greater or equal to
                    while(!operStack.empty() && topOf->get_type()==_operator && static_cast<Operator*>(topOf)->prec() >= oper->prec())
                    {
                        //do nothing with parenthesis
                        if(static_cast<Operator*>(topOf)->prec()==-1)
                        {
                            break;
                        }
                        //push the popped stack to the queue
                        postfix.push(operStack.pop());
                        if(!operStack.empty())
                        {
                            //change top of stack since it was popped
                            topOf=*(operStack.begin());
                        }
                    }
                    //push to operator to stack
                    operStack.push(oper);
                }
                else
                {   //precedence is less than so push to stack
                    operStack.push(oper);
                }

                //when its closed parenthesis
                if(oper->get_sym()==')')
                {
                    //delete the parentheis
                    delete operStack.pop();
                    //change topof stack
                    Token * topOf = *(operStack.begin());
                    while(!operStack.empty() && topOf->get_type()==_operator && static_cast<Operator*>(topOf)->get_sym()!='(')
                    {
                        //push to queue in between open and closed parenthesis
                        postfix.push(operStack.pop());
                        topOf=*(operStack.begin());
                    }
                    delete operStack.pop();
                    topOf=*(operStack.begin());
                    //if trig functions are inside of the parenthesis push
                    if(topOf->get_type()==_function)
                    {
                        postfix.push(operStack.pop());
                    }
                }
            break;
        }
    }

    //catches the rest of the infix queue and pushes it
    while(!operStack.empty())
    {
        Token* op=static_cast<Operator*>(operStack.pop());
        if(op->get_sym()!='(' && op->get_sym() != ')')
        {
            postfix.push(op);
        }
        else
            delete op;
    }

    return postfix;

}


double shuntingyard::Evaluate(Queue<Token *> postfix, double num)
{
    //stack of y values
        Stack<Token*> resultStack;
        while(!postfix.empty())
        {
            //get first item of postfix
            Token* tok=postfix.pop();
            switch (tok->get_type())
            {
            //type is operator
            case _operator:{
                Operator* operTok=static_cast<Operator*>(tok);
                //takes the next two values of postfix queue
                Integer* right=static_cast<Integer*>(resultStack.pop());
                Integer* left=static_cast<Integer*>(resultStack.pop());
                //pushes the result integer from the two popped items
                resultStack.push(new Integer(operTok->calc_op(left->get_Num(),right->get_Num())));
                break;
            }

            case _int:
                //push number to stack
                resultStack.push(tok);
                break;

            case _variable:
                //push variable to stack
                resultStack.push(new Integer(num));
                break;

            case _function:

                TrigFunction* functok=static_cast<TrigFunction*>(tok);
                Integer* var=static_cast<Integer*>(resultStack.pop());
                //pops result stack to do trig fucntion on that
                //does trig math on trig token
                resultStack.push(new Integer(functok->doTrig(var->get_Num())));
                break;
            }
        }
        //pops stack to get the evaluated number
        Token* result=resultStack.pop();
        double resultNum=static_cast<Integer*>(result)->get_Num();
        delete result;
        return resultNum;
}


void shuntingyard::test()
{

//    string user;
//    cout<<"EXP"<<endl;
//    getline(cin,user);
//    Queue<Token*>g;
//    g=Tokenize();
//    Queue<Token*>f;
//    f=toPostFix(g);
//    Evaluate(f,1);



}

