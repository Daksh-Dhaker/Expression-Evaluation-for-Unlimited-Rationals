/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){}

SymEntry::SymEntry(string k,UnlimitedRational*v){
    this->key = k;
    this->val = v;
    this->left = NULL;
    this->right = NULL;
}

SymEntry::~SymEntry(){
    delete val;
    delete left;
    delete right;
}