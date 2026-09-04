#ifndef VAR_SAVER_HPP
#define VAR_SAVER_HPP
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
namespace VarSaver{
    struct Var{
        std::string type;
        std::string name;
        std::string val = "none";
    };
    inline Var NotVar = {"0ERR","0ERR","0ERR"};
    inline std::string notban = ":_ \t;,";
    /**
     * @brief Parses a line of C++ code and extracts variable declarations.
     * @param s The C++ code line
     * @return An empty vector if not a variable declaration line; otherwise,a vector of Var structs.
     * @warning Your .cpp code file must contain a 'main(...)' function.
     * @note In this case, "line" is defined as a statement ending with a semicolon (;).
     */
    inline std::vector<Var> CommandToVar(std::string s){
        if(s.empty())return {};
        std::vector<Var>res;
        std::string vartype;
        for(int i = 0;i<s.size();i++){
            if(s[i] == '=')break;
            if(!std::isalnum(s[i]) && notban.find(s[i]) == notban.npos)return {};
        }
        //find the substring from begin to the end of first (',' '=' ';')
        for(char c:s){
            if(c == ',' || c == ';' || c == '=')break;
            vartype.push_back(c);
        }
        int spc = 0;
        int typeInd = vartype.size()-1;
        //find the var type
        while(typeInd>=0){
            if(spc == 0 && s[typeInd] != ' ')spc++;
            if(spc == 1 && s[typeInd] == ' ')break;
            typeInd--;
        }
        while(vartype.size()-1 > typeInd || vartype.back() == ' ')vartype.pop_back();
        //find variables
        std::string vrbstr;
        for(int i = typeInd+1;i<s.size();i++){if(s[i] == ';')break;vrbstr.push_back(s[i]);}
        std::vector<std::string>vars;
        std::string curvar;
        for(char c:vrbstr){
            if(c == ' ')continue;
            if(c == ','){vars.push_back(curvar);curvar = "";continue;}
            curvar.push_back(c);
        }
        if(curvar != "")vars.push_back(curvar);
        // Pack into Var vector
        std::string fxvartype;
        bool first = true;
            //delete ' ' before var type
        for(char c:vartype){
            if(first && c == ' ')continue;
            first = false;
            fxvartype.push_back(c);
        }
        if(fxvartype == "return" || fxvartype == "goto" || fxvartype == "using" || fxvartype == "delete" || fxvartype == "throw" || fxvartype == "typedef")return {};
        for(std::string vr:vars){
            std::string vrname;
            std::string vrvl;
            bool hvl = false;
            for(char c:vr){
                if(c == '='){hvl = true;continue;}
                if(!hvl)vrname.push_back(c);
                else vrvl.push_back(c);
            }
            if(!hvl){
                Var k = {fxvartype,vrname};
                res.push_back(k);
                continue;
            }else{
                Var k = {fxvartype,vrname,vrvl};
                res.push_back(k);
            }
        }
        return res;
    }
    /**
     * @brief Read C++ source code and extract variables to a file.
     * @param inp C++ code file path.
     * @param out Path to the output file where variable values will be saved.
     * @return true if the variable is saved successfully.
     * @return false if there is an error.
     * @warning Make sure your C++ source code is written correctly. 
     * @note It is recommended to use output file extension that does not conflict with the file extensions of other software.
     */
    inline bool SaveVarToFile(std::string inp,std::string out){
        std::vector<Var>res;
        std::ifstream cppf(inp,std::ios::binary);
        std::ofstream flout(out,std::ios::binary);
        if(!cppf.is_open() || !flout.is_open())return false;
        std::string s;
        int br = 0; //counting '{' or '}'
        //find main
        bool inmain = false;
        bool mainbl = false;
        int mainl = 0; //mainline
        int l = 0; //line
        std::vector<std::string>mainfunc;
        //find the main function
        while(std::getline(cppf,s)){
            if(!s.empty() && s[s.size()-1] == '\r')s.pop_back();
            if(br == 0){
                auto fmain = s.find("int main");
                if(fmain != std::string::npos){
                    mainl = l;
                    inmain = true;
                    mainfunc.push_back(s);
                }
            }
            if(br!=0 && l>=mainl){
                mainfunc.push_back(s);
            }
            if(inmain && br == 0 && l>mainl && mainbl)break;
            for(char c:s){
                if(c == '{'){
                    br++;
                    if(inmain)mainbl = true;
                }
                if(c == '}')br--;
            }
            l++;
        }
        std::string maincm;
        bool fx = false;
        for(std::string cm:mainfunc){
            for(char c:cm){
                if(c == '{'){fx = true;continue;}
                if(fx)maincm.push_back(c);
            }
        }
        std::string cm;
        for(char c:maincm){
            cm.push_back(c);
            if(c == ';'){
                std::vector<Var>k = CommandToVar(cm);
                for(Var vr:k)res.push_back(vr);
                cm = "";
            }
        }
        for(Var vr:res)flout<<vr.type<<" "<<vr.name<<" "<<vr.val<<"\n";
        return true;
    }
};
#endif