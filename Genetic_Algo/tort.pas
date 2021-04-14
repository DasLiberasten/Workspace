unit tort;

interface

uses  genetic, binary;

procedure selection_sort(lo, hi:integer; var current: generation);
procedure single_cross(start_point:byte; ent1, ent2: longword; var son, daughter: longword);
procedure double_cross(start_point, end_point:byte; ent1, ent2: longword; var son, daughter: longword);
procedure universal_cross(i,point:byte; ent1, ent2: longword; var son, daughter: longword);
procedure uniform_cross(mask, ent1, ent2: longword; var child: longword);
procedure rand_mutation(point:byte; i: longint; ent: longword; var mutant: longword);
procedure switch_mutation(pos1, pos2:byte; ent: longword; var mutant: longword);
procedure reverse_mutation(ps: byte; ent: longword; var mutant: longword);
implementation

procedure selection_sort(lo, hi:integer; var current: generation);
var
  tmp: entity;
  i, j, m: integer;
begin
  for i := lo to hi - 1 do
  begin
    m := i;
    for j := i + 1 to hi do
      if current.population[j].F_val > current.population[m].F_val then
      m := j;
    tmp := current.population[m];
    current.population[m] := current.population[i];
    current.population[i] := tmp;
  end;
end;

procedure single_cross(start_point:byte; ent1, ent2: longword; var son, daughter: longword);
var
i, bit1, bit2: byte;
begin
  son := ent1;
  daughter := ent2;
  for i := 0 to start_point do
  begin
    bit1 := Get_bit(ent1, i);
    bit2 := Get_bit(ent2, i);
    
    if bit1 = 0 then
      Zero_Bit(daughter, i)
    else
      Uno_Bit(daughter, i);
    if bit2 = 0 then
      Zero_Bit(son, i)
    else
      Uno_Bit(son, i);
  end;
end;

procedure double_cross(start_point, end_point:byte; ent1, ent2: longword; var son, daughter: longword);
var
  i, bit1, bit2: byte;

begin
  if start_point > end_point then begin
    i := start_point;
    start_point := end_point;
    end_point := i
  end;
  son := ent1;
  daughter := ent2;
  for i := start_point to end_point do
  begin
    bit1 := Get_bit(ent1, i);
    bit2 := Get_bit(ent2, i);
    
    if bit1 = 0 then
      Zero_Bit(daughter, i)
    else
      Uno_Bit(daughter, i);
    
    if bit2 = 0 then
      Zero_Bit(son, i)
    else
      Uno_Bit(son, i);
  end;
end;
               
procedure universal_cross(i,point:byte; ent1, ent2: longword; var son, daughter: longword);
begin
  son := ent1;
  daughter := ent2;
    if point = 1 then
    begin
      if Get_bit(ent1, 31 - i) = 0 then
        Zero_Bit(son, 31 - i)
      else
        Uno_Bit(son, 31 - i);
      if Get_bit(ent2, 31 - i) = 0 then
        Zero_Bit(daughter, 31 - i)
      else
        Uno_Bit(daughter, 31 - i);    
    end
        else
    begin
      if Get_bit(ent1, 31 - i) = 0 then
        Zero_Bit(daughter, 31 - i)
      else
        Uno_Bit(daughter, 31 - i);
      if Get_bit(ent2, 31 - i) = 0 then
        Zero_Bit(son, 31 - i)
      else
        Uno_Bit(son, 31 - i);    
    end;
end;

procedure uniform_cross(mask, ent1, ent2: longword; var child: longword);
var
  i: longint;

begin
  child := ent1;
  for i := 0 to 31 do
  begin
    if Get_bit(mask, i) = 0 then begin
      if Get_bit(ent1, i) = 0 then
        Zero_Bit(child, i)
      else
        Uno_Bit(child, i)
       end else begin
    if Get_bit(ent2, i) = 0 then
      Zero_Bit(child, i)
    else
      Uno_Bit(child, i);
  end;
  end;
end;



procedure rand_mutation(point:byte; i: longint; ent: longword; var mutant: longword);
begin
  mutant := ent;
    if point = 1 then begin
      if Get_bit(ent, i) = 1 then
        Zero_Bit(mutant, i)
      else
        Uno_Bit(mutant, i);
    end;
end;    

procedure reverse_mutation(ps: byte; ent: longword; var mutant: longword);
var
  bit1, bit2, i:byte;

begin
  mutant := ent;
  for i := 0 to (ps div 2) do
  begin
    bit1 := Get_bit(ent, i);
    bit2 := Get_bit(ent, ps - i);
    
    if bit1 = 0 then
      Zero_Bit(mutant, ps - i)
    else
      Uno_Bit(mutant, ps - i);
    
    if bit2 = 0 then
      Zero_Bit(mutant, i)
    else
      Uno_Bit(mutant, i);
  end;
end;

procedure switch_mutation(pos1, pos2:byte; ent: longword; var mutant: longword);
var
  bit1: byte;
begin
    mutant := ent;
    bit1 := Get_bit(ent, pos1);
      if bit1 = 0 then
      begin
        Uno_Bit(mutant, pos1);
        Zero_Bit(mutant, pos2);
      end    
      else
      begin
        Zero_Bit(mutant, pos1);
        Uno_Bit(mutant, pos2)
    end;
  end;

end.
