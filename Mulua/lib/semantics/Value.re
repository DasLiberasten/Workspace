open Base;

[@deriving (sexp_of, equal)]
type t =
  | Nil
  | Boolean(bool)
  | Integer(int);

let to_string =
  fun
  | Nil => "nil"
  | Boolean(x) => Bool.to_string(x)
  | Integer(x) => Int.to_string(x);

let is_truthy =
  fun
  | Nil => false
  | Boolean(x) => x
  | _ => true;
