#include <string_view>
#include <string>

class StringLiteral {
	std::string value;
public:
	StringLiteral(std::string_view value): value(value) { }
	std::string_view getValue() const {
		return value;
	}
};