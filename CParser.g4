parser grammar CParser;
options {
	tokenVocab = CLexer;
}

keyword:
	Auto | Double | Int | Struct |
	Break | Else | Long | Switch |
	Case | Enum | Register | Typedef |
	Char | Extern | Return | Union |
	Const | Float | Short | Unsigned |
	Continue | For | Signed | Void |
	Default | Goto | Sizeof | Volatile |
	Do | If | Static | While;
