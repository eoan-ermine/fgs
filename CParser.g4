parser grammar CParser;
options {
	tokenVocab = CLexer;
}

// 3.1 Lexical elements

token:
	keyword
	| identifier
	| constant
	| stringLiteral
	| operator_
	| punctuator
	;

preprocessingToken:
	headerName
	| identifier
	| ppNumber
	| characterConstant
	| stringLiteral
	| operator_
	| punctuator
	;

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

// 3.1.3 Constants

constant:
	floatingConstant
	| integerConstant
	| enumerationConstant
	| characterConstant
	;

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
	Backslash (digits+=OctalDigit)+ {$digits.size() <= 3}?;

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

operator_:
	SubscriptOperator | CallOperator | MemberAccesSOperator | MemberPointerAccessOperator | IncOperator | DecOperator | AddressOfOperator | MulOperator | AddOperator | SubOperator | BinaryNotOperator | LogicalNotOperator | SizeofOperator | DivOperator | RemOperator | LeftShiftOperator | RightShiftOperator | LessOperator | GreaterOperator | LessEqualOperator | GreaterEqualOperator | EqualOperator | NotEqualOperator | XorOperator | BinaryOrOperator | LogicalAndOperator | LogicalOrOperator | TernaryOperator | AssignOperator | MulAssignOperator | DivAssignOperator | RemAssignOperator | AddAssignOperator | SubAssignOperator | LeftShiftAssignOperator | RightShiftAssignOperator | BinaryAndAssignOperator | XorAssignOperator | BinaryOrAssignOperator | TokenOperator | ConcatenationOperator;

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

// 3.3.1 Primary expressions

primaryExpression:
	identifier # PrimaryExprIdentifier
	| constant # PrimaryExprConstant
	| stringLiteral	 # PrimaryExprStringLiteral
	| LeftParen expression RightParen # PrimaryExprParenExpr;

// 3.3.2 Postfix operators

postfixExpression:
	primaryExpression # Primary
	| postfixExpression LeftSquareBracket expression RightSquareBracket # Subscript
	| postfixExpression LeftParen argumentExpressionList? RightParen # Call
	| postfixExpression MemberAccesSOperator identifier # Access
	| postfixExpression MemberPointerAccessOperator identifier # PtrAccess
	| postfixExpression IncOperator # PostInc
	| postfixExpression DecOperator # PostDec
	;

argumentExpressionList:
	assignmentExpression (Comma assignmentExpression)*;

// 3.3.3 Unary operators

unaryExpression:
	postfixExpression # Postfix
	| IncOperator unaryExpression # PreInc
	| DecOperator unaryExpression # PreDec
	| UnaryOperator castExpression # UnaryCast
	| Sizeof unaryExpression # SizeofExpr
	| Sizeof LeftParen typename_ RightParen # SizeofType
	;

// 3.3.4 Cast operators

castExpression:
	unaryExpression
	| LeftParen typename_ RightParen castExpression;

// 3.3.5 Multiplicative operators

multiplicativeExpression:
	castExpression
	| multiplicativeExpression MulOperator castExpression
	| multiplicativeExpression DivOperator castExpression
	| multiplicativeExpression RemOperator castExpression
	;

// 3.3.6 Additive operators

additiveExpression:
	multiplicativeExpression
	| additiveExpression AddOperator multiplicativeExpression
	| additiveExpression SubOperator multiplicativeExpression
	;

// 3.3.7 Bitwise shift operators

shiftExpression:
	additiveExpression
	| shiftExpression LeftShiftOperator additiveExpression
	| shiftExpression RightShiftOperator additiveExpression
	;

// 3.3.8 Relational operators

relationalExpression:
	shiftExpression
	| relationalExpression LessOperator shiftExpression
	| relationalExpression GreaterOperator shiftExpression
	| relationalExpression LessEqualOperator shiftExpression
	| relationalExpression GreaterEqualOperator shiftExpression
	;

// 3.3.9 Equality operators

