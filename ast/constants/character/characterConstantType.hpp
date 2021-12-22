#pragma once

namespace fgs::ast {

enum class CharacterConstantType {
	SingleByte,
	UTF16,
	UTF32,
	Wide,
	Multicharacter
};

}