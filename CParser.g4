parser grammar CParser;
options {
	tokenVocab = CLexer;
}

// 3.1.1 Keywords

keyword:
	Auto | Double | Int | Struct |
	Break | Else | Long | Switch |
	Case | Enum | Register | Typedef |
	Char | Extern | Return | Union |
	Const | Float | Short | Unsigned |
	Continue | For | Signed | Void |
	Default | Goto | Sizeof | Volatile |
	Do | If | Static | While;

// 3.1.2 Identifiers

identifier:
	Nondigit (Nondigit | Digit)*;
