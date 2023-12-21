/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){}

ExprTreeNode::ExprTreeNode(string t,UnlimitedInt*v){
    long unsigned int i;
    int j=0;
    if(t[0]=='-'){
        j++;
    }
    if(t[0]=='+'){
        j++;
    }
    for(i=j;i<t.size();i++){
        if(t[i]-'0' <0 || t[i]-'0' >9){
            break;
        }
    }
    if(t==":="){
        this->type = t;
        this->val = NULL;
        this->evaluated_value = NULL;
    }
    else if(t=="+"){
        this->type = "ADD";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else if(t=="-"){
        this->type = "SUB";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else if(t=="*"){
        this->type = "MUL";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else if(t == "/"){
        this->type = "DIV";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else{
        if(i==t.size()){
            this->type = "VAL";
            UnlimitedInt* one = new UnlimitedInt("+1");
            UnlimitedRational* value = new UnlimitedRational(v,one);
            this->val = value;
            this->evaluated_value = value;
            one = NULL;
            delete one;
        }else{
            this->type = "VAR";
            this->id = t;
            UnlimitedInt* one = new UnlimitedInt("+1");
            UnlimitedRational* value = new UnlimitedRational(v,one);
            this->val = value;
            this->evaluated_value = value;
            one = NULL;
            delete one; 
        }
    }
    this->right = NULL;
    this->left = NULL;
}

ExprTreeNode::ExprTreeNode(string t,UnlimitedRational*v){
    long unsigned int i;
    int j=0;
    if(t[0]=='-'){
        j++;
    }
    if(t[0]=='+'){
        j++;
    }
    for(i=j;i<t.size();i++){
        if(t[i]-'0' <0 || t[i]-'0' >9){
            break;
        }
    }
    if(t == ":="){
        this->type = t;
        this->val = NULL;
        this->evaluated_value = NULL;
    }
    else if(t=="+"){
        this->type = "ADD";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else if(t=="-"){
        this->type = "SUB";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else if(t=="*"){
        this->type = "MUL";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else if(t == "/"){
        this->type = "DIV";
        this->val = NULL;
        this->evaluated_value = NULL;
    }else{
        if(i==t.size()){
            this->type = "VAL";
            this->val = v;
            this->evaluated_value = v;
        }else{
            this->type = "VAR";
            this->id = t;
            this->val = v;
            this->evaluated_value = v; 
        }
    }
    this->right = NULL;
    this->left = NULL;
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}