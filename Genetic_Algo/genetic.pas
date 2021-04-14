unit genetic;

interface

uses math, binary;

type
  entity = record
    gene: longword;
    val: real;
    F_val: real;
  end;
  
  generation = record
    population: packed array of entity;
    useless_iterations: integer;
    num: integer;
    volume: integer;
    surv: integer;
  end;
  
  progeny = record
    first, second: entity;
  end;
procedure Chto(current: generation; var out_f:text);
procedure Print_entity_file(a:entity; var out_f : text);  
procedure Print_pair_file(a,b:entity; var out_f : text);
procedure init(var ent: entity; gene: longword);
function F(x: real): real;
function check_for_stop_condition(current: generation; max_useless_iterations, max_iterations: integer;
                                                              enough_function_value: real): boolean;
procedure check_for_stop_condition_f(current: generation; max_useless_iterations, max_iterations: integer;
                                                              enough_function_value: real; var out_f: text);                                                                                                                               
procedure random_generation(var current: generation; volume: integer);
procedure print_population(current: generation);
procedure print_population_f(current: generation; var out_f:text);
procedure Selection_proportional(var current: generation; high_guys,
                                low_guys: longint);
procedure Selection_random(var current: generation; high_guys, low_guys: integer);

implementation
procedure Print_entity_file(a:entity; var out_f : text);  
begin
        Print_bit_f(a.gene, out_f);
        writeln(out_f);
end;
procedure Print_pair_file(a,b:entity; var out_f : text);
begin
        Print_bit_f(a.gene, out_f);
        writeln(out_f);
        Print_bit_f(b.gene, out_f);
        writeln(out_f);
end;
procedure init(var ent: entity; gene: longword);
begin
  ent.val := (gene * 4) / power(2, 32);
  ent.F_val := F(ent.val);
end;

function F(x: real): real;
begin
  F := x * (x - 1.1) * (x - 1.1) * (x - 1.1) * (x - 1.1) * (x - 1.1) * 
  (x - 1.2) * (x - 1.2) * (x - 1.2) * (x - 1.2) * (x - 1.3) * (x - 1.3)
   * (x - 1.3) * cos(x + 100);
end;

function check_for_stop_condition(current: generation; max_useless_iterations, max_iterations: integer;
                                                              enough_function_value: real): boolean;
begin
  check_for_stop_condition := false;
  
  if current.num >= max_iterations then
  begin
    writeln('Limit of iterations(', current.num, ')');
    check_for_stop_condition := true;
  end;
  if current.population[low(current.population)].F_val > enough_function_value then
  begin
    writeln('Answer at ', current.num, ' after getting enough accuracy');
    check_for_stop_condition := true;
  end;
  if current.useless_iterations >= max_useless_iterations then
  begin
    writeln('Answer at ', current.num, ' after getting enough valueless iterations');
    check_for_stop_condition := true;
  end;
end;

procedure check_for_stop_condition_f(current: generation; max_useless_iterations, max_iterations: integer;
                                                              enough_function_value: real; var out_f: text);
begin
  if current.num >= max_iterations then
  begin
    writeln(out_f,'Limit of iterations(', current.num, ')');
  end;
  if current.population[low(current.population)].F_val > enough_function_value then
  begin
    writeln(out_f,'Answer at ', current.num, ' after getting enough accuracy');
  end;
  if current.useless_iterations >= max_useless_iterations then
  begin
    writeln(out_f,'Answer at ', current.num, ' after getting enough valueless iterations');
  end;
end;

procedure random_generation(var current: generation; volume: integer);
var
  i: integer;
begin
  current.useless_iterations := 0;
  current.num := 0;
  current.volume := volume;
  current.surv := volume;
  setlength(current.population, volume);
  for i := low(current.population) to high(current.population) do
  begin
    current.population[i].gene := random(high(longword));
    current.population[i].val := (current.population[i].gene * 4) / power(2, 32);
    current.population[i].F_val := F(current.population[i].val);
  end;
end;