equalityExpression:
	relationalExpression
	| equalityExpression EqualOperator relationalExpression
	| equalityExpression NotEqualOperator relationalExpression
	;

// 3.3.10 Bitwise AND operator

andExpression:
	equalityExpression
	| andExpression AddressOfOperator equalityExpression
	;

// 3.3.11 Bitwise exclusive OR operator

exclusiveOrExpression:
	andExpression
	| exclusiveOrExpression XorOperator andExpression
	;

// 3.3.12 Bitwise inclusive OR operator

inclusiveOrExpression:
	exclusiveOrExpression
	| inclusiveOrExpression BinaryOrOperator exclusiveOrExpression
	;

// 3.3.13 Logical AND operator

logicalAndExpression:
	inclusiveOrExpression
	| logicalAndExpression LogicalAndOperator inclusiveOrExpression
	;

// 3.3.14 Logical OR operator

logicalOrExpression:
	logicalAndExpression
	| logicalOrExpression LogicalOrOperator logicalAndExpression
	;

// 3.3.15 Conditional operator

conditionalExpression:
	logicalOrExpression
	| logicalOrExpression Quotation expression Colon conditionalExpression
	;

// 3.3.16 Assignment operators

assignmentExpression:
	conditionalExpression
	| unaryExpression AssignmentOperator assignmentExpression
	;

// 3.3.17 Comma operator

expression:
	assignmentExpression
	| expression Comma assignmentExpression
	;

// 3.4 Constant expression

constantExpression:
	conditionalExpression;

// 3.5 Declarations

declaration:
	declarationSpecifiers initDeclaratorList? Semicolon
	;

declarationSpecifiers:
	storageClassSpecifier declarationSpecifiers?
	| typeSpecifier declarationSpecifiers?
	| typeQualifier declarationSpecifiers?
	;

initDeclaratorList:
	initDeclarator
	| initDeclaratorList Comma initDeclarator
	;

initDeclarator:
	declarator
	| declarator AssignOperator initializer
	;

// 3.5.1 Storage-class specifiers

storageClassSpecifier:
	Typedef
	| Extern
	| Static
	| Auto
	| Register
	;

// 3.5.2 Type specifiers

typeSpecifier:
	Void | Char | Short | Int | Long
	| Float | Double | Signed | Unsigned
	| structOrUnionSpecifier | enumSpecifier | typedefName
	;

// 3.5.2.1 Structure and union specifiers

structOrUnionSpecifier:
	structOrUnion identifier? LeftCurlyBracket structDeclarationList RightCurlyBracket
	| structOrUnion identifier
	;

structOrUnion:
	Struct | Union;

structDeclarationList:
	structDeclaration*
	;

structDeclaration:
	specifierQualifierList structDeclaratorList Semicolon ;

specifierQualifierList:
	typeSpecifier specifierQualifierList?
	| typeQualifier specifierQualifierList
	;

structDeclaratorList:
	structDeclarator (Comma structDeclarator)+
	;

structDeclarator:
	declarator
	| declarator? Colon constantExpression
	;


// 3.5.2.2 Enumeration specifiers

enumSpecifier:
	Enum identifier? LeftCurlyBracket enumeratorList RightCurlyBracket
	| Enum identifier
	;

enumeratorList:
	enumerator (Comma enumerator)+
	;

enumerator:
	enumerationConstant
	| enumerationConstant AssignOperator constantExpression
	;

// 3.5.3 Type qualifiers

typeQualifier:
	Const | Volatile ;

// 3.5.4 Declarators

declarator:
	pointer? directDeclarator
	;

directDeclarator:
	identifier
	| LeftParen declarator RightParen
	| directDeclarator LeftSquareBracket constantExpression? RightSquareBracket
	| directDeclarator LeftParen parameterTypeList RightParen
	| directDeclarator LeftParen identifierList? RightParen
	;

pointer:
	Star typeQualifierList?
	| Star typeQualifierList? pointer
	;

typeQualifierList:
	typeQualifier typeQualifier*
	;

