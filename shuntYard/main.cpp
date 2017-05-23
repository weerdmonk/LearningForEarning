
#include <iostream>
#include <cstring>

using namespace std;

/*
 * TODO: add support for floating point numbers
 */

template<class type> struct Stack
{
  type **array;
  unsigned int capacity, top;

  Stack(int size)
  {
    capacity = size;
    array = new type* [capacity];
    top = 0;
  }

  ~Stack()
  {
    delete[] array;
  }

  bool isEmpty() { return top == 0; }

  bool isFull() { return top == capacity; }

  void push(type *data)
  {
    if (data == NULL)
    {
      return;
    }
    if ( isFull() != true )
    {
      array[top++] = data;
    }
    else
    {
      cout << "Stack is full!\n";
    }
  }

  type* pop()
  {
    type *data = NULL;
    if ( isEmpty() != true )
    {
      data = array[--top];
    }
    else
    {
      cout << "Stack is empty!\n";
    }

    return data;
  }

  type* peek()
  {
    type *data = NULL;
    if ( isEmpty() == true )
    {
      return data;
    }

    data = array[top - 1];
    return data;
  }
};


template<class type> struct Queue
{
  type **array;
  unsigned int capacity, front, rear, size;

  Queue(int _capacity)
  {
    capacity = _capacity;
    array = new type* [capacity];
    front = size = 0;
    rear = capacity - 1;
  }

  ~Queue()
  {
    delete[] array;
  }

  bool isEmpty() { return size == 0; }

  bool isFull() { return size == capacity; }

  void enqueue(type *data)
  {
    if (data == NULL)
    {
      return;
    }

    if ( isFull() == true )
    {
      cout << "Queue is full!\n";
      return;
    }

    rear = ++rear % capacity;
    array[rear] = data;
    ++size;
  }

  type* dequeue()
  {
    type *data = NULL;

    if ( isEmpty() == true )
    {
      cout << "Queue is empty!\n";
      return data;
    }

    data = array[front];
    front = ++front % capacity;
    --size;

    return data;
  }

};

typedef unsigned int Precedence_t;

enum Associativity_t
{
  A_NONE = 0,
  A_LEFT,
  A_RIGHT
};

struct Operator_t
{
  char op;
  Precedence_t prec;
  Associativity_t assoc;
};

struct Function_t
{
  char const *func;
  unsigned int len;
};

const char func_arg_separator = ',';

enum Token_Type_t
{
  T_OP = -1,
  T_FUNC
};

struct Token_t
{
  Token_Type_t type;
  union _token
  {
    Operator_t op;
    Function_t func;
  } token;
};

/* constants */

const unsigned int num_ops = 5;

const unsigned int num_funcs = 16;

# define left_parenthesis_idx   num_ops + num_funcs
# define right_parenthesis_idx  num_ops + num_funcs + 1

const Token_t tokens[] = {
  { T_OP, { .op = {'^', 3, A_RIGHT } } },
  { T_OP, { .op = {'*', 2, A_LEFT } } },
  { T_OP, { .op = {'/', 2, A_LEFT } } },
  { T_OP, { .op = {'+', 1, A_LEFT } } },
  { T_OP, { .op = {'-', 1, A_LEFT } } },
  { T_FUNC, { .func = {"min", 3 } } },
  { T_FUNC, { .func = {"max", 3 } } },
  { T_FUNC, { .func = {"mod", 3 } } },
  { T_FUNC, { .func = {"abs", 3 } } },
  { T_FUNC, { .func = {"sin", 3 } } },
  { T_FUNC, { .func = {"cos", 3 } } },
  { T_FUNC, { .func = {"tan", 3 } } },
  { T_FUNC, { .func = {"cot", 3 } } },
  { T_FUNC, { .func = {"sec", 3 } } },
  { T_FUNC, { .func = {"csc", 3 } } },
  { T_FUNC, { .func = {"arcsin", 6 } } },
  { T_FUNC, { .func = {"arccos", 6 } } },
  { T_FUNC, { .func = {"arctan", 6 } } },
  { T_FUNC, { .func = {"arccot", 6 } } },
  { T_FUNC, { .func = {"arctan", 6 } } },
  { T_FUNC, { .func = {"arcsec", 6 } } },
  { T_OP, { .op = {'(', 0, A_NONE } } },
  { T_OP, { .op = {')', 0, A_NONE } } }
};

struct Parser
{
  /* variables */
  char *str, *output;
  Stack<Token_t> op_stack;

