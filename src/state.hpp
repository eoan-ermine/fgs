#pragma once

#include "llvm/IR/Value.h"

#include <unordered_map>

using EnumerationsStorage = std::unordered_map<std::string, llvm::Value*>;

class State {
	EnumerationsStorage enumerations;
public:
	EnumerationsStorage& getEnumerations() {
		return enumerations;
	}
	const EnumerationsStorage& getEnumerations() const {
		return enumerations;
	}
};