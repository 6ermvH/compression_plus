#include <queue>
#include <unordered_map>
#include <string>
#include <functional>

class Tbor {
  private:
    struct Node {
      Node* left;
      Node* right;
      char symbol;
      std::size_t num;
      bool isTerminate;
      Node(Node* n1, Node* n2, char c1, std::size_t c2, bool n3) : left(n1), right(n2),
                                                                   symbol(c1), num(c2), isTerminate(n3) {} 
    };

    struct compare_node {
      bool operator() (Node* lhs, Node* rhs) const {
        return lhs->num < rhs->num;
      }
    };
  public:

    Tbor() = delete;
    Tbor(const Tbor&) = delete;
    Tbor& operator=(const Tbor&) = delete;

    Tbor(const std::string& text);
    ~Tbor();

  private:
    
    Tbor(const std::unordered_map<char, std::size_t>& letters);
    std::unordered_map<char, std::size_t> text_to_tokens(const std::string& text);
    void dfs(Node* current, std::function<void(Node*)> op);
    static void delete_node(Node* current);

    Node* root;
    std::map<char, std::bitset> 
};