procedure print_population(current: generation);
var
  i: integer;
begin
  for i := low(current.population) to high(current.population) do
  begin
    write(i, ': gene = ');
    Print_bit(current.population[i].gene);
    writeln('; val =', current.population[i].val,
       '; F_val =', current.population[i].F_val);
  end;
end;
procedure Chto(current: generation; var out_f:text);
begin
writeln(out_f,'Final score: ', current.population[0].F_val,
                 ' at point ', current.population[0].val);
end;
procedure print_population_f(current: generation; var out_f: text);
var
  i: integer;
begin
  for i := low(current.population) to high(current.population) do
  begin
    write(out_f,i, ': gene = ');
    Print_bit_f(current.population[i].gene, out_f);
    writeln(out_f, '; val =',current.population[i].val,
       '; F_val =', current.population[i].F_val);
  end;
end;

procedure Selection_proportional(var current: generation; high_guys,
                                low_guys: longint);
var
  i, k: longint;
  avr: real;
  new_pop: array of entity;
  entity_flags: array of boolean;
  first_fit, second_fit, first, second: integer;
begin
  setlength(entity_flags, current.volume);
  setlength(new_pop, current.volume);
  k := 0;
  avr := 0;
  for i := 0 to current.volume - 1 do
    avr := avr + current.population[i].F_val;
  
  avr := avr / current.volume;
  
  for i := 0 to high_guys - 1 do
    if i <= high(current.population) then 
    begin
      new_pop[k] := current.population[i];
      k := k + 1;
    end;
  for i := current.volume - low_guys to current.volume - 1 do 
  begin
    new_pop[k] := current.population[i];
    k := k + 1;
  end;
  for i := 1 to (current.volume - (low_guys + high_guys)) div 2 do
  begin
    repeat
      first := random(current.volume - (low_guys +
                                                high_guys)) + high_guys;
    until(entity_flags[first] = false);
    entity_flags[first] := true; 
    repeat
      second := random(current.volume - (low_guys +
                                                high_guys)) + high_guys;
    until(entity_flags[second] = false) and (first <> second);
    entity_flags[second] := true;
    first_fit := round(current.population[first].F_val / avr);
    second_fit := round(current.population[second].F_val / avr);
    if random(first_fit + second_fit) < first_fit then
    begin
      new_pop[k] := current.population[first];
      inc(k);
    end
        else
    begin
      new_pop[k] := current.population[second];
      inc(k);
    end;
  end;
  current.population := new_pop;
  current.surv := k - 1;
  setlength(new_pop, 0);
  setlength(entity_flags, 0);
end;

procedure Selection_random(var current: generation; high_guys, low_guys: integer);
var
  k, i, first, second: integer;
  new_pop: array of entity;
  entity_flags: array of boolean;
begin
  setlength(new_pop, current.volume);
  setlength(entity_flags, current.volume);
  k := 0;
  for i := 0 to high_guys - 1 do
    if i <= high(current.population) then 
    begin
      new_pop[k] := current.population[i];
      k := k + 1;
    end;
  for i := current.volume - low_guys to current.volume - 1 do 
  begin
    new_pop[k] := current.population[i];
    k := k + 1;
  end;
  
  for i := 1 to (current.volume - (low_guys + high_guys)) div 2 do
  begin
    repeat
      first := random(current.volume - (low_guys +
                                                high_guys)) + high_guys;
    until(entity_flags[first] = false);
    entity_flags[first] := true; 
    repeat
      second := random(current.volume - (low_guys +
                                                high_guys)) + high_guys;
    until(entity_flags[second] = false) and (first <> second);
    entity_flags[second] := true;
    
    if random(2) = 1 then
    begin
      new_pop[k] := current.population[first];
      inc(k);
    end
        else
    begin
      new_pop[k] := current.population[second];
      inc(k);
    end;
  end;
  current.population := new_pop;
  current.surv := k - 1;
  setlength(new_pop, 0);
  setlength(entity_flags, 0);
end;
end.
