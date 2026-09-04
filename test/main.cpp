#include<iostream>
#include "../var_saver.hpp"
int main(){long long r;
    long long b = 99;int f = 8;
    VarSaver::SaveVarToFile(__FILE__,"save.out");
    return 0;
}
