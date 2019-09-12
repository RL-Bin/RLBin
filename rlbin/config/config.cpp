/** @file config.cpp
    @brief Reads an initial config file and command line and create the final config file    
*/

#include <iostream>
#include <fstream>
#include <string>

#include "..\core\include\SubUnits\Utils\defs.h"
#include "..\core\include\SubUnits\Utils\RLBinUtils.h"

#include "..\include\config\config.h"
#include "..\core\include\CLI11\CLI11.hpp"

std::string ParseCLIConfig(int argc, char **argv)
{
	CLI::App app("RLBin");

	app.allow_extras();

	std::string mode = "native";
	int nativeflag = 0;	
	int staticflag = 0;	
	int dynamicflag = 0;	
	int disassmblerflag = 0;	
	
	CLI::Option* mopt = app.add_option("-m,--Mode", mode, "Operation Mode Option")->check(CLI::IsMember({"native","static","dynamic","disassemble"}))->group("Operation Mode");	 
	CLI::Option* nflag = app.add_flag("--native", nativeflag, "Native Mode flag")->group("Operation Mode");
	CLI::Option* sflag = app.add_flag("--static", staticflag, "Static Mode flag")->group("Operation Mode");
	CLI::Option* dflag = app.add_flag("--dynamic", dynamicflag, "Dynamic Mode flag")->group("Operation Mode");
	CLI::Option* dsflag = app.add_flag("--disassemble", disassmblerflag, "Disassembler Mode flag")->group("Operation Mode");

	int optlevel = 0;
	CLI::Option* oopt = app.add_option("-o,--OptLevel", optlevel, "Operation Mode Option")->check(CLI::Range(0,3))->group("Dynamic Mode Optimzation");	 

	bool code_pointer = false;
	CLI::Option* cpflag = app.add_flag("--UseCodePointers", code_pointer, "Using Code Pointer flag")->group("Static Mode");

	std::string verbosity = "quiet";
	int quietflag = 0;	
	int normalflag = 0;	
	int verboseflag = 0;	

	CLI::Option* vopt = app.add_option("-v,--Verbosity", verbosity, "Logging Level")->check(CLI::IsMember({"quiet","normal","verbose"}))->group("Logging Level");	 
	CLI::Option* qflag = app.add_flag("--quiet", quietflag, "Quiet Logging Mode flag")->group("Logging Level");
	CLI::Option* noflag = app.add_flag("--normal", normalflag, "Normal Logging Mode flag")->group("Logging Level");
	CLI::Option* vflag = app.add_flag("--verbose", verboseflag, "Verbose Mode flag")->group("Logging Level");

	app.set_config("--config", ".\\config\\config.ini", "Configuration File", false);

	try{
		app.parse(argc, argv);
	}
	catch (const CLI::ParseError &e){
		app.exit(e);
	}

	//std::cout << app.config_to_str(true, true) << std::endl;

	// Generate the actual config file
 	std::ofstream config_stream(CURRENT_CONFIG_FILE);

	//Resolving operation mode
	int modflag = nativeflag + staticflag+ dynamicflag+ disassmblerflag;
	if(mopt->count()){
		if(modflag){
			std::cout << "Mode Flags cannot be used at the same time as Mode Option. Flags will be ignored. \nMode: " << mode << "\n"; 
		}
	}	
	else{
		if(modflag > 1){
			std::cout << "Conflicting Modes, Please provide only one working mode!\n";
			exit(-1);
		}
		else{
			if(nativeflag) mode = "native"; 
			else if(staticflag) mode = "static";
			else if(disassmblerflag) mode = "disassembler";
		}
	}
	config_stream << mode << std::endl;
	// (Done) Resolving operation mode

	//Resolving optimzation level and code pointer
	if(oopt->count()){
		if((mode == "native")||(mode == "static")){
			std::cout << "OptLevel will be ignored in native and static mode!\n"; 
		}
		else{
			config_stream << optlevel << std::endl;
		}
	}
	if(mode == "static")
	{
		config_stream << code_pointer << std::endl;
	}
	else if (code_pointer)
	{
		std::cout << "CodePointer in nonstatic mode will be ignored!\n";
	}
	// (Done) Resolving optimzation level

	//Resolving Debug level
	int verbosityflags = quietflag + normalflag + verboseflag;
	if(vopt->count()){
		if(verbosityflags){
			std::cout << "Verbosity Flags cannot be used at the same time as Verbosity Option. Flags will be ignored. \nVerbosity Level: " << verbosity << "\n"; 
		}
	}
	else{
		if(verbosityflags > 1){
			std::cout << "Conflicting Verbosity Level, Please provide only one!\n";
			exit(-1);
		}
		else{
			if(normalflag) verbosity = "normal"; 
			else if(verboseflag) verbosity = "verbose";
		}
	}
	config_stream << verbosity << std::endl;
	//(Done) Resolving Debug level


	//Passing the rest of arguments to target process
	std::vector<std::string> target_vector = app.remaining(false);

	if(target_vector.size()==0)
		RLBinUtils::RLBin_Error("File name of the target application is not provided. RL-Bin will exit! \n", __FILENAME__, __LINE__);
	else
		RLBinUtils::CheckFileExists(target_vector[0].c_str(), "Target application cannot be found. RL-Bin will exit! \n");

	std::string target;

	for (int i = 0; i < target_vector.size(); i++)
	{
		target.append(target_vector[i]);
		target.append(" ");
	}
	return target;
}