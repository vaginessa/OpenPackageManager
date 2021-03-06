#include <bits/stdc++.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "paths.hpp"
#include "install.hpp"
using namespace std;
using namespace boost::property_tree;

void remove_pack(char* pname){
	stringstream ss;
	ss << pname;
	string del_path = APP_PACKAGES_PATH + ss.str();
	char* s_copy = (char*)alloca(del_path.size() + 1);
	memcpy(s_copy, del_path.c_str(), del_path.size() + 1);

	if(check_installed(pname))
	{
		rm(del_path); 
		string installedlist = APP_BIN_PATH;
		installedlist += "installed.list";
		ifstream jsonFile(installedlist);
		ptree pt, mpt, npt;
		if (jsonFile.good()){
			read_json(jsonFile, pt);
			bool cont = true;
			for(auto & package_list:pt.get_child("installed")){
				ptree new_package;
				cont = true;
				for(auto & package:package_list.second ){
					if (package.first == "packagename" && package.second.get_value<string>() == ss.str()){
						cont = false;
						break;
					}
					new_package.put(package.first,package.second.get_value<string>());
				}
				if (cont)
					mpt.push_back(make_pair("", new_package));
			}
		}
		npt.add_child("installed", mpt);
		write_json(installedlist, npt);
	}
	else
		printf("%s: No such package found\n", pname);



}
