/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

bool isbig(UnlimitedInt* i1,UnlimitedInt*i2){
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
        arr1 =NULL;
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

UnlimitedInt::~UnlimitedInt(){
    delete []unlimited_int;
}

UnlimitedInt::UnlimitedInt(){}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){}

UnlimitedInt::UnlimitedInt(string s){
    int i;
    int t=0;
    int string_size = s.size();
    string a ="";
    if(s[0]=='-' || s[0]=='+'){
        a = a+s[0];
        t=1;
    }
    while(s[t]=='0' && t<string_size-1){
        t++;
    }
    s = a+s.substr(t);
    if(s[0]=='-'){
        this->size = s.size()-1;
        i=1;
        this->sign = -1;
        this->capacity = this->size;
        unlimited_int = new int[capacity];
    }else if(s[0]=='+'){
        this->size = s.size()-1;
        i=1;
        this->sign = 1;
        this->capacity = this->size;
        unlimited_int = new int[capacity];       
    }else{
        this->size = s.size();
        i=0;
        this->sign = 1;
        this->capacity = this->size;
        unlimited_int = new int[capacity];
    }

    int k=0;
    for(int j = s.size()-1;j>=i;j--){
        unlimited_int[k]= stoi(s.substr(j,1));
        k++;
    }
}

