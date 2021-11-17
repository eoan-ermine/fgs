#pragma once

#include <optional>

#include <cstdint>
#include <stdexcept>

enum class SignednessSpecifier {
	Signed,
	Unsigned
};

enum class SizeSpecifier {
	Short,
	Long,
};

enum class BaseType {
	Void,
	Char,
	Int,
	Float,
	Double
};

class Type {
	std::optional<SignednessSpecifier> signedness;
	std::optional<SizeSpecifier> size;
	BaseType base;
	unsigned int byteWidth;
public:
	Type(SignednessSpecifier signedness_,
		SizeSpecifier_ size,
		BaseType base_, unsigned int byteWidth_): signedness(signedness_), size(size_), base(base_), byteWidth(byteWidth_) { }

	std::optional<SignednessSpecifier> getSignedness() const {
		return signedness;
	}
	std::optional<SizeSpecifier> getSize() const {
		return size;
	}
	BaseType getBase() const {
		return base;
	}

	unsigned int getByteWidth() const {
		return byteWidth;
	}
};