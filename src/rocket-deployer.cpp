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

#include "rocket-deployer.h"

using namespace Rocket;
 
int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		std::cout << "\nNo argument provided! Exiting ..." << std::endl;
		return 0;
	}
	int ret = -1;
	
	argc-=(argc>0);
	argv+=(argc>0); // skip program name argv[0] if present
	
	EXIT_ON_FAILURE(system(NULL), "ROCKET DEPLOYER INITIALIZED", "......Ok");
	
	//RocketDeployer rd;
	
	Arguments arguments = RocketDeployer::parseArguments(argc, argv);
	try
	{
		const std::string& value = RocketDeployer::getArgVal(arguments, "app");
		cout << value << endl;
	}
	CATCH_ARG_EXCEPTIONS("app");
	
	return 0;
}
