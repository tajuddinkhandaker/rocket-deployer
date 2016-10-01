/*
 * rocket-deployer.cpp
 * 
 * Copyright 2016 Tajuddin Khandaker <tajuddin.khandaker.cse.ju@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

// build script: g++ -Wall -g -o rocket-deployer src/rocket-deployer.cpp && ./bin/rocket-deployer

#include <iostream>
#include <string>
#include <vector>
/* system example : DIR */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

#define KEY_LENGTH 100
#define VALUE_LENGTH 1000

#define EXIT_ON_FAILURE(ACTION, start_msg, msg_ok) \
  printf (start_msg); \
  ACTION; \
  if(ret) puts(msg_ok); \
  else exit (EXIT_FAILURE);
  
  
#define CATCH_ARG_EXCEPTIONS(key) \
	catch(e_errors e) \
	{ \
		if(e == err_arg_not_found) \
			std::cout << "\nArgument not found! >> " << key << std::endl; \
		if(e == err_arg_value_empty) \
		{ \
			std::cout << "\nArgument of " << key << " is empty!\nExiting ..." << std::endl; \
			exit (EXIT_FAILURE); \
		} \
	}

using namespace std;

typedef std::pair<std::string, std::string> Argument;
typedef std::vector<Argument> Arguments;
typedef Arguments::iterator IterArguments;

enum e_commands
{
	cmd_cd,
	cmd_cp,
	cmd_git_clone,
	cmd_git_pull,
	cmd_composer_selfupdate,
	cmd_composer_update,
	cmd_composer_dumpautoload
};

enum e_cmd_msg
{
	cmd_msg_default = 1
};

enum e_errors
{
	err_arg_not_found,
	err_arg_value_empty
};

const std::string g_c_commands[][3] = { 
	{ "cd", "Changing directories ...." },
	{ "cp", "Copying files ...." },
	{ "git clone", "" },
	{ "git pull", "" },
	{ "composer self-update", "" },
	{ "composer update", "" },
	{ "composer dumpautoload", "" }
};

const std::pair<std::string, std::string> parseArgs(const std::string& argument)
{
	const std::size_t ARG_LENGTH = KEY_LENGTH + VALUE_LENGTH + 1;
	char key[KEY_LENGTH], value[VALUE_LENGTH];
	
	if(argument.length() > ARG_LENGTH)
		return std::make_pair( "", "" );
			
	int ret = sscanf(argument.c_str(), "--%[^=]=%s", key, value);
	if(ret == EOF || !ret)
		return std::make_pair( "", "" );
		
	return std::make_pair(key, value);
}

const std::string& getArgVal(Arguments& arguments, const string& key) 
{
	for(IterArguments it = arguments.begin(); it != arguments.end(); it++)
	{
		Argument arg = *it;
		if(arg.first == key)
		{
			if(arg.second.empty())
				throw err_arg_value_empty;
			return it->second;
		}
	}
	throw err_arg_not_found;
}
 
int main(int argc, char* argv[])
{
	int ret = -1;
	Arguments arguments;
	
	argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
	EXIT_ON_FAILURE(system(NULL), "ROCKET DEPLOYER INITIALIZED", "......Ok");

	for(int argIndex = 0; argIndex < argc; argIndex++)
	{
		Argument keyValue = parseArgs(std::string(argv[argIndex]));
		if(keyValue.first.empty())
		{
			std::cout << "\nInvalid argument. Please check argument " << argIndex + 1 << std::endl << std::endl;
			exit (EXIT_FAILURE);
		}
		//std::cout << std::endl << keyValue.first << "=" << keyValue.second << std::endl;
		arguments.push_back( keyValue );
	}
	try
	{
		const std::string& value = getArgVal(arguments, "app");
		cout << value << endl;
	}
	CATCH_ARG_EXCEPTIONS("app");
	
	return 0;
}
