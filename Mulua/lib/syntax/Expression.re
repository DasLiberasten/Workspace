open Base;

module Literal = {
  [@deriving sexp]
  type t =
    | Nil
    | Boolean(bool)
    | Integer(int);
};

%gen
module rec Expression: {
  [@deriving sexp]
  type t =
    | Identifier(Identifier.t)
    | Literal(Literal.t)
    | BinaryExpression(BinaryExpression.t)
    | InputExpression
    | UnaryExpression(UnaryExpression.t)  
} = Expression

and BinaryExpression: {
  module BinaryOperator: {
    [@deriving sexp]
    type t =
      | Add
      | Subtract
      | Multiply
      | DivideInteger
      | Equal
      | NotEqual
      | Less
      | LessOrEqual
      | Greater
      | GreaterOrEqual;
  };

  [@deriving sexp]
  type t = {
    left: Expression.t,
    operator: BinaryOperator.t,
    right: Expression.t,
  };
} = BinaryExpression

and UnaryExpression: {

  [@deriving sexp]
  type t = {
    _expression: Expression.t,
  };
} = UnaryExpression;

include Expression;
