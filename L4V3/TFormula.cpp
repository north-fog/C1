#include "TStack.h" 
#include "TFormula.h" 
#include <cstring>




bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isBracket(char c) {
    return c == '(' || c == ')';
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}



TFormula::TFormula(char form[]){
    int i=0;
    while (form[i] != '\0' && i < MaxLength - 1) {
        Formula[i] = form[i];
        i++;
    }
    Formula[i] = '\0';
    PostfixForm[0] = '\0';
};

int TFormula::FormulaChecker(int Brackets[],int size){
    int len = strlen(Formula);
    int errorcount = 0;
    TStack stack(MaxLength);
    for(int i=0; i<len; i++){
        if (Formula[i]=='('){
            stack.Put(i);
        }
        else if (Formula[i]==')'){
            if(stack.IsEmpty()){
                Brackets[errorcount]=i; 
                errorcount++;
    }       else {
                stack.Get();  
    }
}
    }
    while (!stack.IsEmpty()) {
        Brackets[errorcount] = stack.Get();
        errorcount++;
    }
    return errorcount;   

};

int TFormula::FormulaConverter(void){
    int len = strlen(Formula);
    TStack stack(MaxLength);
    int postfixindex = 0;
       for (int i = 0; i < len; i++) {
        char c = Formula[i];

        if (c == ' ') continue;
        
        if (isDigit(c) ) {
            while (i < len && (isDigit(Formula[i]))) {
                PostfixForm[postfixindex++] = Formula[i++];
            }
            PostfixForm[postfixindex++] = ' ';
            i--;

        }
        //открывающая скобка
        else if (c == '(') {
            stack.Put(c);

        }
        //закрывающая скобка
        else if (c == ')') {
            while (!stack.IsEmpty() && stack.Peek() != '(') {
                PostfixForm[postfixindex++] = stack.Get();
                PostfixForm[postfixindex++] = ' ';
            }
            if (!stack.IsEmpty()) {
                stack.Get();  
            }
        } 
        //операторы
        else if (isOperator(c)) {
            while (!stack.IsEmpty() && isOperator(stack.Peek()) && priority(stack.Peek()) >= priority(c)) {
                PostfixForm[postfixindex++] = stack.Get();
                PostfixForm[postfixindex++] = ' ';
            }
            stack.Put(c);

        }
    }
    
    while (!stack.IsEmpty()) {
                PostfixForm[postfixindex++] = stack.Get();
                PostfixForm[postfixindex++] = ' ';
    }
    
    if (postfixindex > 0 && PostfixForm[postfixindex - 1] == ' ') {
        PostfixForm[postfixindex - 1] = '\0';
    }
    else {
        PostfixForm[postfixindex] = '\0';
    }
    
    return 0; 
} 
double TFormula::FormulaCalculator() {
    TStack stack(MaxLength);
    int len = strlen(PostfixForm);
    
    for (int i = 0; i < len; i++) {
        char c = PostfixForm[i];
        
        if (c == ' ') continue;
        
        if (isDigit(c)) {
            int num = 0;
            while (i < len && isDigit(PostfixForm[i])) {
                num = num * 10 + (PostfixForm[i] - '0');
                i++;
    }
            i--;  
            stack.Put(num);
}
        else if (isOperator(c)) {
            double b = stack.Get();
            double a = stack.Get();
            double result = 0.0;
            
            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            stack.Put(result);
        }
    }
    
    return stack.Get();
}
    

