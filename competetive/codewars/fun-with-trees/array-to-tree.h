#include <vector>
#include <queue>

extern class TreeNode;

class Solution
{
public:
    static TreeNode* arrayToTree(std::vector<int> arr) 
    {
        if (arr.empty()) {
            return NULL;
        }
        
        std::reverse(arr.begin(), arr.end());
        TreeNode* root = new TreeNode(arr.back());
        arr.pop_back();


        std::queue<TreeNode*> Q;
        Q.push(root);

        while(!arr.empty()) {
            auto v = arr.back();
            arr.pop_back();

            auto node = Q.front();

            if (node->m_left == NULL) {
                node->m_left = new TreeNode(v);
                Q.push(node->m_left);
            } else {
                node->m_right = new TreeNode(v);
                Q.pop();
                Q.push(node->m_right);
            }
        }

        return root;
    }
};