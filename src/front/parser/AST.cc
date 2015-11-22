#include <string>
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
  CallExprAST(const std::string &callee, std::vecotr<BaseAST*> &args)
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

