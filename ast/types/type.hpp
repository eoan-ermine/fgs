enum class Type {
	Void, Char, Short, Int, Long,
	Float, Double, __Bool, __Complex
};

class TypeInfo {
	Type type;
	bool is_pointer;
public:
	TypeInfo(Type type, bool is_pointer): type(type), is_pointer(is_pointer) { }

	Type getType() const {
		return type;
	}

	bool isPointer() const {
		return is_pointer;
	}
};