parameterTypeList:
	parameterList (Comma Ellipsis)?
	;

parameterList:
	parameterDeclaration (Comma parameterDeclaration)*
	;

parameterDeclaration:
	declarationSpecifiers declarator
	| declarationSpecifiers abstractDeclarator?
	;

identifierList:
	identifier (Comma identifier)*
	;

// 3.5.5 Type names

typename_:
	specifierQualifierList abstractDeclarator?
	;

abstractDeclarator:
	pointer
	| pointer? directAbstractDeclarator
	;

directAbstractDeclarator:
	LeftParen abstractDeclarator RightParen
	| LeftSquareBracket constantExpression? RightSquareBracket
	| LeftParen parameterTypeList? RightParen
	| directAbstractDeclarator LeftSquareBracket constantExpression? RightSquareBracket
	| directAbstractDeclarator LeftParen parameterTypeList? RightParen
	;

// 3.5.6 Type definitions

typedefName:
	identifier;

// 3.5.7 Initialization

initializer:
	assignmentExpression
	| LeftCurlyBracket initializerList RightCurlyBracket
	| LeftCurlyBracket initializerList Comma RightCurlyBracket
	;

initializerList:
	initializer (Comma initializer)*
	;

// 3.6 Statements

statement:
	labeledStatement
	| compoundStatement
	| expressionStatement
	| selectionStatement
	| iterationStatement
	| jumpStatement
	;

// 3.6.1 Labeled statements

labeledStatement:
	identifier Colon statement
	| Case constantExpression Colon statement
	| Default Colon statement
	;

// 3.6.2 Compound statement

compoundStatement:
	LeftCurlyBracket declarationList? statementList? RightCurlyBracket
	;

declarationList:
	declaration+;

statementList:
	statement+;

// 3.6.3 Expression and null statements

expressionStatement:
	expression? Semicolon;

// 3.6.4 Selection statements

selectionStatement:
	If LeftParen expression RightParen statement
	| If LeftParen expression RightParen statement Else statement
	| Switch LeftParen expression RightParen statement
	;

// 3.6.5 Iteration statements

iterationStatement:
	While LeftParen expression RightParen statement
	| Do statement While LeftParen expression RightParen Semicolon
	| For LeftParen expression? Semicolon expression? Semicolon expression? RightParen statement
	;

// 3.6.6 Jump statements

jumpStatement:
	Goto identifier Semicolon
	| Continue Semicolon
	| Break Semicolon
	| Return expression? Semicolon
	;

// 3.7 External definitions

translationUnit:
	externalDeclaration+;

externalDeclaration:
	functionDefinition
	| declaration;

// 3.7.1 Function definitions

functionDefinition:
	declarationSpecifiers? declarator
	| declarationList? compoundStatement
	;

// 3.8 Preprocessing directives

preprocessingFile:
	group?;

group:
	groupPart+;

groupPart:
	ppTokens? NEWLINE
	| ifSection
	| controlLine;

ifSection:
	ifGroup elifGroups? elseGroup? endifLine;

ifGroup:
	Ampersand If constantExpression NEWLINE group?
	| Ampersand Ifdef identifier NEWLINE group?
	| Ampersand Ifndef identifier NEWLINE group?
	;

elifGroups:
	elifGroup+;

elifGroup:
	Ampersand Elif constantExpression NEWLINE group?;

elseGroup:
	Ampersand Else NEWLINE group?;

endifLine:
	Ampersand Endif NEWLINE;

controlLine:
	Ampersand Include ppTokens NEWLINE
	| Ampersand Define identifier replacementList NEWLINE
	| Ampersand Define identifier LeftParen identifierList RightParen replacementList NEWLINE
	| Ampersand Undef identifier NEWLINE
	| Ampersand Line ppTokens NEWLINE
	| Ampersand Error ppTokens? NEWLINE
	| Ampersand Pragma ppTokens? NEWLINE
	| Ampersand NEWLINE
	;

replacementList:
	ppTokens?;

ppTokens:
	preprocessingToken+;