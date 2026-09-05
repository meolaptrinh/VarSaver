#include<iostream>
#include "../var_saver.hpp"
int main(){
    int a = 0;
    int b = 10;
    int c;
    double f,r,g,h;
    VarSaver::SaveVarToFile(__FILE__,"save.out");
    VarSaver::LoadVarToFile("save.out","main2.cpp");
    return 0;
}
