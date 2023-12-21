/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

bool isbig1(UnlimitedInt* i1,UnlimitedInt*i2){
    int*arr1 = i1->get_array();
    int*arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    while(arr1[size1-1]==0 && size1>1){
        size1--;
    }
    while(arr2[size2-1]==0 && size2>1){
        size2--;
    }
    bool big = true;
    if(size1>size2){
        big = true;
    }else if(size1<size2){
        big = false;
    }else{
        for(int i=size1-1;i>=0;i--){
            if(arr1[i]>arr2[i]){
                big = true;
                break;
            }
            if(arr1[i]<arr2[i]){
                big =false;
                break;
            }
        }
    }
    if(sign1 ==1 && sign2 ==1){
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        return big;
    }else if(sign1 == 1 && sign2 ==-1){
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        return true;
    }else if(sign1 == -1 && sign2 ==1){
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        return false;
    }else{
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        return !big;
    }
}

UnlimitedInt* gcd(UnlimitedInt* i1,UnlimitedInt* i2){
    UnlimitedInt* num1 = i1;
    UnlimitedInt* num2 = i2;
    if(isbig1(num1,num2)){
        while(UnlimitedInt::mod(num1,num2)->to_string()!="+0"){
            UnlimitedInt* temp = UnlimitedInt::mod(num1,num2);
            num1 = num2;
            num2 = temp;
            temp = NULL;
            delete temp;
        }
        num1 = NULL;
        delete num1;
        return num2;
    }else{
        while(UnlimitedInt::mod(num2,num1)->to_string()!="+0"){
            UnlimitedInt* temp = UnlimitedInt::mod(num2,num1);
            num2 = num1;
            num1 = temp;
            temp = NULL;
            delete temp;
        }
        num2 = NULL;
        delete num2;
        return num1;
    }
}

UnlimitedRational::UnlimitedRational(){}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num,UnlimitedInt* den){
    if(den->to_string()=="+0"){
        this->p = new UnlimitedInt("+0");
        this->q = den;
    }else if(num->to_string() =="+0"){
        UnlimitedInt* one = new UnlimitedInt("+1");
        this->p = num;
        this->q = one;
        one = NULL;
        delete one;
    }
    else{
        //cout<<"Reached here"<<endl;
        int sign1 = num->get_sign();
        int sign2 = den->get_sign();
        UnlimitedInt* num_ans;
        UnlimitedInt* den_ans;
        if(sign1 == sign2){
            string s1 = num->to_string();
            string s2 = den->to_string();
            if(sign1 == -1){
                s1[0]='+';
                s2[0]='+';
            }
            UnlimitedInt* num1 = new UnlimitedInt(s1);
            UnlimitedInt* den1 = new UnlimitedInt(s2);
            num_ans = UnlimitedInt::div(num1,gcd(num1,den1));
            den_ans = UnlimitedInt::div(den1,gcd(num1,den1));
            this->p = num_ans;
            this->q = den_ans;
            delete num1;
            delete den1;
        }else{
            string s1 = num->to_string();
            string s2 = den->to_string();
            if(sign1 == 1){
                s1[0]='-';
                s2[0]='+';
            }
            UnlimitedInt*num1 = new UnlimitedInt(s1.substr(1));
            UnlimitedInt*den1 = new UnlimitedInt(s2.substr(1));
            UnlimitedInt*num2 = new UnlimitedInt(s1);
            UnlimitedInt*den2 = new UnlimitedInt(s2);
            num_ans = UnlimitedInt::div(num2,gcd(num1,den1));
            den_ans = UnlimitedInt::div(den2,gcd(num1,den1));
            this->p = num_ans;
            this->q = den_ans;
            delete num1;
            delete den1;
            delete num2;
            delete den2;
        }
    }
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    string ans = p->to_string();
    if(ans[0]=='+'){
        return ans.substr(1);
    }else{
        return ans;
    }
}

string UnlimitedRational::get_q_str(){
    string ans = q->to_string();
    if(ans[0]=='+'){
        return ans.substr(1);
    }else{
        return ans;
    }
}

string UnlimitedRational::get_frac_str(){
    string num_str = p->to_string();
    string den_str = q->to_string();
    if(num_str[0]=='+'){
        num_str = num_str.substr(1);
    }
    if(den_str[0]=='+'){
        den_str = den_str.substr(1);
    }
    string ans = num_str+"/"+den_str;
    return ans;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1,UnlimitedRational* i2){
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();
    UnlimitedRational* ans;
    if(b->to_string()=="+0" || d->to_string()=="+0"){
        UnlimitedInt* zero = new UnlimitedInt("+0");
        ans = new UnlimitedRational(zero,zero);
        zero = NULL;
        delete zero;
    }else{
        UnlimitedInt* num = UnlimitedInt::add(UnlimitedInt::mul(a,d),UnlimitedInt::mul(b,c));
        UnlimitedInt* den = UnlimitedInt::mul(b,d);
        ans = new UnlimitedRational(num,den);
        num = NULL;
        den = NULL;
        delete num;
        delete den;
    }
    a = NULL;
    b = NULL;
    c = NULL;
    d = NULL;
    delete a;
    delete b;
    delete c;
    delete d;
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1,UnlimitedRational* i2){
    UnlimitedInt* a = i2->get_p();
    UnlimitedInt* b = i2->get_q();
    UnlimitedInt* min_one = new UnlimitedInt("-1");
    a = UnlimitedInt::mul(a,min_one);
    UnlimitedRational* n = new UnlimitedRational(a,b);
    UnlimitedRational* ans = UnlimitedRational::add(i1,n);
    a = NULL;
    b = NULL;
    min_one = NULL;
    n = NULL;
    delete a;
    delete b;
    delete min_one;
    delete n;
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1,UnlimitedRational*i2){
    //cout<<"Reached Here"<<endl;
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();
    UnlimitedRational* ans;
    if(b->to_string()=="+0" || d->to_string()=="+0"){
        UnlimitedInt* zero = new UnlimitedInt("+0");
        ans = new UnlimitedRational(zero,zero);
        zero = NULL;
        delete zero;
    }else{
        //cout<<"Reached Here"<<endl;
        UnlimitedInt* num = UnlimitedInt::mul(a,c);
        UnlimitedInt* den = UnlimitedInt::mul(b,d);
        ans = new UnlimitedRational(num,den);
        num = NULL;
        den = NULL;
        delete num;
        delete den;
    }
    a = NULL;
    b = NULL;
    c = NULL;
    d = NULL;
    
    delete a;
    delete b;
    delete c;
    delete d;
    
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1,UnlimitedRational* i2){
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();
    UnlimitedRational* ans;
    if(b->to_string()=="+0" || d->to_string()=="+0" || c->to_string()=="+0"){
        UnlimitedInt* zero = new UnlimitedInt("+0");
        ans = new UnlimitedRational(zero,zero);
        zero = NULL;
        delete zero;
    }else{
        UnlimitedInt* num = UnlimitedInt::mul(a,d);
        UnlimitedInt* den = UnlimitedInt::mul(b,c);
        ans = new UnlimitedRational(num,den);
        num = NULL;
        den = NULL;
        delete num;
        delete den;
    }
    a = NULL;
    b = NULL;
    c = NULL;
    d = NULL;
    
    delete a;
    delete b;
    delete c;
    delete d;
    
    return ans;
}
