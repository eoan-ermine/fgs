#include "identifier.hpp"

enum class PrimaryExpressionType {
	Identifier, Constant, StringLiteral,
	Expression
};

union PrimaryExpressionValue {
	Identifier, Constant, StringLiteral
};

class PrimaryExpression {
	PrimaryExpressionType type;
	PrimaryExpressionValue value;
public:
	PrimaryExpression(PrimaryExpressionType type,
		PrimaryExpressionValue value):
	type(type), value(value) { }
};