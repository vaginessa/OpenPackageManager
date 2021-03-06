#include <bits/stdc++.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "update.hpp"
#include "paths.hpp"

using namespace boost::property_tree;
using namespace std;


void search_pack(vector<string> pack_list)
{
	//update the packages.list file
	string s = PACKAGES_LIST_URL;
    char* s_copy = (char*)alloca(s.size() + 1);
    memcpy(s_copy, s.c_str(), s.size() + 1);
    int pack_stat = update(s_copy);                                        
    if(pack_stat == -1){                                                   
        cout << "Error: Packages.list download failed!!" << endl;          
        return;                                                            
    }  

	stringstream ss;
    string packageslist = APP_BIN_PATH;
    packageslist += "packages.list";
	ifstream jsonFile(packageslist);
	vector<string> names;
    if (jsonFile.good()){
        ptree pt;
        read_json(jsonFile, pt);
        for(auto & ppt:pt){
            for(auto & package_list:ppt.second){
                for(auto & package:package_list.second){
                    if (package.first  == "packagename"){
                        if (pack_list.size() == 0 || find(pack_list.begin(), pack_list.end(), package.second.get_value<string>()) != pack_list.end())
                            names.push_back(package.second.get_value<string>());
                    }
                }
            }
        }
    }
    cout << "Packages [" << names.size() <<  "]:" << endl;
	for(int i = 0; i < names.size(); i++)
	{
		cout << names[i] << endl;
	}
}
