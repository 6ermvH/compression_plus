#include <queue>
#include <unordered_map>
#include <map>
#include <optional>
#include <string>
#include <functional>

class Tbor {
  private:
    struct Node {
      Node* left;
      Node* right;
      std::optional<char> symbol;
      std::size_t num;
      Node(Node* n1, Node* n2, std::optional<char> c1, std::size_t c2) : left(n1), right(n2),
                                                          symbol(c1), num(c2) {} 
    };

    struct compare_node {
      bool operator() (Node* lhs, Node* rhs) const {
        return lhs->num > rhs->num;
      }
    };
  public:

    Tbor() = delete;
    Tbor(const Tbor&) = delete;
    Tbor& operator=(const Tbor&) = delete;

    Tbor(const std::string& text);
    std::vector<bool> get_preambule();
    std::vector<char> get_alphabet();
    std::map<char, std::vector<bool> > data();
    ~Tbor();

  private:
    
    Tbor(const std::unordered_map<char, std::size_t>& letters);
    std::unordered_map<char, std::size_t> text_to_tokens(const std::string& text);
    void dfs(Node* current, std::function<void(Node*)> op);
    void dfs(Node* current, std::vector<bool> bits);

    static void delete_node(Node* current);

    Node* root_;
    std::map<char, std::vector<bool> > keyChars_;
};
