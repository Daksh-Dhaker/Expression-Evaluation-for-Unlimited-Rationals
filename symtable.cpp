/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable(){
    this->size =0;
    this->root = NULL;
}

SymbolTable::~SymbolTable(){
    delete root;
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* s = new SymEntry(k,v);
    SymEntry* temp = root;
    if(root == NULL){
        root = s;
        size++;
        temp = NULL;
        delete temp;
    }else{
        size++;
        while(temp!=NULL){
            if(temp->key >=k){
                if(temp->left == NULL){
                    temp->left = s;
                    break; 
                }else{
                    temp = temp->left;
                }
            }else{
                if(temp->right == NULL){
                    temp->right = s;
                    break;
                }else{
                    temp = temp->right;
                }
            }
        }
        temp = NULL;
        delete temp;
        s = NULL;
        delete s;
    }
}

void SymbolTable::remove(string k){
    if(root == NULL){
        return;
    }
    else if(root->left == NULL && root->right == NULL){
        SymEntry* temp = root;
        root = NULL;
        delete temp;
        size--;
        return ;
    }else{
        SymEntry* temp = root;
        SymEntry* parent = NULL;
        while(temp->key != k && temp!=NULL){
            parent = temp;
            if(temp->key <k){
                temp = temp->right;
            }else{
                temp = temp->left;
            }
        }
        if(temp == NULL){
            parent = NULL;
            delete temp;
            delete parent;
            return;
        }
        if(temp->left == NULL && temp->right == NULL){
            if(parent == NULL){
                SymEntry* temp1 = temp;
                temp = NULL;
                delete temp1;
                size--;
                parent = NULL;
                delete parent;
                return ;
            }
            if(parent->left == temp){
                parent->left = NULL;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }else{
                parent->right = NULL;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }
        }
        else if(temp->left == NULL && temp->right !=NULL){
            if(parent == NULL){
                root = temp->right;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }
            if(parent->left == temp){
                parent->left = temp->right;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }else{
                parent->right = temp->right;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }
        }
        else if(temp->left !=NULL && temp->right == NULL){
            if(parent == NULL){
                root = temp->left;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }
            if(parent->left == temp){
                parent->left = temp->left;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }else{
                parent->right = temp->left;
                delete temp;
                size--;
                parent = NULL;
                delete parent;
                return;
            }
        }
        else if(temp->left !=NULL && temp->right !=NULL){
            SymEntry* succ = temp->right;
            while(succ->left !=NULL){
                succ = succ->left;
            }
            string succ_key = succ->key;
            UnlimitedRational* succ_val = succ->val;
            this->remove(succ_key);
            temp->key = succ_key;
            temp->val = succ_val;
            succ = NULL;
            delete succ;
            return;
        }
    }
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* temp = root;
    while(temp->key!=k && temp!=NULL){
        if(temp->key <k){
            temp=temp->right;
        }else{
            temp = temp->left;
        }
    }
    UnlimitedRational* value = temp->val;
    temp = NULL;
    delete temp;
    return value;
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}
