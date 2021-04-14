unit binary;

interface

procedure Uno_Bit(var input: longword; number: byte);
procedure Zero_Bit(var input: longword; number: byte);
function Get_bit(input: longword; number: byte): byte;
procedure Print_bit(input: longword);
procedure Print_bit_f(num : longword; var out_f : text);

implementation
procedure Print_bit_f(num : longword; var out_f : text);
var
    mask : longword;

begin
    mask := 1 shl 31;
    while mask <> 0 do
    begin
        if (num and mask) = 0 then
            write(out_f, 0)
        else
            write(out_f, 1);
        mask := mask shr 1;
    end;
end;
procedure Uno_Bit(var input: longword; number: byte);
var
    mask: longword;
begin
    mask := 1;
    mask := mask shl (31-number);
    input := input or mask;
end;

procedure Zero_Bit(var input: longword; number: byte);
var
    mask: longword;
begin
    mask := 1;
    mask := mask shl (31-number);
    input := not ((not input) or mask);
end;

function Get_bit(input: longword; number: byte): byte;
var
    mask: longword;
begin
    mask := 1;
    mask := mask shl (31 - number);
    if input and mask > 0 then
        Get_bit := 1
    else
        Get_bit := 0;
end;

procedure Print_bit(input: longword);
var
    mask: longword;
begin
    mask := 1 shl 31;
    while mask <> 0 do begin
        if (input and mask) = 0 then write(0)
            else write(1);
        mask := mask shr 1;
    end;
end;

end.
