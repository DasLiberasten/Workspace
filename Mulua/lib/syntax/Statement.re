open Base;

%gen
module rec Statement: {
  [@deriving sexp]
  type t =
    | Assignment(Assignment.t)
    | If_Statement(If_Statement.t)
    | If_Else_Statement(If_Else_Statement.t)
    | While_Statement(While_Statement.t)
    | Print_Statement(Print_Statement.t);
} = Statement

and Block: {
  [@deriving sexp]
  type t = list(Statement.t);
} = Block

and Assignment: {
  module AssignmentOperator: {
    [@deriving sexp]
    type t =
      | Assign;
  };

  [@deriving sexp]
  type t = {
    left: Identifier.t,
    operator: AssignmentOperator.t,
    right: Expression.t,
  };
} = Assignment

and If_Statement: {
  [@deriving sexp]
  type t = {
    condition: Expression.t,
    if_block: Block.t,
  };
} = If_Statement

and If_Else_Statement: {
  [@deriving sexp]
  type t = {
    condition: Expression.t,
    if_block: Block.t,
    else_block: Block.t,
  };
} = If_Else_Statement

and While_Statement: {
  [@deriving sexp]
  type t = {
    condition: Expression.t,
    cycle: Block.t,
  };
} = While_Statement

and Print_Statement: {
  [@deriving sexp]
  type t = {
    _print: Expression.t,
  };
} = Print_Statement;

include Statement;
