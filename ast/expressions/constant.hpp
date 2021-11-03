enum class ConstantType {
	Integer, Floating, Character
};

union ConstantValue {
	int integer;
	double floating;
	char character;
};

class Constant {
	ConstantType type;
	ConstantValue value;
public:
	ConstantType getType() const {
		return type;
	}
	ConstantValue getValue() const {
		return value;
	}
};