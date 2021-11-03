enum class Operator {
	// Assignment

	Assign, AddAssign, SubAssign, MulAssign, DivAssign,
	ModAssign, AndAssign, OrAssign, XorAssign,
	LeftShiftAssign, RightShiftAssign,

	// Increment/decrement

	PreIncrement, PreDecrement, PostIncrement, PostDecrement,

	// Arithmetic

	UnaryPlus, UnaryMinus, Add, Sub, Mul, Div, Mod,
	Not, And, Or, Xor, LeftShift, RightShift,

	// Logical

	LogicalNot, LogicalAnd, LogicalOr,

	// Comparison

	Eq, NotEq, Less, Greater, LessOrEqual, GreaterOrEqual,

	// Member access

	Subscript, Dereference, Address, Access, PointerAccess,

	// Other

	FunctionCall, Comma, Cast, Conditional, Sizeof, Alignof
};