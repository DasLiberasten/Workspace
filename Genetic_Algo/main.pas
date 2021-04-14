program genetic_algorithm;
uses genetic, math, binary, config, tort, dos;

var
  current_generation: generation;
  cur_progeny, prom_progeny: progeny;
  rd1, rd2, point, bit1, bit2: byte;
  i, j, first, second, third, fourth, mut_ent, lo, hi, Fin_time: integer;
  prev_best: real;
  debug: char;
  out_f, read_f : text;
  conf: config_data;
  mask, mutant: longword;
  flag:boolean;
  s : string;
  H1, M1, S1, Ms1, H2 ,M2 ,S2 ,Ms2:word;

begin
  randseed := 14;
  Fin_time :=0;
  conf := get_data('gen.config');
  print_config(conf);
  writeln('Debug_mode on? y/n');
  readln(debug);
  if debug = 'y' then conf.debug_mode := true
  else conf.debug_mode := false;;
  random_generation(current_generation, conf.population_size);
  prev_best := 0;
  if not conf.debug_mode then begin
  assign(out_f, 'output.txt');
  rewrite(out_f);
  end;
  while true do
  begin
  GetTime(H1, M1, S1, Ms1);
  lo:=low(current_generation.population);
  hi:=high(current_generation.population);
    selection_sort(lo, hi, current_generation);
    writeln('Generation ', current_generation.num);
    if conf.debug_mode then 
      print_population(current_generation)
    else begin
      writeln(out_f,'Generation ', current_generation.num);
      print_population_f(current_generation, out_f);
      write('gene = ');
    Print_bit(current_generation.population[0].gene); 
    writeln('; val=', current_generation.population[0].val,
             '; F_val=', current_generation.population[0].F_val);
             end;
    if abs(current_generation.population[0].F_val - prev_best) < conf.epsilon then
      inc(current_generation.useless_iterations)
    else
      current_generation.useless_iterations := 0;
    
    prev_best := current_generation.population[0].F_val;
    if check_for_stop_condition(current_generation, 
                                conf.max_useless_iterations,
                                conf.max_iterations,
                                conf.enough_val) then
    begin
    if not conf.debug_mode then begin
    check_for_stop_condition_f(current_generation, 
                                conf.max_useless_iterations,
                                conf.max_iterations,
                                conf.enough_val,out_f);
      Chto(current_generation,out_f);
      GetTime(H2 , M2 , S2 , Ms2); 
      Fin_time := Fin_time + (Ms2 - Ms1) 
                           + (S2*100 - S1*100) 
                           + (M2*6000 - M1*6000) 
                           + (H2*360000 - H1*360000);
      writeln(out_f,'Final work time ', Fin_time div 100,',',Fin_time mod 100, ' seconds');                
      writeln(out_f);
      close(out_f);
      end else 
      writeln('Final score: ', current_generation.population[0].F_val,
              ' at point ', current_generation.population[0].val);
      halt(0);
    end;
        {Selection}
    if conf.selection = 'RANDOM' then
      Selection_random(current_generation, conf.high_guys, conf.low_guys)
    else if conf.selection = 'PROPORTIONAL' then
      Selection_proportional(current_generation, conf.high_guys, conf.low_guys);
         {Cross}   
    for i := 1 to (conf.progeny_size div 2) do
    begin
      repeat
        rd1 := random(31);
        rd2 := random(31);
      until(rd1 <> rd2);
      repeat
        first := random(current_generation.surv);
        second := random(current_generation.surv);
      until(first <> second);
      if conf.crossbreeding = 'SINGLE' then begin
      if not conf.debug_mode then begin
      writeln(out_f,'Before  crossbreeding');
      Print_pair_file(current_generation.population[first],current_generation.population[second],out_f);
      end;
        single_cross(rd1, current_generation.population[first].gene,
                     current_generation.population[second].gene,
                     cur_progeny.first.gene, cur_progeny.second.gene)
      end else if conf.crossbreeding = 'DOUBLE' then begin
      if not conf.debug_mode then begin
      writeln(out_f,'Before  crossbreeding');
      Print_pair_file(current_generation.population[first],current_generation.population[second],out_f);
      end;
        double_cross(rd1, rd2, current_generation.population[first].gene,
                     current_generation.population[second].gene,
                     cur_progeny.first.gene, cur_progeny.second.gene)
      end else if conf.crossbreeding = 'UNIVERSAL' then begin
        prom_progeny.first.gene := current_generation.population[first].gene;
        prom_progeny.second.gene := current_generation.population[second].gene;
        if not conf.debug_mode then begin
        writeln(out_f,'Before  crossbreeding');
        Print_pair_file(current_generation.population[first],current_generation.population[second],out_f);
        end;
      for j := 0 to 31 do
        begin
          point := random(2);
          universal_cross(j, point, prom_progeny.first.gene,
                          prom_progeny.second.gene, cur_progeny.first.gene,
                          cur_progeny.second.gene);
          prom_progeny.first.gene := cur_progeny.first.gene;
          prom_progeny.second.gene := cur_progeny.second.gene;                 
        end;
      end else begin
        
        repeat
          third := random(current_generation.surv);
          fourth := random(current_generation.surv);
        until(third <> fourth);
        if not conf.debug_mode then begin
                writeln(out_f,'First pair before  crossbreeding');
        Print_pair_file(current_generation.population[first],current_generation.population[second],out_f);
                writeln(out_f,'Second pair before  crossbreeding');
        Print_pair_file(current_generation.population[third],current_generation.population[fourth],out_f);
        end;
        mask := random(high(longword));
        uniform_cross(mask, current_generation.population[first].gene,
                      current_generation.population[second].gene,
                      cur_progeny.first.gene);
        mask := random(high(longword));
        uniform_cross(mask, current_generation.population[third].gene,
                      current_generation.population[fourth].gene,
                      cur_progeny.second.gene);
      end;
      if not conf.debug_mode then begin  
      writeln(out_f,'After  crossbreeding');
      Print_pair_file(cur_progeny.first,cur_progeny.second,out_f);
      end;  
      Init(cur_progeny.first, cur_progeny.first.gene);
      Init(cur_progeny.second, cur_progeny.second.gene);                                   
      current_generation.population[current_generation.surv + 1] := cur_progeny.first;
      inc(current_generation.surv);
      current_generation.population[current_generation.surv + 1] := cur_progeny.second;
      inc(current_generation.surv);
    end;
        {Mutations}
    while current_generation.volume - 1 <> current_generation.surv do
    begin
      inc(current_generation.surv);
      mut_ent := random(current_generation.surv);
      if not conf.debug_mode then begin
        writeln(out_f,'Choosen one for mutation ');
        Print_entity_file(current_generation.population[mut_ent],out_f);
        end;
      if conf.mutation = 'RANDOM' then begin
        mutant := current_generation.population[mut_ent].gene;
        for j := 0 to 31 do
        begin
          point := random(4);
          rand_mutation(point, j, mutant, current_generation.population[current_generation.surv].gene);
          mutant := current_generation.population[current_generation.surv].gene;
        end;
      end                                
      else 
      if conf.mutation = 'SWITCH' then begin
        flag := true;
  while flag do begin
    repeat
      rd1 := random(31);
      rd2 := random(31);
    until rd1 <> rd2;
    bit1 := Get_bit(current_generation.population[mut_ent].gene, rd1);
    bit2 := Get_bit(current_generation.population[mut_ent].gene, rd2);
    if bit1 <> bit2 then
    begin
      flag := false;
     switch_mutation(rd1, rd2, current_generation.population[mut_ent].gene, current_generation.population[current_generation.surv].gene);
    end;                                  
    end;
    end else 
    begin
      rd1 := random(31);
      reverse_mutation(rd1, current_generation.population[mut_ent].gene, current_generation.population[current_generation.surv].gene);  
    end; 
    if not conf.debug_mode then begin
            writeln(out_f,'New mutant ');
        Print_entity_file(current_generation.population[current_generation.surv],out_f);
       end;                                 
      Init(current_generation.population[current_generation.surv],
              current_generation.population[current_generation.surv].gene);
    end;
    
    for i := low(current_generation.population) to high(current_generation.population) do
    begin
      for j := i + 1 to high(current_generation.population) do
      begin
        if current_generation.population[i].gene = current_generation.population[j].gene then 
          init(current_generation.population[j], random(high(longword)));
      end;
    end;
    inc(current_generation.num);
    GetTime(H2 , M2 , S2 , Ms2); 
      Fin_time := Fin_time + (Ms2 - Ms1) 
                           + (S2*100 - S1*100) 
                           + (M2*6000 - M1*6000) 
                           + (H2*360000 - H1*360000);
    if not conf.debug_mode then                       
    Writeln(out_f,'Current timework ', Fin_time);
  end;
      if not conf.debug_mode then
    begin
        assign(read_f, 'output.txt');
        reset(read_f);
        while not eof(read_f) do
        begin
            readln(read_f, s);
            writeln(s);
        end;
        close(read_f);
    end;
  setlength(current_generation.population, 0);
end.
