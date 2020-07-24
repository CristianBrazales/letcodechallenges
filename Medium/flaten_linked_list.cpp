/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root)
            return;
        if((root->left==nullptr && root->right==nullptr ))
            return;

        stack <TreeNode*> s;
        TreeNode* top,*new_top,*right,*left,*new_node, *prev;
        s.push(root);

        // save the references
        prev=root;
        bool skip=true;
        while(!s.empty()){
            //pop current top
            top=s.top();
            s.pop();
            int value=top->val;
            // create a new node
            new_node=new TreeNode(value);
            // check childs
            right=top->right;
            if(right)
                s.push(right);
            left=top->left;
            if(left)
                s.push(left);
            // since we start with the root already
            // no need to repeat this
            if(!skip){
              
            prev->left=nullptr;
            prev->right=new_node;
            prev=new_node;
            }
            skip=false;

        }


    }
};
