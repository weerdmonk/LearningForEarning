
#include <iostream>
#include <cstring>

using namespace std;

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

/* constants */
const Operator_t operators[] = { { '^', 3, A_RIGHT },
  { '*', 2, A_LEFT },
  { '/', 2, A_LEFT },
  { '+', 1, A_LEFT },
  { '-', 1, A_LEFT },
  //{ '(', 0, A_NONE },
  //{ ')', 0, A_NONE },
  { '\0', 0, A_NONE }
};

const unsigned int num_ops = 5;

struct Parser
{
  /* variables */
  char *str, *output;
  Stack<char> op_stack;

  /* methods */
  Parser(const char *string) : op_stack(strlen(string))
  {
    unsigned int str_len = 0;

    str = const_cast<char*>(string);

    str_len = strlen(str);

    output = new char[str_len];
  }

  ~Parser()
  {

  }

  unsigned int operatorToIdx(char token)
  {
    unsigned int idx = -1;
    switch (token)
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

  bool isNumber(char token)
  {
    bool result = false;

    if ( (token >= 47) &&
        (token <= 58) )
    {
      result = true;
    }
    return result;
  }

  bool isOperator(char token)
  {
    bool result = false;

    for(int i = 0; i < num_ops; i++)
    {
      if (token == operators[i].op)
      {
        result = true;
        break;
      }
    }

    return result;
  }

  /**
   * Algorithm
   * 
   * Read token
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

  void parse()
  {
    unsigned int out_idx = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
      /*
       * TODO; handle invalid inputs
       * TODO: add support for floating point numbers
       * TODO: add support for multi-character operators
       * TODO; add support for common functions
       */

      char token = str[i];

      if ( token == ' ' )
      {
        /* skip whitespaces */
        continue;
      }
      else if ( isOperator(token) == true )
      {
        char *op_top = op_stack.peek();

        while( (op_top != NULL) &&
            (isOperator(*op_top) == true) )
        {
          unsigned int tok_idx = operatorToIdx(token);
          unsigned int top_idx = operatorToIdx(*op_top);

          if ( ( (operators[tok_idx].assoc == A_LEFT) &&
                (operators[tok_idx].prec <= operators[top_idx].prec) ) ||
              ( (operators[tok_idx].assoc == A_RIGHT) &&
                (operators[tok_idx].prec < operators[top_idx].prec) ) )
          {
            op_top = op_stack.pop();
            output[out_idx++] = *op_top;
          }
          else
          {
            break;
          }

          op_top = op_stack.peek();
        }

        op_stack.push(&str[i]);
      }
      else if ( token == '(' )
      {
        op_stack.push(&str[i]);
      }
      else if ( token == ')' )
      {
        char *op_top = op_stack.peek();

        while( (op_top != NULL) &&
            (*op_top != '(') )
        {
          op_top = op_stack.pop();
          output[out_idx++] = *op_top;

          op_top = op_stack.peek();
        }

        op_top = op_stack.pop();
        if ( (op_top == NULL) ||
            (*op_top != '(') )
        {
          cout << "Mismatched ')' found!!\n";
          return;
        }
      }
      else if ( isNumber(token) == true )
      {
        /* token is a number or variable */
        output[out_idx++] = str[i];
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
      char *op_top = op_stack.pop();
      if ( *op_top == '(' )
      {
        cout << "Mismatched '(' found!!\n";
        return;
      }
      output[out_idx++] = *op_top;
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
  cout << "\nSupported operators are: ^, *, /, +, and -\n";
  cout << "Only integers are allowed. Common functions are not supported yet.\n\n";
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