  /* methods */
  Parser(const char *string) : op_stack(strlen(string))
  {
    str = const_cast<char*>(string);
    output = new char[strlen(str)];
  }

  ~Parser()
  {
    delete[] output;
  }

  unsigned int operatorToIdx(char *tok_str)
  {
    unsigned int idx = -1;
    if (tok_str == NULL)
    {
      return idx;
    }

    switch (*tok_str)
    {
      case '^':
        idx = 0;
        break;
      case '*':
        idx = 1;
        break;
      case '/':
        idx = 2;
        break;
      case '+':
        idx = 3;
        break;
      case '-':
        idx = 4;
        break;
      default:
        ;;
    }

    return idx;
  }

#define ascii_zero  48
#define ascii_nine  57

  bool isNumber(char *tok_str)
  {
    bool result = false;
    if (tok_str == NULL)
    {
      return result;
    }

    if ( (*tok_str>= 48) &&
        (*tok_str <= 57) )
    {
      result = true;
    }
    return result;
  }

  bool isOperator(char *tok_str)
  {
    bool result = false;
    if (tok_str == NULL)
    {
      return result;
    }

    for(int i = 0; i < num_ops; i++)
    {
      if (*tok_str == tokens[i].token.op.op)
      {
        result = true;
        break;
      }
    }

    return result;
  }

  bool isFunction(char* tok_str, unsigned int *tok_len, unsigned int *tok_idx)
  {
    bool result = false;

    for(int i = num_ops; i < num_ops + num_funcs; i++)
    {
      if ( strncmp(tok_str, tokens[i].token.func.func, tokens[i].token.func.len) == 0 )
      {
        result = true;
        if (tok_len != NULL)
        {
          *tok_len = tokens[i].token.func.len;
        }
        if (tok_idx != NULL)
        {
          *tok_idx = i;
        }
        break;
      }
    }

    return result;
  }

  /**
   * Algorithm
   *
   * Read token
   * If token is a function
   *  push function onto op_stack
   * If token is argument separator
   *  until token at top of op_stack is (
   *    pop tokens off op_stack and enqueue to output
   * If token is an operator o1
   *  while there is an operator o2 at top of op_stack and either
   *  o1 is left associative and has precedence <= o2 or
   *  o1 is right associative and has precedence < o2
   *    pop o2 off op_stack and enqueue to output
   *  push o1 onto op_stack
   * If token is (
   *  push onto op_stack
   * If token is )
   *  until token at top of op_stack is (
   *    pop tokens off op_stack and enqueue to output
   *  Pop off left ( from op_stack but dont enqueue to output
   * If token is a number
   *  Enqueue to output
   * If no more tokens are left to read
   *  Pop token(s) off op_stack and enqueue to output
   *
   */

#define output_add_space()  output[out_idx++] = ' '

  void parse()
  {
    unsigned int out_idx = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
      char token = str[i];
      unsigned int func_len, func_idx;

      if ( token == ' ' )
      {
        /* skip whitespaces */
        continue;
      }
      else if ( isFunction(&str[i], &func_len, &func_idx) == true )
      {
        op_stack.push(const_cast<Token_t*>(&tokens[func_idx]));
        i += func_len - 1;
      }
      else if ( token == func_arg_separator )
      {
        Token_t *op_top = op_stack.peek();

        while( (op_top != NULL) &&
            (op_top->token.op.op != '(') )
        {
          op_top = op_stack.pop();
          output[out_idx++] = op_top->token.op.op;
          output_add_space();

          op_top = op_stack.peek();
        }

        if ( (op_top == NULL) ||
            (op_top->token.op.op != '(') )
        {
          cout << "Mismatched ')' found!!\n";
          return;
        }
      }
      else if ( isOperator(&str[i]) == true )
      {
        unsigned int tok_idx = operatorToIdx(&str[i]);
        Token_t *op_top = op_stack.peek();

        while( (op_top != NULL) &&
               (isOperator(&(op_top->token.op.op)) == true) )
        {
          unsigned int top_idx = operatorToIdx(&(op_top->token.op.op));

          if ( ( (tokens[tok_idx].token.op.assoc == A_LEFT) &&
                (tokens[tok_idx].token.op.prec <= tokens[top_idx].token.op.prec) ) ||
              ( (tokens[tok_idx].token.op.assoc == A_RIGHT) &&
                (tokens[tok_idx].token.op.prec < tokens[top_idx].token.op.prec) ) )
          {
            op_top = op_stack.pop();
            output[out_idx++] = op_top->token.op.op;
            output_add_space();
          }
          else
          {
            break;
          }

          op_top = op_stack.peek();
        }

        op_stack.push(const_cast<Token_t*>(&tokens[tok_idx]));
      }
      else if ( token == '(' )
      {
        op_stack.push(const_cast<Token_t*>(&tokens[left_parenthesis_idx]));
      }
      else if ( token == ')' )
      {
        Token_t *op_top = op_stack.peek();

        while( (op_top != NULL) &&
            (op_top->token.op.op != '(') )
        {
          op_top = op_stack.pop();
          output[out_idx++] = op_top->token.op.op;
          output_add_space();

          op_top = op_stack.peek();
        }

        op_top = op_stack.pop();
        if ( (op_top == NULL) ||
             (op_top->token.op.op != '(') )
        {
          cout << "Mismatched ')' found!!\n";
          return;
        }

        op_top = op_stack.peek();
        if ( (op_top != NULL) &&
             (op_top->type == T_FUNC) )
        {
          op_top = op_stack.pop();
          for (int i = 0; i < op_top->token.func.len; i++)
          {
            output[out_idx++] = op_top->token.func.func[i];
          }
          output_add_space();
        }
      }
      else if ( isNumber(&str[i]) == true )
      {
        /* token is a number or variable */
        output[out_idx++] = str[i];
        output_add_space();
      }
      else
      {
        cout << "Invalid input data!!\n";
        return;
      }

    }