UnlimitedInt::UnlimitedInt(int kk){
    string s = std::to_string(kk);
    if (kk<0){
        ;
    }else{
        s = "+"+s;
    }
    int i;
    if(s[0]=='-'){
        this->size = s.size()-1;
        i=1;
        this->sign = -1;
        this->capacity = this->size;
        unlimited_int = new int[capacity];
    }else if(s[0]=='+'){
        this->size = s.size()-1;
        i=1;
        this->sign = 1;
        this->capacity = this->size;
        unlimited_int = new int[capacity];       
    }else{
        this->size = s.size();
        i=0;
        this->sign = 1;
        this->capacity = this->size;
        unlimited_int = new int[capacity];
    }
    int k=0;
    for(int j = s.size()-1;j>=i;j--){
        unlimited_int[k]= stoi(s.substr(j,1));
        k++;
    }
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1,UnlimitedInt *i2){
    int*arr1 = i1->get_array();
    int*arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    while(arr1[size1-1]==0 && size1>1){
        size1--;
    }
    while(arr2[size2-1]==0 && size2>1){
        size2--;
    }
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    if(sign1 == sign2){
        int carry =0;
        string s ="";
        int i=0;
        int j=0;
        while(i<size1 && j<size2){
            int curr = (arr1[i]+arr2[j]+carry)%10;
            carry = (arr1[i]+arr2[j]+carry)/10;
            s = std::to_string(curr)+s;
            i++;
            j++;
        }
        while(i<size1){
            int curr = (arr1[i]+carry)%10;
            carry = (arr1[i]+carry)/10;
            s = std::to_string(curr)+s;
            
            i++;
        }
        while(j<size2){
            int curr = (arr2[j]+carry)%10;
            carry = (arr2[j]+carry)/10;
            s = std::to_string(curr)+s;
            
            j++;
        }
        
        if(carry !=0){
            s = std::to_string(carry)+s;
        }
        if(sign1 ==1){
            s="+"+s;
        }else{
            s = "-"+s;
        }
        UnlimitedInt* ans = new UnlimitedInt(s);
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        return ans;
    }else if(sign2 == -1 && sign1 == 1){
        string s = i2->to_string();
        s[0]= '+';
        UnlimitedInt* temp = new UnlimitedInt(s);
        UnlimitedInt* ans = UnlimitedInt::sub(i1,temp);
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        delete temp;
        return ans;
    }else{
        string s = i1->to_string();
        s[0]='+';
        UnlimitedInt* temp = new UnlimitedInt(s);
        UnlimitedInt* ans = UnlimitedInt::sub(i2,temp);
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        delete temp;
        return ans;
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1,UnlimitedInt* i2){
    int*arr1 = i1->get_array();
    int*arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    while(arr1[size1-1]==0 && size1>1){
        size1--;
    }
    while(arr2[size2-1]==0 && size2>=1){
        size2--;
    }
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    if(sign1 != sign2){
        if(sign1 == -1){
            string s = i2->to_string();
            if(s[0]=='+'){
                s[0]='-';
            }else{
                s = "+"+s;
            }
            UnlimitedInt* temp = new UnlimitedInt(s);
            UnlimitedInt* ans = UnlimitedInt::add(i1,temp);
            arr1 = NULL;
            arr2 = NULL;
            delete arr1;
            delete arr2;
            delete temp;
            return ans;
        }else{
            string s = i2->to_string();
            s[0]='+';
            UnlimitedInt* temp = new UnlimitedInt(s);
            UnlimitedInt* ans = UnlimitedInt::add(i1,temp);
            arr1 = NULL;
            arr2 = NULL;
            delete arr1;
            delete arr2;
            delete temp;
            return ans;
        }
    }else{
        int big = -1;
        if(size1>size2){
            big = 1;
        }else if(size1<size2){
            big = 0;
        }else{
            for(int i=size1-1;i>=0;i--){
                if(arr1[i]>arr2[i]){
                    big = 1;
                    break;
                }
                if(arr1[i]<arr2[i]){
                    big =0;
                    break;
                }
            }
        }
        if(big ==-1){
            UnlimitedInt* ans = new UnlimitedInt("+0");
            return ans;
        }else{
            int *sub1;
            int* sub2;
            int minsize;
            int maxsize;
            if(big == 1){
                sub1 = arr1;
                sub2 = arr2;
                minsize = size2;
                maxsize = size1;
            }else{
                sub1 = arr2;
                sub2 = arr1;
                minsize = size1;
                maxsize = size2;
            }
            int carry =0;
            string s ="";
            for(int i=0;i<minsize;i++){
                int diff = (sub1[i]-sub2[i]-carry);
                if(diff <0){
                    diff = diff +10;
                    carry =1;
                }else{
                    carry =0;
                }
                s = std::to_string(diff)+s;
            }
            for(int i=minsize;i<maxsize;i++){
                int diff = sub1[i]-carry;
                if(diff <0){
                    diff = diff+10;
                    carry =1;
                }else{
                    carry =0;
                }
                s = std::to_string(diff)+s;
            }
            int t=0;
            int string_size = s.size();
            while(s[t]=='0' && t<string_size-1){
                t++;
            }
            s = s.substr(t);
            
            if(big ==1){
                if(sign1 ==1){
                    s ="+"+s;
                    UnlimitedInt* ans = new UnlimitedInt(s);
                    arr1 = NULL;
                    arr2 = NULL;
                    delete arr1;
                    delete arr2;
                    return ans;
                }else{
                    s = "-"+s;
                    UnlimitedInt* ans = new UnlimitedInt(s);
                    arr1 = NULL;
                    arr2 = NULL;
                    delete arr1;
                    delete arr2;
                    return ans;
                }
            }else{
                if(sign1 ==1){
                    s = "-"+s;
                    UnlimitedInt* ans = new UnlimitedInt(s);
                    arr1 = NULL;
                    arr2 = NULL;
                    delete arr1;
                    delete arr2;
                    return ans;
                }else{
                    s = "+"+s;
                    UnlimitedInt* ans = new UnlimitedInt(s);
                    arr1 = NULL;
                    arr2 = NULL;
                    delete arr1;
                    delete arr2;
                    return ans;
                }
            }
        }
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1,UnlimitedInt* i2){
    
    UnlimitedInt* ans = new UnlimitedInt("+0");
    UnlimitedInt* temp1;
    UnlimitedInt* temp2;
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    string string1 = i1->to_string();
    string string2 = i2->to_string();
    string1 = string1.substr(1);
    
    string2 = string2.substr(1);
    if(size1 > size2){
        temp1 = new UnlimitedInt(string2);
        temp2 = new UnlimitedInt(string1);
    }else{
        temp1 = new UnlimitedInt(string1);
        temp2 = new UnlimitedInt(string2);
    }
    size1 = temp1->get_size();
    size2 = temp2->get_size();
    int *arr1 = temp1->get_array();
    int *arr2 = temp2->get_array();
    while(arr1[size1-1]==0 && size1>1){
        size1--;
    }
    
    while(arr2[size2-1]==0 && size2>1){
        size2--;
    }
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    UnlimitedInt* zero = new UnlimitedInt("+0");
    for(int i=0;i<temp1->get_size();i++){
        UnlimitedInt* currsum = zero;
        string s = temp2->to_string();
        for(int j=0;j<i;j++){
            s = s+"0";
        }
        
        UnlimitedInt* to_be_added = new UnlimitedInt(s);
        for(int j=0;j<arr1[i];j++){
            currsum = add(to_be_added,currsum);
        }

        ans = UnlimitedInt::add(ans,currsum);
    }
    if(ans->to_string()=="+0"){
        arr1 = NULL;
        arr2 = NULL;
        delete temp1;
        delete temp2;
        delete arr1;
        delete arr2;
        return ans;
    }
    if(sign1!=sign2){
        string s = ans->to_string();
        if(s[0]=='+' || s[0]=='-'){
            s[0]='-';
        }else{
            s = "-"+s;
        }
        UnlimitedInt* multans = new UnlimitedInt(s);
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        delete temp1;
        delete temp2;
        delete ans;
        return multans; 
    }else{
        arr1 = NULL;
        arr2 = NULL;
        delete arr1;
        delete arr2;
        delete temp1;
        delete temp2;
        return ans;
    }
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1,UnlimitedInt*i2){
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    
    string dividend_string = i1->to_string().substr(1);
    string divisor_string = i2->to_string().substr(1);
    UnlimitedInt* dividend = new UnlimitedInt(dividend_string);
    UnlimitedInt* divisor = new UnlimitedInt(divisor_string);
    
    if(isbig(divisor,dividend) && divisor->to_string()!=dividend->to_string()){
        if(sign1 == sign2){
            UnlimitedInt* ans = new UnlimitedInt("+0");
            return ans;
        }else{
            if(dividend->to_string()=="+0"){
                UnlimitedInt* ans = new UnlimitedInt("+0");
                return ans;
            }else{
                UnlimitedInt* ans = new UnlimitedInt("-1");
                return ans;
            }
        }
    }else{
        string part_dividend = "";
        string ans="";
        UnlimitedInt* partial;
        for(long unsigned int i=0;i<dividend_string.size();i++){
            part_dividend = part_dividend + (dividend_string[i]);
            partial = new UnlimitedInt(part_dividend);
            int digit=0;
            
            while(isbig(partial,divisor) || partial->to_string()==divisor->to_string()){
                digit++;
                partial = sub(partial,divisor);
            }
            
            part_dividend = partial->to_string().substr(1);
            ans = ans+std::to_string(digit);
        }
        
        if(sign1 == sign2){
            UnlimitedInt* divans = new UnlimitedInt(ans);
            delete dividend;
            delete divisor;
            delete partial;
            return divans;
        }else{
            UnlimitedInt* divans = new UnlimitedInt(ans);
            UnlimitedInt* min_one = new UnlimitedInt("-1");
            divans = mul(divans,min_one);
            //UnlimitedInt* partial = new UnlimitedInt(part_dividend);
            if(partial->to_string()!="+0"){
                divans = add(divans,min_one);
            }
            delete dividend;
            delete divisor;
            delete min_one;
            delete partial;
            return divans;
        }
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt*i1,UnlimitedInt* i2){
    UnlimitedInt* ans = sub(i1,mul(i2,div(i1,i2)));
    return ans;
}

string UnlimitedInt::to_string(){
    while(unlimited_int[size-1]==0 && size>1){
        size--;
    }
    string s ="";
    for(int i=size-1;i>=0;i--){
        s =s+ std::to_string(unlimited_int[i]);
    }
    if(sign == 1){
        s ='+'+s;
    }else{
        s = '-'+s;
    }
    return s;
}
