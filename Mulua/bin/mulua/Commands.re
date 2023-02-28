open Base;

let parse_file = path =>
  path
  |> MuLua_parser.Parser.parse_file
  |> Result.map_error(
       ~f=
         fun
         | `SystemError(message) => Stdio.prerr_endline(message)
         | `SyntaxError({start, current}) =>
           Stdio.eprintf(
             "%s:%d:%d-%d:%d: Syntax error\n",
             path,
             start.pos_lnum,
             start.pos_cnum,
             current.pos_lnum,
             current.pos_cnum,
           ),
     );

let run_file = parse_file %> Result.map(~f=MuLua_semantics.Program.eval);

let print_ast = {
  let to_string = MuLua_syntax.Program.sexp_of_t %> Sexp.to_string_hum;
  parse_file %> Result.map(~f=to_string %> Stdio.print_endline);
};
