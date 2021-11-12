lexer grammar CLexer;

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
