// hello.cpp

// build script: g++ -Wall -g -o Hello.exe Hello.cpp

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

using namespace std;

typedef std::pair<std::string, std::string> Argument;

enum e_commands
{
	cmd_cd,
	cmd_cp,
	cmd_git_clone,
	cmd_git_pull,
	cmd_composer_selfupdate,
	cmd_composer_update,
	cmd_composer_dumpautoload,
};

enum e_cmd_msg
{
	cmd_msg_default = 1
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

std::vector< std::pair<std::string, std::string> > arguments;

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
 
int main(int argc, char* argv[])
{
	int ret = -1;
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
	return 0;
}
