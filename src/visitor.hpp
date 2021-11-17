#pragma once

#include "CParserBaseVisitor.h"
#include "ast/constants/constants.hpp"

class visitor: public CParserBaseVisitor {
public:
	antlrcpp::Any visitIntegerConstant(CParser::IntegerConstantContext *ctx) {
		return static_cast<ASTNode*>(
			new integerConstant{
				std::stoi(ctx->toString())
			}
		);
	}
	antlrcpp::Any visitFloatingConstant(CParser::FloatingConstantContext* ctx) {
		return static_cast<ASTNode*>(
			new floatingConstant{
				std::stod(ctx->toString())
			}
		);
	}
	antlrcpp::Any visitCharacterConstant(CParser::CharacterConstantContext* ctx) {
		return static_cast<ASTNode*>(
			new characterConstant{
				std::stoi(ctx->toString())
			}
		);
	}
	antlrcpp::Any visitStringLiteral(CParser::StringLiteralContext* ctx) {
		return static_cast<ASTNode*>(
			new stringConstant{
				ctx->toString()
			}
		);
	}
}