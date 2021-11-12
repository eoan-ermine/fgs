lexer grammar CLexer;

// 2.2.1 Character sets

SourceCharacterSet:
	[A-Za-z0-9!"#%&'()*+,\-./:;<=>?[\\\]^_{|}~\t\u{11}\u{0}\f ];

CCharSet:
	[A-Za-z0-9!"#%&()*+,\-./:;<=>?[\]^_{|}~\t\u{11}\u{0}\f \n];

SCharSet:
	[A-Za-z0-9!#%&()'*+,\-./:;<=>?[\]^_{|}~\t\u{11}\u{0}\f \n];

HCharSet:
	[A-Za-z0-9!"#%&'()*+,\-./:;<=?[\\\]^_{|}~\t\u{11}\u{0}\f ];

QCharSet:
	[A-Za-z0-9!#%&'()*+,\-./:;<=>?[\\\]^_{|}~\t\u{11}\u{0}\f ];

Exclamation: '!';
Quotation: '"';
Number: '#';
Percent: '%';
Ampersand: '&';
Apostrophe: '\'';
LeftParen: '(';
RightParen: ')';
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

Ellipsis: '...';

Zero: '0';

LowerA: 'a';
UpperA: 'A';

LowerB: 'b';
UpperB: 'B';

LowerF: 'f';
UpperF: 'F';

LowerN: 'n';
UpperN: 'N';

LowerR: 'r';
UpperR: 'R';

LowerT: 't';
UpperT: 'T';

LowerV: 'v';
UpperV: 'V';

LowerE: 'E';
UpperE: 'e';

LowerX: 'X';
UpperX: 'x';

LowerL: 'l';
UpperL: 'L';

SubscriptOperator: '[]';
CallOperator: '()';
MemberAccesSOperator: '.';
MemberPointerAccessOperator: '->';
IncOperator: '++';
DecOperator: '--';
AddressOfOperator: '&';
MulOperator: '*';
AddOperator: '+';
SubOperator: '-';
BinaryNotOperator: '~';
LogicalNotOperator: '!';
SizeofOperator: 'sizeof';
DivOperator: '/';
RemOperator: '%';
LeftShiftOperator: '<<';
RightShiftOperator: '>>';
LessOperator: '<';
GreaterOperator: '>';
LessEqualOperator: '<=';
GreaterEqualOperator: '>=';
EqualOperator: '==';
NotEqualOperator: '!=';
XorOperator: '^';
BinaryOrOperator: '|';
LogicalAndOperator: '&&';
LogicalOrOperator: '||';
TernaryOperator: '?:';
AssignOperator: '=';
MulAssignOperator: '*=';
DivAssignOperator: '/=';
RemAssignOperator: '%=';
AddAssignOperator: '+=';
SubAssignOperator: '-=';
LeftShiftAssignOperator: '<<=';
RightShiftAssignOperator: '>>=';
BinaryAndAssignOperator: '&=';
XorAssignOperator: '^=';
BinaryOrAssignOperator: '|=';
TokenOperator: '#';
ConcatenationOperator: '##';

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

// 3.1.9 Comments

Comment:
	'/*' ~[\\]* '*/' -> skip;

// 3.3.3 Unary operators

UnaryOperator:
	AddressOfOperator | MulOperator | AddOperator | SubOperator | BinaryNotOperator | LogicalNotOperator;

// 3.3.16 Assignment operators

AssignmentOperator:
	AssignOperator | MulAssignOperator | DivAssignOperator | RemAssignOperator | AddAssignOperator | SubAssignOperator | LeftShiftAssignOperator | RightShiftAssignOperator | BinaryAndAssignOperator | XorAssignOperator | BinaryOrAssignOperator
	;