
#include <algorithm>
#include <iostream>
#include <utility>
#include <iomanip>
#include <string>
#include <cmath>
#include <list>

using namespace std::string_literals;
using std::string, std::pair, std::list;


/**
 * @brief Es un arbol de cadenas que nos ayudará a realizar
 * el analisis de sintaxis y la evaluacion de la cadena
 */
struct SyntaxTree {
  SyntaxTree() {}
  SyntaxTree(string const& val) : value(val) {}

  constexpr bool empty() const noexcept { return value == ""; }

  SyntaxTree& add(SyntaxTree const& to_add) {
    if (!to_add.empty())
      children.emplace_back(to_add);
    return *this;
  }

  void print(int deep = 0) {
    for (int i = 0; i < deep; ++i)
      std::cout << "> ";
    std::cout << value << '\n';
    for (auto child : children)
      child.print(deep + 1);
  }

  string value{ "" };
  list<SyntaxTree> children { };
};



/**
 * @brief Gestiona la entrada
 */
struct EntryManager {
public:
  EntryManager(string const& code)
    : code(code) {
  }

  constexpr void advance() noexcept {
    index_current++;
  }

  constexpr char current() const noexcept {
    return code[index_current];
  }

  constexpr string current_str() const noexcept {
    return ""s + code[index_current];
  }

  constexpr bool is_sum() const noexcept {
    return current() == '+' || current() == '-';
  }

  constexpr bool is_prod() const noexcept {
    return current() == '*' || current() == '/';
  }

  constexpr bool is_pow() const noexcept {
    return current() == 'p';
  }

  constexpr bool is_num() const noexcept {
    return '0' <= current() && current() <= '9';
  }
private:
  int index_current = 0;
  string code;
};



/**
 * @brief Examina la sintaxis de la cadena de entrada
 */
struct ArithmeticAnalyzer {
public:
  ArithmeticAnalyzer(string const& code)
    : input(code) {
  }

  auto analyze() {
    SyntaxTree tree;
    try {
      tree = expr();
    }
    catch (string const& err) {
      std::cout << "[Error]: " << err << '\n';
    }
    return tree;
  }
private:

  // <Expr> -> <Term> <ExprAux>
  SyntaxTree expr() {
    return SyntaxTree("+")
      .add(term())
      .add(expr_aux());
  }

  // <ExprAux> -> + <Expr> | - <Expr> | E
  SyntaxTree expr_aux() {
    if (input.is_sum()) {
      return SyntaxTree("+")
        .add(term())
        .add(expr_aux());
    }
    return {};
  }

  // <Term> -> <Factor> <TermAux>
  SyntaxTree term() {
    return SyntaxTree("*")
      .add(factor())
      .add(term_aux());
  }

  // <TermAux> -> * <Term>
  // <TermAux> -> / <Term> | E
  SyntaxTree term_aux() {
    if (input.is_prod()) {
      SyntaxTree tree(input.current_str());
      input.advance();
      tree
        .add(factor())
        .add(term_aux());
      return tree;
    }
    return {};
  }

  // <Factor> -> <Base> <FactorAux>
  SyntaxTree factor() {
    return SyntaxTree("p")
      .add(base())
      .add(factor_aux());
  }

  // <FactorAux> -> p <Factor> | E
  SyntaxTree factor_aux() {
    if (input.is_pow()) {
      input.advance();
      return SyntaxTree("p")
        .add(base())
        .add(factor_aux());
    }
    return {};
  }

  // <Base> -> (<Expr>) | <Number>
  SyntaxTree base() {
    SyntaxTree tree("+");

    if (input.is_sum()) {
      tree.value = input.current_str();
      input.advance();
    }

    if (input.is_num()) {
      tree.add(number());
    }
    else if (input.current() == '(') {
      input.advance();
      tree.add(expr());
      if (input.current() != ')') {
        throw "Hay parentesis sin cerrar"s;
      }
      input.advance();
    } else {
      throw "Se esperaba un termino/expresion"s;
    }

    return tree;
  }

  SyntaxTree number() {
    static std::string_view alphabets[] = { "0123456789", ".", "+-", "Ee" };
    static int automat[][4] = {
      {  2,  7,  1, -1 },
      {  2,  7, -1, -1 },
      {  2,  3, -1,  4 },
      {  3, -1, -1,  4 },
      {  5, -1,  6, -1 },
      {  5, -1, -1, -1 },
      {  5, -1, -1, -1 },
      {  3, -1, -1, -1 },
    };
    static bool accepts[8] = { 0, 0, 1, 1, 0, 1, 0, 0 };

    SyntaxTree tree;

    int state = 0;
    bool error = false;

    while (!error) {
      error = true;
      for (int i = 0; i < 4; ++i) {
        auto& alphabet = alphabets[i];
        if (std::find(alphabet.begin(), alphabet.end(), input.current()) == alphabet.end())
          continue;
        error = false;

        if (automat[state][i] == -1) {
          error = true;
          break;
        }

        state = automat[state][i];

        tree.value.push_back(input.current());
        input.advance();
      }
    }

    if (!accepts[state]) {
      throw "Formato de numero invalido"s;
    }

    return tree;
  }

private:
  EntryManager input;
};


double eval(SyntaxTree const& root) {
  double res = 0.0;
  if (root.value == "+")
  {
    for (auto& child : root.children)
      res += eval(child);
  }
  else if (root.value == "-")
  {
    for (auto& child : root.children)
      res -= eval(child);
  }
  else if (root.value == "*")
  {
    res = 1.0;
    for (auto& child : root.children)
      res *= eval(child);
  }
  else if (root.value == "/")
  {
    if (root.children.size() == 2)
    {
      double num = eval(root.children.front());
      double denom = eval(root.children.back());

      if (denom == 0.0)
        std::cout << "[ERROR]: Division por cero\n";

      res = num / denom;
    }
    if (root.children.size() == 1)
    {
      double denom = eval(root.children.front());

      if (denom == 0.0)
        std::cout << "[ERROR]: Division por cero\n";

      res = 1.0 / denom;
    }
  }
  else if (root.value == "p")
  {
    if (root.children.size() == 2)
    {
      res = std::pow(
        eval(root.children.front()),
        eval(root.children.back()));
    }
    if (root.children.size() == 1)
    {
      res = eval(root.children.front());
    }
  }
  else if ('0' <= root.value[0] && root.value[0] <= '9' || root.value[0] == '.')
  {
    res = std::stod(root.value);
  }
  return res;
}

double eval(const string& code) {
  ArithmeticAnalyzer aa(code);

  auto tree = aa.analyze();

  return eval(tree);
}


int main(int argc, char const* argv[]) {

  if (argc == 2)
    std::cout << std::setprecision(14) << eval(argv[1]) << '\n';

  return 0;
}
