#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class TreeNode
{
public:
    TreeNode(const string &s = string(), int c = 0, TreeNode* l = nullptr, TreeNode* r = nullptr):
        value(s), count(c), left(l), right(r) { }
    TreeNode(const TreeNode& o):
        value(o.value), count(o.count), left(o.left), right(o.right) {  }
    TreeNode& operator=(const TreeNode&);
private:
    string value;
    int count;
    TreeNode *left;
    TreeNode *right;
};
TreeNode& TreeNode::operator=(const TreeNode& rhs)
{
    value = rhs.value;
    count = rhs.count;
    left = rhs.left;
    right = rhs.right;
    return *this;
}

int main()
{
    TreeNode t1("t1"), t2("t2");
    auto t3(t2);
    t3 = t1;

    return 0;
}