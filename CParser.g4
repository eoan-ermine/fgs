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

// 3.1.3.1 Floating constants

floatingConstant:
	fractionalConstant exponentPart? FloatingSuffix?
	| digitSequence exponentPart FloatingSuffix?;

fractionalConstant:
	digitSequence? '.' digitSequence
	| digitSequence '.';

exponentPart:
	(LowerE | UpperE) Sign? digitSequence;

digitSequence:
	Digit+;

// 3.1.3.2 Integer constants

integerConstant:
	decimalConstant integerSuffix?
	| octalConstant integerSuffix?
	| hexadecimalConstant integerSuffix?;

decimalConstant:
	NonzeroDigit Digit*;

octalConstant:
	Zero OctalDigit*;

hexadecimalConstant:
	Zero (LowerX | UpperX) HexadecimalDigit+;

integerSuffix:
	UnsignedSuffix LongSuffix?
	| LongSuffix UnsignedSuffix?;

// 3.1.3.3 Enumeration constants

enumerationConstant:
	identifier;

// 3.1.3.4 Character constants

characterConstant:
	UpperL? Apostrophe cCharSequence Apostrophe;

cCharSequence:
	cChar+;

cChar:
	CharSet
	| escapeSequence;

escapeSequence:
	simpleEscapeSequence
	| octalEscapeSequence
	| hexadecimalEscapeSequence;

simpleEscapeSequence:
	(Backslash Apostrophe) | (Backslash Quotation) | (Backslash Backslash) | (Backslash LowerA) | (Backslash LowerB) | (Backslash LowerF) | (Backslash LowerN) | (Backslash LowerR) | (Backslash LowerT) | (Backslash LowerV);

octalEscapeSequence:
	Backslash OctalDigit{1-3};

hexadecimalEscapeSequence:
	Backslash LowerX HexadecimalDigit+;