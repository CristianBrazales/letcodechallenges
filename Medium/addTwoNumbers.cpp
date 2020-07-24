/**
Problem described:
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       int multiplier=1;
       int val1,val2,add;
       int total=0;
        add=0;

        ListNode* solution=nullptr;
        ListNode*ret=solution;

        while(l1!=nullptr || l2!=nullptr || add>0){

            if(l1){
                val1=l1->val;
                l1=l1->next;

            }else
                val1=0;

            if(l2){
                 val2=l2->val;
                  l2=l2->next;
            }else
                val2=0;
            total=val1+val2+add;
            std::cout<<total<<val1<<val2<<std::endl;
            if(total>=10){
                add=total/10;
            }else{
                add=0;
            }

            ListNode* new_node=new ListNode(total%10);
            if(solution==nullptr){
                ret=new_node;
                solution=new_node;
            }else{
                solution->next=new_node;
                solution=new_node;
            }
        }


        return ret;
    }
};
