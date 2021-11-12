lexer grammar CLexer;

// 2.2.1 Character sets

Exclamation: '!';
Quotation: '"';
Number: '#';
Percent: '%';
Ampersand: '&';
Apostrophe: '\'';
LeftParen: '(';
RightParent: ')';
Star: '*';
Plus: '+';
Comma: ',';
Hyphen: '-';
Dot: '.';
Slash: '/';
Colon: ':';
Semicolon: ';';
LeftAngleBracket: '<';
Equal: '=';
RightAngleBracket: '>';
Question: '?';
LeftSquareBracket: '[';
Backslash: '\\';
RightSquareBracket: ']';
Caret: '^';
Underscore: '_';
LeftCurlyBracket: '{';
VerticalBar: '|';
RightCurlyBracket: '}';
Tilde: '~';

Zero: '0';

UpperE: 'E';
LowerE: 'e';

UpperX: 'X';
LowerX: 'x';

// 3.1.1 Keywords

Auto: 'auto';
Double: 'double';
Int: 'int';
Struct: 'struct';
Break: 'break';
Else: 'else';
Long: 'long';
Switch: 'switch';
Case: 'case';
Enum: 'enum';
Register: 'register';
Typedef: 'typedef';
Char: 'char';
Extern: 'extern';
Return: 'return';
Union: 'union';
Const: 'const';
Float: 'float';
Short: 'short';
Unsigned: 'unsigned';
Continue: 'continue';
For: 'for';
Signed: 'signed';
Void: 'void';
Default: 'default';
Goto: 'goto';
Sizeof: 'sizeof';
Volatile: 'volatile';
Do: 'do';
If: 'if';
Static: 'static';
While: 'while';

// 3.1.2 Identifiers

Nondigit:
	[_a-zA-Z];

Digit:
	[0-9];

// 3.1.3.1 Floating constants

Sign:
	[+-];

FloatingSuffix:
	[flFL];

// Integer constants

NonzeroDigit:
	[1-9];

OctalDigit:
	[0-7];

HexadecimalDigit:
	[0-9a-fA-F];

UnsignedSuffix:
	[uU];

LongSuffix:
	[lL];
