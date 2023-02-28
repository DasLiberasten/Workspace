open MuLua_syntax.Expression;

module Literal = {
  let eval: Literal.t => Value.t =
    fun
    | Nil => Nil
    | Boolean(x) => Boolean(x)
    | Integer(x) => Integer(x);
};

let rec eval = (~env=Environment.empty) =>
  fun
  | Literal(x) => x |> Literal.eval
  | Identifier(x) => x |> Environment.get(env)
  | BinaryExpression({left, operator, right}) => {
      let left_part = eval(~env,left);
      let right_part = eval(~env,right);
      switch (left_part, right_part) {
      | (Value.Integer(left_part), Value.Integer(right_part)) =>
        switch (operator) {
        | Add =>      Value.Integer(left_part + right_part)
        | Subtract => Value.Integer(left_part - right_part)
        | Multiply => Value.Integer(left_part * right_part)
        | DivideInteger =>
          switch (right_part) {
          | 0 => failwith("Zero division error")
          | _ => Value.Integer(left_part / right_part)
          }
        | Less =>           Value.Boolean(left_part < right_part)
        | Greater =>        Value.Boolean(left_part > right_part)
        | LessOrEqual =>    Value.Boolean(left_part <= right_part)
        | GreaterOrEqual => Value.Boolean(left_part >= right_part)
        | Equal =>          Value.Boolean(left_part == right_part)
        | NotEqual =>       Value.Boolean(left_part != right_part)
        }
      | _ => switch(operator){
        | Equal => Value.Boolean(left_part == right_part)
        | NotEqual => Value.Boolean(left_part != right_part)
        | _ => failwith("Zero 11 error")
  }; 
      };
  }
  | InputExpression => Value.Integer(Scanf.scanf(" %d", x => x))
  | UnaryExpression({_expression}) => {
      let evaled_expression = eval(~env,_expression);
      switch(evaled_expression){
      | Value.Integer(evaled_expression) => { Value.Integer(-evaled_expression)}   
      | _ => failwith("Unary expression is not implemented for that type")
      }
    };

