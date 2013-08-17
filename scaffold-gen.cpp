/****************************
comment

program is a status-machine.

****************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

string const version = "0.5";

string makefile_comment()
{
	return
		string("##") + "\n" + 
		"# Autogenerated by Cing C++ Development Framework" + "( " + version + " )" +
		"\n" + "# You can modify it to suit your application." + "\n" +
		"#";
}

string source_comment()
{
	return
		string("//") + "\n" + 
		"// Autogenerated by Cing C++ Development Framework" + "( " + version + " )" +
		"\n" + "// You can modify it to suit your application." + "\n" +
		"//";
}

bool is_exist(std::string file_path)
{
	if(access(file_path.c_str(), F_OK) < 0)
		return false;
	else
		return true;
}

// include target 
string dep_command(vector<string> &objects)
{
	string commd;
	commd += "default: ";
	for(vector<string>::iterator it=objects.begin(); it != objects.end(); ++it)
	{
		commd += "$(OBJDIR)/";
		commd += *it;
		commd += ".o ";

		commd += "$(OBJDIR)/";
		commd += *it;
		commd += "d.o ";
	} 
	commd += "$(BINDIR)/$(target) ";
	commd += "$(BINDIR)/$(target)d";

	return commd;
}

int obj_command_template(ofstream &file, string &object)
{
	file << "$(OBJDIR)/" << object << ".o: $(SRCDIR)/" << object << 
	".cpp $(INCDIR)/" << object << ".h" << endl;
	file << "\t" << "$(CPP) $(INCLUDE) $(RELEASEOPT_CPP) -c $< -o $@" << endl << endl;

	file << "$(OBJDIR)/" << object << "d" << ".o: $(SRCDIR)/" << object << 
	".cpp $(INCDIR)/" << object << ".h" << endl;
	file << "\t" << "$(CPP) $(INCLUDE) $(DEBUGOPT_CPP) -c $< -o $@" << endl << endl;

	return 0;
}

string get_token(string &line)
{
	int i = 0;
	string temp;
	while(line[i] != ' ' && i < line.size())
	{
		temp.push_back(line[i]);
		++i;
	}
	return temp;
}
void get_user_add(ifstream &makefile, vector<string> &userConfig)
{
	string line;
	string firstSym;
	while(std::getline(makefile,line))
	{
		firstSym = get_token(line);
		cout << line << endl;
		cout << firstSym << endl;
		if (firstSym == "APP_ADD_INCLUDE")
		{
			userConfig.push_back(string(line, 19));
		}
		else if(firstSym == "APP_ADD_LIBRARY")
		{
			userConfig.push_back(string(line, 19));

		}
		else if(firstSym == "SYSLIBS")
		{
			userConfig.push_back(string(line, 11));
		}
		else
		{

		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "Please input more module names:" << endl;
		cout << "\t" << "For example:" << endl;
		cout << "\t" << "\t" << "scaffold-gen APP1 server client" << endl;
	}
	else
	{
		string const src = "src";
		string const incl = "include";
		string const build_system = "BuildSystem";
		string const output = "output";
		string const obj = "obj";
		string const lib = "lib";
		string const bin = "bin";
		string const cur_dir = "./";
		string const f_makefile = "Makefile";
		string const components = "components";

		string const src_path = cur_dir + src;
		string const incl_path = cur_dir + incl;
		string const output_dir_path = cur_dir + output;
		string const obj_dir_path = output_dir_path + "/" + obj;
		string const lib_dir_path = output_dir_path + "/" + lib;
		string const bin_dir_path = output_dir_path + "/"  + bin;
		string const f_makefile_path = cur_dir + f_makefile;
		string const components_path = cur_dir + components;
		string const build_system_path = cur_dir + build_system;
		string const build_system_obj_path = build_system_path + "/" + "obj";

		mkdir(src_path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir(incl_path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir(output_dir_path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir(obj_dir_path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir(lib_dir_path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir(bin_dir_path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);

		vector< string > f_src;
		string temp_argc;
		string temp_argc_h;
		string temp_argc_cpp;
		string upper_temp_argc;
		ofstream src_file; 

		string APP_NAME = argv[1];

		for(unsigned int i = 2; i <= argc-1; ++i)
		{
			temp_argc = argv[i];
			temp_argc_h = incl_path + "/" + temp_argc + ".h";
			temp_argc_cpp = src_path + "/" + temp_argc + ".cpp";

			// .h
			if(is_exist(temp_argc_h.c_str()))
			{
				cout << temp_argc_h << "already exists" << endl;
				return 0;
			}
			src_file.open(temp_argc_h.c_str());
			src_file << source_comment() << endl;
			src_file << endl << endl;
			upper_temp_argc = temp_argc;
			transform(upper_temp_argc.begin(), upper_temp_argc.end(), upper_temp_argc.begin(), ::toupper);
			src_file << "#ifndef " << APP_NAME << "_" << upper_temp_argc << "_H" << endl;
			src_file << "#define " << APP_NAME << "_" << upper_temp_argc << "_H" << endl;
			src_file << endl;
			src_file << "namespace " << APP_NAME << " " << "{ " << endl;
			src_file << endl << endl;
			src_file << "class " << temp_argc << " " << endl;
			src_file << "{" << endl;
			src_file << endl << endl << endl << endl << endl;
			src_file << "};" << endl;
			src_file << endl;
			src_file << "} // namespace " << APP_NAME << endl;
			src_file << "#endif" << endl;
			src_file.close();
			
			// .cpp
			if(is_exist(temp_argc_cpp.c_str()))
			{
				cout << temp_argc_cpp << "already exists" << endl;
				return 0;
			}
			src_file.open(temp_argc_cpp.c_str());
			src_file << source_comment() << endl;
			src_file << endl << endl;
			src_file << "#include " << "\"" << temp_argc << ".h" << "\"" << endl << endl << endl;
			src_file << "namespace " << APP_NAME << " " << "{ " << endl;
			src_file << endl << endl;
			src_file << endl << endl << endl << endl << endl;
			src_file << "} // namespace " << APP_NAME << endl;
			src_file.close();

			// component
			src_file.open(components_path.c_str(),ofstream::app);
			src_file << argv[i] << endl;
			src_file.close();
		}

		// Makefile UI
		vector<string> userAdd;
		if (is_exist(f_makefile_path))
		{
			cout << "Makefile already exist" << endl;
			ifstream mkfile(f_makefile_path.c_str());
			get_user_add(mkfile,userAdd);
			mkfile.close();
		}
		else
		{
			userAdd.push_back(" ");
			userAdd.push_back(" ");
			userAdd.push_back(" ");
		}

		ofstream mkfile;
		mkfile.open(f_makefile_path.c_str());
		mkfile << makefile_comment() << endl << endl;
		mkfile << "cwd = $(shell pwd)" << endl << endl;
		mkfile << "APP_ADD_INCLUDE += " << userAdd[0] << endl;
		mkfile << "APP_ADD_LIBRARY += " << userAdd[1] << endl;
		mkfile << endl;
		mkfile << "objects = ";

		ifstream components_file(components_path.c_str());
		string object;
		vector<string> objects_buffer;
		while(getline(components_file,object))
		{
			mkfile << object << " ";
			objects_buffer.push_back(object);
		}
		components_file.close();

		mkfile << endl;
		mkfile << "target         = " << endl;
		mkfile << "target_version = 1" << endl;
		mkfile << "dep_libs    = " << endl;
		mkfile << endl;
		mkfile << "SYSLIBS += " << userAdd[2] << endl;
		mkfile << endl;
		mkfile << "include $(cwd)/BuildSystem/global" << endl;
		mkfile << "include $(cwd)/BuildSystem/obj" << endl;
		mkfile << "include $(cwd)/BuildSystem/bin" << endl;
		mkfile.close();

		//obj
		ofstream objfile;
		objfile.open(build_system_obj_path.c_str());
		objfile <<  makefile_comment() << endl << endl;
		objfile << dep_command(objects_buffer) << endl << endl;

		for(vector<string>::iterator it= objects_buffer.begin(); it != objects_buffer.end(); ++it)
		{
			obj_command_template(objfile,*it);
		}
		objfile.close();
	}

	return 0;
}

