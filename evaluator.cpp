/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::~Evaluator(){
    delete symtable;
}

Evaluator::Evaluator(){
    this->symtable = new SymbolTable();
}

UnlimitedRational* evaluate(ExprTreeNode* root){
    if(root->type=="VAL" || root->type == "VAR"){
        return root->evaluated_value;
    }else{
        if(root->type == "ADD"){
            root->evaluated_value = UnlimitedRational::add(evaluate(root->left),evaluate(root->right));
            return root->evaluated_value;
        }else if(root->type == "SUB"){
            root->evaluated_value = UnlimitedRational::sub(evaluate(root->left),evaluate(root->right));
            return root->evaluated_value;
        }else if(root->type == "MUL"){
            root->evaluated_value = UnlimitedRational::mul(evaluate(root->left),evaluate(root->right));
            return root->evaluated_value;
        }else{
            root->evaluated_value = UnlimitedRational::div(evaluate(root->left),evaluate(root->right));
            return root->evaluated_value;
        }
    }
}

void Evaluator::parse(vector<string> code){
    vector<ExprTreeNode*> tree1;
    UnlimitedInt* one = new UnlimitedInt("+1");
    ExprTreeNode* root = new ExprTreeNode(":=",one);
    ExprTreeNode* symbol = new ExprTreeNode(code[0],one);
    root->left = symbol;
    
    for(long unsigned int i=2;i<code.size();i++){
        
        if(code[i]!=")"){
            if(code[i]=="("){
                ;
            }
            else if(code[i]=="+" || code[i]=="-" || code[i]=="/" || code[i]=="*"){
                ExprTreeNode* node = new ExprTreeNode(code[i],one);
                tree1.push_back(node);
            }else{
                ExprTreeNode* node = new ExprTreeNode(code[i],one);
                if(node->type == "VAL"){
                    UnlimitedInt* num = new UnlimitedInt(code[i]);
                    UnlimitedRational* variable_val = new UnlimitedRational(num,one);
                    node->val = variable_val;
                    node->evaluated_value = variable_val;
                    tree1.push_back(node);
                }else{
                    UnlimitedRational* value = symtable->search(code[i]);
                    node->val = value;
                    node->evaluated_value = value;
                    tree1.push_back(node);
                }
            }
        }else{
            ExprTreeNode* temp1 = tree1.back();
            tree1.pop_back();
            ExprTreeNode* temp2 = tree1.back();
            tree1.pop_back();
            ExprTreeNode* temp3 = tree1.back();
            tree1.pop_back();
            temp2->right = temp1;
            temp2->left = temp3;
            tree1.push_back(temp2);
            temp1 = NULL;
            temp2 = NULL;
            temp3 = NULL;
            delete temp1;
            delete temp2;
            delete temp3;   
        }
    }
    
    ExprTreeNode* exp = tree1.back();
    tree1.pop_back();
    root->right = exp;
    expr_trees.push_back(root);
    one = NULL;
    delete one;
    exp = NULL;
    delete exp;
    root = NULL;
    delete root;
    symbol = NULL;
    delete symbol;
}

void Evaluator::eval(){
    ExprTreeNode* root = expr_trees.back();
    
    ExprTreeNode* exp = root->right;
    UnlimitedRational* ans = evaluate(exp);
    string variable = root->left->id;
    symtable->insert(variable,ans);
    exp = NULL;
    delete exp;
    root = NULL;
    delete root;
    ans = NULL;
    delete ans;
    //std::cout<<ans->get_frac_str()<<endl;
}

