#include "CBaseVisitor.h"

#include "ast/constants/integer/integerConstant.hpp"
#include "ast/constants/floating/floatingConstant.hpp"
#include "ast/constants/character/characterConstant.hpp"

class CParseVisitor : public CBaseVisitor {
  virtual antlrcpp::Any visitIntegerConstant(CParser::IntegerConstantContext *ctx) override {
  	return fgs::ast::ASTNodePtr{new fgs::ast::IntegerConstant(ctx->toString())};
  }

  virtual antlrcpp::Any visitFloatingConstant(CParser::FloatingConstantContext *ctx) override {
  	return fgs::ast::ASTNodePtr{new fgs::ast::FloatingConstant(ctx->toString())};
  }

  virtual antlrcpp::Any visitCharacterConstant(CParser::CharacterConstantContext *ctx) override {
    return fgs::ast::ASTNodePtr{new fgs::ast::CharacterConstant(ctx->toString())};
  }
};