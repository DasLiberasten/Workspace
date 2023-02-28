open Base;
open MuLua_syntax.Statement;

let rec eval_block = (~env=Environment.empty) =>
  List.fold(~init=env, ~f=env => eval(~env))

and eval = (~env=Environment.empty) =>
  fun
  | Assignment({left, operator: Assign, right}) =>
    env |> Environment.set(~key=left, ~data=right |> Expression.eval(~env))
  | If_Statement({ condition, if_block }) =>{
      let sum_condition = Expression.eval(~env,condition);
      if (Value.is_truthy(sum_condition)){
        eval_block(~env,if_block);
      } else {
        env;
      };
  }
  | If_Else_Statement({ condition, if_block, else_block }) =>{
      let sum_condition = Expression.eval(~env,condition);
      if (Value.is_truthy(sum_condition)){
        eval_block(~env,if_block);
      } else {
        eval_block(~env,else_block);
      };  
  }
  | While_Statement({ condition, cycle }) =>{
      let sum_condition = Expression.eval(~env, condition);
      if (Value.is_truthy(sum_condition)){
        eval(~env=eval_block(~env,cycle),While_Statement({condition, cycle}))
      } else {
        env
      };   
  }
  | Print_Statement({ _print }) =>{
      let sum_print = Expression.eval(~env,_print)
      Stdio.print_endline(Value.to_string(sum_print))
      env;
  }
