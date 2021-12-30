#include "CBaseVisitor.h"

#include "ast/constants/integer/integerConstant.hpp"
#include "ast/constants/floating/floatingConstant.hpp"
#include "ast/constants/character/characterConstant.hpp"

class CParseVisitor : public CBaseVisitor {
  virtual antlrcpp::Any visitIntegerConstant(CParser::IntegerConstantContext *ctx) override {
  	return fgs::ast::IntegerConstant::parse(ctx->toString());
  }

  virtual antlrcpp::Any visitFloatingConstant(CParser::FloatingConstantContext *ctx) override {
  	return fgs::ast::FloatingConstant::parse(ctx->toString());
  }

  virtual antlrcpp::Any visitCharacterConstant(CParser::CharacterConstantContext *ctx) override {
    return fgs::ast::CharacterConstant::parse(ctx->toString());
  }
};