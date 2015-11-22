#include <string>
#include <vector>
#include "../APP.h"

/**
 * AST Types
 */
enum AstID {
  BaseID,
  VariableDeclID,
  BinaryExprID,
  CallExprID,
  JumpStmtID,
  VariableID,
  NumberID
};

/**
 * Base class of AST
 */
class BaseAST {
private:
  AstID ID;

public:
  BaseAST(AstID id) : ID(id) {}
  virtual ~BaseAST() {}
  AstID getValueID() const { return ID; }
};

/**
 * Variable Declaration
 */
class VariableDeclAST : public BaseAST {
public:
  typedef enum {
    param,
    local
  } DeclType;

private:
  std::string Name;
  DeclType Type;

public:
  VariableDeclAST(const std::string &name) : BaseAST(VariableDeclID), Name(name) {}
  ~VariableDeclAST() {}
  static inline bool classof(VariableDeclAST const*) { return true; }
  static inline bool classof(BaseAST const* base) {
    return base->getValueID() == VariableDeclID;
  }
  std::string getName() { return Name; }
  bool setDeclType(DeclType type) {
    Type = type;
    return true;
  }
  DeclType getType() { return Type; }
};

/**
 * Binary Operator AST
 */
class BinaryExprAST : public BaseAST {
private:
  std::string Op;
  BaseAST *LHS, *RHS;

public:
  BinaryExprAST(std::string op, BaseAST *lhs, BaseAST *rhs)
    : BaseAST(BinaryExprID), Op(op), LHS(lhs), RHS(rhs) {}
  ~BinaryExprAST() {
    SAFE_DELETE(LHS);
    SAFE_DELETE(RHS);
  }
  static inline bool classof(BinaryExprAST const*) { return true; }
  static inline bool classof(BaseAST const* base) {
    return base->getValueID() == BinaryExprID;
  }

  std::string getOp() { return Op; }
  BaseAST *getLHS() { return LHS; }
  BaseAST *getRHS() { return RHS; }
};

/**
 * Function Call AST
 */
class CallExprAST : public BaseAST {
private:
  std::string Callee;
  std::vector<BaseAST*> Args;

public:
  CallExprAST(const std::string &callee, std::vector<BaseAST*> &args)
    : BaseAST(CallExprID), Callee(callee), Args(args) { }
  ~CallExprAST();
  static inline bool classof(CallExprAST const*) { return true; }
  static inline bool classof(BaseAST const* base) {
    return base->getValueID() == CallExprID;
  }
  std::string getCallee() { return Callee; }
  BaseAST *getArgs(int i) {
    if (i < Args.size()) {
      return Args[i];
    } else {
      return nullptr;
    }
  }
};

/**
 * Jump AST
 */
class JumpStmtAST : public BaseAST {
private:
  BaseAST *Expr;

public:
  JumpStmtAST(BaseAST *expr) : BaseAST(JumpStmtID), Expr(expr) {}
  ~JumpStmtAST() { SAFE_DELETE(Expr); }
  static inline bool classof(JumpStmtAST const*) { return true; }
  static inline bool classof(BaseAST const* base) {
    return base->getValueID() == JumpStmtID;
  }
  BaseAST *getExpr() { return Expr; }
};

/**
 * Variable AST
 */
class VariableAST : public BaseAST {
private:
  std::string Name;

public:
  VariableAST(const std::string &name) : BaseAST(VariableID), Name(name) {}
  ~VariableAST() {}
  static inline bool classof(VariableAST const*) { return true; }
  static inline bool classof(BaseAST const* base) {
    return base->getValueID() == VariableID;
  }
  std::string getName() { return Name; }
};

/**
 * Number AST
 */
class NumberAST : public BaseAST {
private:
  int Val;

public:
  NumberAST(int val) : BaseAST(NumberID), Val(val) {}
  ~NumberAST() {}
  static inline bool classof(NumberAST const*) { return true; }
  static inline bool classof(BaseAST const* base) {
    return base->getValueID() == NumberID;
  }
  int getNumberValue() { return Val; }
};

/**
 * Prototype AST
 */
class PrototypeAST {
private:
  std::string Name;
  std::vector<std::string> Params;

public:
  PrototypeAST(const std::string &name, const std::vector<std::string> &params)
    : Name(name), Params(params) {}
  std::string getName() { return Name; }
  std::string getParamName(int i) {
    if (i < Params.size()) {
      return Params[i];
    } else {
      return NULL;
    }
  }
  int getParamNum() { return Params.size(); }
};

/**
 * Function Body AST
 */
class FunctionStmtAST {
private:
  std::vector<VariableDeclAST*> VariableDecls;
  std::vector<BaseAST*> StmtLists;

public:
  FunctionStmtAST() {}
  ~FunctionStmtAST() {}
  bool addVariableDeclaration(VariableDeclAST *vdecl);
  bool addStatement(BaseAST *stmt) {
    StmtLists.push_back(stmt);
    return true;
  }
  VariableDeclAST *getVariableDecl(int i) {
    if (i < VariableDecls.size()) {
      return VariableDecls[i];
    } else {
      return nullptr;
    }
  }
  BaseAST *getStatement(int i) {
    if (i < StmtLists.size()) {
      return StmtLists[i];
    } else {
      return nullptr;
    }
  }
};

/**
 * Function AST
 */
class FunctionAST {
private:
  PrototypeAST *Proto;
  FunctionStmtAST *Body;

public:
  FunctionAST(PrototypeAST *proto, FunctionStmtAST *body)
    : Proto(proto), Body(body) {}
  ~FunctionAST();
  std::string getName() { return Proto->getName(); }
  PrototypeAST *getPrototype() { return Proto; }
  FunctionStmtAST *getBody() { return Body; }
};

/**
 * Whole Sorce Code AST
 */
class TranslationUnitAST {
private:
  std::vector<PrototypeAST*> Prototypes;
  std::vector<FunctionAST*> Functions;

public:
  TranslationUnitAST() {}
  ~TranslationUnitAST() {}
  bool addPrototype(PrototypeAST *proto);
  bool addFunction(FunctionAST *func);
  bool empty();
  PrototypeAST *getPrototype(int i) {
    if (i < Prototypes.size()) {
      return Prototypes[i];
    } else {
      return nullptr;
    }
  }
  FunctionAST *getFunction(int i) {
    if (i < Functions.size()) {
      return Functions[i];
    } else {
      return nullptr;
    }
  }
};

