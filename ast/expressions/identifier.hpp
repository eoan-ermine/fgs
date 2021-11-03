#include <string_view>
#include <string>

class Identifier {
	std::string name;
public:
	Identifier(std::string_view name): name(name) { }

	std::string_view getName() const {
		return name;
	}
};