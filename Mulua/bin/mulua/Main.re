open Cmdliner;

let () = {
  let commands = {
    let to_exit_status = Result.is_error %> Bool.to_int;

    let program = {
      let doc = "Program path.";
      let docv = "PROGRAM";
      Arg.(required & pos(0, some(string), None) & info([], ~doc, ~docv));
    };

    let run = {
      let doc = "Run the program.";
      Cmd.v(
        Cmd.info("run", ~doc),
        Term.(const(Commands.run_file %> to_exit_status) $ program),
      );
    };

    let ast = {
      let doc = "Print AST of the program.";
      Cmd.v(
        Cmd.info("ast", ~doc),
        Term.(const(Commands.print_ast %> to_exit_status) $ program),
      );
    };

    [run, ast];
  };

  let mulua = {
    let doc = "muLua programming language.";
    let info = Cmd.info("mulua", ~doc);
    let default = Term.(ret(const(`Help((`Auto, None)))));
    Cmd.group(info, ~default, commands);
  };

  mulua |> Cmd.eval' |> exit;
};
