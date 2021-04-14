unit config;

interface

uses sysutils;

type
  config_data = record
    population_size, low_guys, high_guys,
    progeny_size, max_useless_iterations, max_iterations: integer;
    enough_val, epsilon: real;
    debug_mode: boolean;
    selection, crossbreeding, mutation: string;
  end;

function get_data(filename: string): config_data;
procedure print_config(conf: config_data);


implementation

function get_data(filename: string): config_data;
var
  conf: TextFile;
  current_string, config_var, name: string;
  eq_pos, err: integer;
begin
  assign(conf, filename);
  reset(conf);
  get_data.population_size := 30;
  get_data.high_guys := 5;
  get_data.low_guys := 5;
  get_data.progeny_size := 7;
  get_data.max_useless_iterations := 20;
  get_data.max_iterations := 1000;
  get_data.enough_val := 0.230319;
  get_data.debug_mode := false;
  get_data.selection := 'PROPORTIONAL';
  get_data.crossbreeding := 'UNIVERSAL';
  get_data.mutation := 'REVERSE';
  get_data.epsilon := 0.0000001;
  while not eof(conf) do
  begin
    readln(conf, current_string);
    current_string := trim(current_string);{Delete all spaces}
    if current_string[1] = '#' then continue;
    eq_pos := pos('=', current_string);
    if eq_pos = 0 then
    begin
      writeln('Illegal entering information, no "=" in line ', current_string);
      halt;
    end;
    config_var := trim(copy(current_string, 0, eq_pos - 1));
    name := trim(copy(current_string, eq_pos + 1, high(current_string)));
    case config_var of
      'population_size':
        begin
          val(name, get_data.population_size, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about population_size');
            halt;
          end;
        end;
      'high_guys':
        begin
          val(name, get_data.high_guys, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about high_guys');
            halt;
          end;
        end;
      'low_guys':
        begin
          val(name, get_data.low_guys, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about low_guys');
            halt
          end;
        end;
      'progeny_size':
        begin
          val(name, get_data.progeny_size, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about progeny_size');
            halt;
          end;
        end;
      'max_useless_iterations':
        begin
          val(name, get_data.max_useless_iterations, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about max_useless_iterations');
            halt;
          end;
        end;
      'max_iterations':
        begin
          val(name, get_data.max_iterations, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about max_iterations');
            halt;
          end;
        end;
      'enough_val':
        begin
          val(name, get_data.enough_val, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information abuot enough_val');
            halt;
          end;
        end;
      'selection':
        begin
          if  (upcase(name) = 'PROPORTIONAL') or (upcase(name) = 'RANDOM') then
            get_data.selection := upcase(name)
                else
          begin
            writeln('Illegal entering information about selection ', name);
            halt;
          end;
        end;
      'crossbreeding':
        begin
          if (upcase(name) = 'SINGLE') or 
             (upcase(name) = 'DOUBLE') or
             (upcase(name) = 'UNIVERSAL') or
             (upcase(name) = 'UNIFORM') then
            get_data.crossbreeding := upcase(name)
                else
          begin
            writeln('Illegal entering information about crossbreeding ', name);
            halt;
          end;
        end;
      'mutation':
        begin
          if (upcase(name) = 'RANDOM') or 
             (upcase(name) = 'SWITCH') or
             (upcase(name) = 'REVERSE') then
            get_data.mutation := upcase(name)
                else
          begin
            writeln('Illegal entering information about mutation ', name);
            halt;
          end;
        end;
      'epsilon':
        begin
          val(name, get_data.epsilon, err);
          if err <> 0 then
          begin
            writeln('Illegal entering information about epsilon');
            halt;
          end;
        end;
    end;
  end;
end;

procedure print_config(conf: config_data);
begin
  writeln('get_data.population_size = ', conf.population_size);
  writeln('get_data.high_guys = ', conf.high_guys);
  writeln('get_data.low_guys = ', conf.low_guys);
  writeln('get_data.selection = ', conf.selection);
  writeln('get_data.crossbreeding = ', conf.crossbreeding);
  writeln('get_data.mutation = ', conf.mutation);
  writeln('get_data.progeny_size = ', conf.progeny_size);
  writeln('get_data.max_useless_iterations = ', conf.max_useless_iterations);
  writeln('get_data.max_iterations = ', conf.max_iterations);
  writeln('get_data.enough_val = ', conf.enough_val);
  writeln('get_data.epsilon = ', conf.epsilon);
end;

end.

