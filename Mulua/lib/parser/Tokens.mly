%token EOF

%token <string> Identifier

%token NilLiteral "nil"
%token <bool> BooleanLiteral
%token <int> IntegerLiteral

%token If "if"
%token Then "then"
%token Else "else"
%token While "while"
%token Do "do"
%token End "end"

%token ParenLeft "("
%token ParenRight ")"

%token Plus "+"
%token Minus "-"
%token Star "*"
%token DoubleSlash "//"
%token EqualEqual "=="
%token TildeEqual "~="
%token LessEqual "<="
%token GreaterEqual ">="
%token Less "<"
%token Greater ">"
%token Equal "="

%token Print "print"
%token Input "input"

%left Less LessEqual Greater GreaterEqual EqualEqual TildeEqual
%left Plus Minus
%left Star DoubleSlash
%%


