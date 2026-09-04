#include<iostream>
#include "../var_saver.hpp"
int main(){long long r;
    long long b = 99;int f = 8;
    VarSaver::SaveVarToFile(__FILE__,"save.out");
    VarSaver::LoadVarToFile("save.out","main2.cpp");
    return 0;
}
