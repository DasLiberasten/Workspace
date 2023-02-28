%{
open MuLua_syntax
%}

%start <Program.t> program

%%

let program :=
  | ~ = block; EOF;
    <>

let block :=
  | ~ = statement*;
    <>

let statement :=
  | ~ = assignment_statement;
    <>
  | ~ = if_statement;
    <>
  | ~ = if_else_statement;
    <>
  | ~ = while_statement;
    <>
  | ~ = print_statement;
    <>

let assignment_statement :=
  | left = assignable; operator = assignment_operator; right = expression;
    {
      Statement.Assignment { left; operator; right; }
    }

let if_statement :=
  | If; condition = expression; Then; if_block = block; End;
    {
      Statement.If_Statement { condition; if_block; }
    }

let if_else_statement :=
  | If; condition = expression; Then; if_block = block; Else; else_block = block; End;
    {
      Statement.If_Else_Statement { condition; if_block; else_block; }
    } 

let while_statement :=
  | While; condition = expression; Do; cycle = block; End;
    {
      Statement.While_Statement { condition; cycle; }
    } 

let print_statement :=
  | Print; ParenLeft; _print = expression; ParenRight;
    {
      Statement.Print_Statement { _print; }
    } 

let assignable ==
  | ~ = Identifier;
    <>

let assignment_operator ==
  | Equal;
    { Statement.Assignment.AssignmentOperator.Assign }

let expression :=
  | ~ = Identifier;
    <Expression.Identifier>
  | ~ = literal;
    <>
  | ~ = parenthesized_expression;
    <>
  | ~ = binary_expression;
    <>
  | ~ = input_expression;
    <>
  | ~ = unary_expression;
    <>

let literal :=
  | NilLiteral;
    {
      Expression.Literal Expression.Literal.Nil
    }
  | value = BooleanLiteral;
    {
      Expression.Literal (Expression.Literal.Boolean value)
    }
  | value = IntegerLiteral;
    {
      Expression.Literal (Expression.Literal.Integer value)
    }

let binary_expression :=
  | left = expression; operator = binary_operator; right = expression;
  {
    Expression.BinaryExpression {left; operator; right}
  }
  
let binary_operator ==
  | Plus;
    { 
      Expression.BinaryExpression.BinaryOperator.Add 
    }
  | Minus;
    { 
      Expression.BinaryExpression.BinaryOperator.Subtract 
      }
  | Star;
    { 
      Expression.BinaryExpression.BinaryOperator.Multiply 
    }
  | DoubleSlash;
    { 
      Expression.BinaryExpression.BinaryOperator.DivideInteger 
    }
  | EqualEqual;
    { 
      Expression.BinaryExpression.BinaryOperator.Equal 
    }
  | TildeEqual;
    { 
      Expression.BinaryExpression.BinaryOperator.NotEqual 
    }
  | LessEqual;
    { 
      Expression.BinaryExpression.BinaryOperator.LessOrEqual 
    }
  | GreaterEqual;
    { 
      Expression.BinaryExpression.BinaryOperator.GreaterOrEqual 
    }
  | Less;
    { 
      Expression.BinaryExpression.BinaryOperator.Less 
    }
  | Greater;
    { 
      Expression.BinaryExpression.BinaryOperator.Greater 
    }

let parenthesized_expression :=
  | ParenLeft; _expression = expression; ParenRight;
    {
      _expression
    }

let input_expression := 
  | Input; ParenLeft; ParenRight;
    { 
      Expression.InputExpression
    }
  
let unary_expression :=
  | Minus; _expression=expression;
    { 
      Expression.UnaryExpression {_expression}
    }