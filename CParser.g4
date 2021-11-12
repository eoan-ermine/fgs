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
	digitSequence? Dot digitSequence
	| digitSequence Dot;

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
	CCharSet
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

// 3.1.4 String literals

stringLiteral:
	UpperL? Quotation sCharSequence? Quotation;

sCharSequence:
	sChar+;

sChar:
	SCharSet
	| escapeSequence;

// 3.1.5 Operators

operator:
	SubscriptOperator | CallOperator | MemberAccesSOperator | MemberPointerAccessOperator | PreIncOperator | PreDecOperator | AddressOfOperator | MulOperator | AddOperator | SubOperator | BinaryNotOperator | LogicalNotOperator | SizeofOperator | DivOperator | RemOperator | LeftShiftOperator | RightShiftOperator | LessOperator | GreaterOperator | LessEqualOperator | GreaterEqualOperator | EqualOperator | NotEqualOperator | XorOperator | BinaryOrOperator | LogicalAndOperator | LogicalOrOperator | TernaryOperator | AssignOperator | MulAssignOperator | DivAssignOperator | RemAssignOperator | AddAssignOperator | SubAssignOperator | LeftShiftAssignOperator | RightShiftAssignOperator | BinaryAndAssignOperator | XorAssignOperator | BinaryOrAssignOperator | TokenOperator | ConcatenationOperator;

// 3.1.6 Punctuators

punctuator:
	SubscriptOperator | CallOperator | 
	(LeftCurlyBracket RightCurlyBracket) | Star | Comma | Colon | Equal | Semicolon | (Dot Dot Dot) | Number;

// 3.1.7 Header names

headerName:
	LeftAngleBracket hCharSequence RightAngleBracket
	| Quotation qCharSequence Quotation;

hCharSequence:
	hChar+;

hChar:
	HCharSet;

qCharSequence:
	qChar+;

qChar:
	QCharSet;

// 3.1.8 Preprocessing numbers

ppNumber:
	Digit
	| Dot Digit
	| ppNumber (Digit | Nondigit | (LowerE Sign) | (UpperE Sign) | Dot)+;