    /* pop all operators from op_stack and enqueue to output */
    while ( op_stack.isEmpty() != true )
    {
      Token_t *op_top = op_stack.pop();
      if ( op_top->token.op.op == '(' )
      {
        cout << "Mismatched '(' found!!\n";
        return;
      }
      if (op_top->type == T_OP)
      {
        output[out_idx++] = op_top->token.op.op;
        output_add_space();
      }
      else if (op_top->type == T_FUNC)
      {
        for (int i = 0; i < op_top->token.func.len; i++)
        {
          output[out_idx++] = op_top->token.func.func[i];
        }
      }
    }

    /* append null character to output string */
    output[out_idx] = '\0';

    /* print input and output strings */
    cout << "Input: " << str << '\n';
    cout << "Output: " << output << '\n';
  }

};

void print_help(const char* binary_path)
{
  cout << "Usage: " << binary_path << " {expression string to parse}\n";
  cout << "\nSupported operators:\n" \
                                 "  ^, *, /, +, -\n";
  cout << "Supported functions:\n" \
                                "  min, max,\n" \
                                "  mod, abs,\n" \
                                "  sin, cos,\n" \
                                "  tan, cot,\n" \
                                "  sec, csc,\n" \
                                "  arcsin, arccos,\n" \
                                "  arctan, arccot,\n" \
                                "  arcsec, arccsc,\n";
  cout << "\nOnly integers are allowed.\n";
}

int main(int argc, char** argv)
{
/*
  int *d1 = new int;
  *d1 = 10;
  int *d2 = new int;
  *d2 = 20;
  int *d3 = new int;
  *d3 = 30;
  int *d4 = new int;
  *d4 = 40;
  int *d5 = new int;
  *d5 = 50;
  int *d6 = new int;
  *d6 = 60;

  int *data;

  Stack<int> s(3);

  s.push(d1);
  s.push(d2);
  s.push(d3);

  data = s.pop();
  if (data) cout << *data << "\n";
  data = s.pop();
  if (data) cout << *data << "\n";
  data = s.pop();
  if (data) cout << *data << "\n";
  data = s.pop();

  cout << "**************\n";

  Queue<int> q(3);

  q.enqueue(d1);
  q.enqueue(d2);
  q.enqueue(d3);
  q.enqueue(d4);

  data = q.dequeue();
  if (data) cout << *data << "\n";
  data = q.dequeue();
  if (data) cout << *data << "\n";
  data = q.dequeue();
  if (data) cout << *data << "\n";
  data = q.dequeue();

  q.enqueue(d4);
  q.enqueue(d5);
  q.enqueue(d6);

  data = q.dequeue();
  if (data) cout << *data << "\n";

  q.enqueue(d1);
  q.enqueue(d2);

  data = q.dequeue();
  if (data) cout << *data << "\n";
  data = q.dequeue();
  if (data) cout << *data << "\n";
  data = q.dequeue();
  if (data) cout << *data << "\n";
  data = q.dequeue();

  cout << "**************\n";

  delete d1, d2, d3, d4, d5, d6;
*/

  if (argc != 2)
  {
    print_help(argv[0]);
    return 0;
  }

  Parser shuntYard(argv[1]);

  shuntYard.parse();

  return 0;
}
