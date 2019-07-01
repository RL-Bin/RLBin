/**
 * @file StatUnit.cpp
 * @brief Defines the body of functions in StatUnit class.
 */

#include <list>
#include <algorithm>

#include <iostream>
#include "..\include\StatUnit\StatUnit.h"

#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\SubUnits\Config\Config.h"
#include "..\include\SubUnits\Disassembler\Disassembler.h"

// inititalizing the only instace of class 
StatUnit* StatUnit::s_instance = NULL;

StatUnit* StatUnit::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of StatUnit exists", __FILENAME__, __LINE__);
		return NULL;
	}
	RLBinUtils::RLBin_Log("StatUnit Created!", __FILENAME__);
	s_instance = new StatUnit();
	return s_instance;
}

StatUnit* StatUnit::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("StatUnit is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void StatUnit::Run() 
{
	Modules::Create();
	Modules::Get()->Initialize();

	Disassembler::Create();

	// if config file needs data reference, add them to the list to_be_disassembled
	if(Config::Get()->GetFeatureValue("UseCodePointers") == 1)
	{
		AddDataRefs();
	}

	Modules::Get()->PrintModulesShort();
	
	RecursiveDisassembly();

	PrintDisassembly();

	ExitProcess(0);
}

void StatUnit::RecursiveDisassembly() 
{
    if(!CheckList(to_be_disassembled, Modules::Get()->GetEntryPoint()))
    {
    	to_be_disassembled.push_back(Modules::Get()->GetEntryPoint());	
    }

    while(!to_be_disassembled.empty())
    {

    	//RLBinUtils::RLBin_Static(RLBinUtils::ConvertHexToString(to_be_disassembled.front()));
    	//if(IsValidInstAndTarget(to_be_disassembled.front()))
    	//{
    	//	Disassembler::Get()->PrintInst(to_be_disassembled.front(), T_STATIC);
    	//}
    	
    	if(!IsValidInstAndTarget(to_be_disassembled.front()))
    	{
			to_be_disassembled.pop_front();
		}
    	else if(Disassembler::Get()->IsInstDirectJump(to_be_disassembled.front())) // Direct Jump
    	{
    		// find out the destination of call or jump
    		ADDRESS dest; 
    		Disassembler::Get()->GetDirectCTIDest(to_be_disassembled.front(), &dest);
    		//RLBinUtils::RLBin_Static("\t\t" + RLBinUtils::ConvertHexToString(dest));
			// add dest to the list to be discovered if it's not in either list
		    if((!CheckList(to_be_disassembled, dest))&&(!CheckList(disassembled, dest)))
		    {
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(dest));
		    	to_be_disassembled.push_back(dest);	
		    }

			// remove the current instruction from to be discovered and add it to discovered
		    disassembled.push_back(to_be_disassembled.front());
		    to_be_disassembled.pop_front();
    	}
    	else if(Disassembler::Get()->IsInstDirectCall(to_be_disassembled.front())) // Direct Call
    	{
    		// find out the destination of call or jump
    		ADDRESS dest; 
    		Disassembler::Get()->GetDirectCTIDest(to_be_disassembled.front(), &dest);
    		//RLBinUtils::RLBin_Static("\t\t" + RLBinUtils::ConvertHexToString(dest));
    		// add dest to the list to be discovered if it's not in either list
		    if((!CheckList(to_be_disassembled, dest))&&(!CheckList(disassembled, dest)))
		    {
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(dest));
		    	to_be_disassembled.push_back(dest);	
		    }

   			ADDRESS next = to_be_disassembled.front() + Disassembler::Get()->GetInstSize(to_be_disassembled.front());
    		// add next to the list to be discovered if it's not in either list
    		//RLBinUtils::RLBin_Static("\t\t" + RLBinUtils::ConvertHexToString(next));    		
		    if((!CheckList(to_be_disassembled, next))&&(!CheckList(disassembled, next)))
		    {
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(next));		    	
		    	to_be_disassembled.push_back(next);	
		    }

			// remove the current instruction from to be discovered and add it to discovered
		    disassembled.push_back(to_be_disassembled.front());
		    to_be_disassembled.pop_front();

		    // add dest to the list of called addresses
		    if(!CheckList(static_funcs, dest))
		    {
		    	static_funcs.push_back(dest);	
		    }
    	}
    	else if((Disassembler::Get()->IsInstRet(to_be_disassembled.front())) || (Disassembler::Get()->IsInstIndirectJump(to_be_disassembled.front()))) // return or indirect jmp
    	{
    		// remove the current instruction from to be discovered and add it to discovered
		    disassembled.push_back(to_be_disassembled.front());    		
    		to_be_disassembled.pop_front();	
    	}
    	else if(Disassembler::Get()->IsInstIndirectCall(to_be_disassembled.front())) // indirect call
    	{
    		ADDRESS next = to_be_disassembled.front() + Disassembler::Get()->GetInstSize(to_be_disassembled.front());
    		// add next to the list to be discovered if it's not in either list
    		//RLBinUtils::RLBin_Static("\t\t" + RLBinUtils::ConvertHexToString(next));    		
		    if((!CheckList(to_be_disassembled, next))&&(!CheckList(disassembled, next)))
		    {
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(next));
		    	to_be_disassembled.push_back(next);	
		    }

    		// remove the current instruction from to be discovered and add it to discovered
    		disassembled.push_back(to_be_disassembled.front());
    		to_be_disassembled.pop_front();	
    	}
    	else if(Disassembler::Get()->IsInstConditionalJump(to_be_disassembled.front())) // conditional jump
    	{
    		ADDRESS dest[2]; 
    		Disassembler::Get()->GetConditionalCTIDest(to_be_disassembled.front(), dest);
    		// add dest to the list to be discovered if it's not in either list
    		//RLBinUtils::RLBin_Static("\t\t" + RLBinUtils::ConvertHexToString(dest[0]));
		    if((!CheckList(to_be_disassembled, dest[0]))&&(!CheckList(disassembled, dest[0])))
		    {
		    	to_be_disassembled.push_back(dest[0]);
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(dest[0]));
		    }
   			//RLBinUtils::RLBin_Static("\t\tCCC" + RLBinUtils::ConvertHexToString(dest[1]));
		    if((!CheckList(to_be_disassembled, dest[1]))&&(!CheckList(disassembled, dest[1])))
		    {
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(dest[1]));
		    	to_be_disassembled.push_back(dest[1]);	
		    }

    		// remove the current instruction from to be discovered and add it to discovered
    		disassembled.push_back(to_be_disassembled.front());
    		to_be_disassembled.pop_front();	
    	}
    	else if((* (byte *)to_be_disassembled.front()) == 0XCC) // int 3 does not go to next instruction
    	{
 		   	// remove the current instruction from to be discovered and add it to discovered
		    disassembled.push_back(to_be_disassembled.front());
		    to_be_disassembled.pop_front();	
    	}
    	else // NormalCase
    	{
    		ADDRESS next = to_be_disassembled.front() + Disassembler::Get()->GetInstSize(to_be_disassembled.front());
    		// add next to the list to be discovered if it's not in either list
    		//RLBinUtils::RLBin_Static("\t\t" + RLBinUtils::ConvertHexToString(next));
		    if((!CheckList(to_be_disassembled, next))&&(!CheckList(disassembled, next)))
		    {
		    	//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(next));		    	
		    	to_be_disassembled.push_back(next);	
		    }

 		   	// remove the current instruction from to be discovered and add it to discovered
		    disassembled.push_back(to_be_disassembled.front());
		    to_be_disassembled.pop_front();	
    	}
    }
}

bool StatUnit::CheckList(std::list<ADDRESS> input_list, ADDRESS to_be_checked)
{
	std::list<ADDRESS>::iterator findIter = std::find(input_list.begin(), input_list.end(), to_be_checked);
    if(findIter == input_list.end())
		return false;
	else
		return true;
}

void StatUnit::PrintDisassembly()
{	
	int code_coverage = 0;
	int inst_coverage = 0;

	disassembled.sort();

	std::list<ADDRESS>::iterator it;
	for(it=disassembled.begin(); it!=disassembled.end(); ++it)
	{
		code_coverage += Disassembler::Get()->GetInstSize(*it);
		inst_coverage ++;
	}
	
	RLBinUtils::RLBin_Static("____________________________________________________________");
	RLBinUtils::RLBin_Static("                         Summary");
	RLBinUtils::RLBin_Static("____________________________________________________________");
	RLBinUtils::RLBin_Static("Code Coverage:	" + RLBinUtils::ConvertIntToString(code_coverage) + " bytes");
	SIZE_TYPE text_sec_size = Modules::Get()->GetMainModule()->sections.front().size;
	RLBinUtils::RLBin_Static("				(out of " + RLBinUtils::ConvertIntToString(text_sec_size) +
							 " bytes in .text) --> " + RLBinUtils::ConvertIntToString((100*code_coverage/text_sec_size)) + "%");
	RLBinUtils::RLBin_Static("Inst Coverage:	" + RLBinUtils::ConvertIntToString(inst_coverage)+ " instructions");
	RLBinUtils::RLBin_Static("Func Coverage:	" + RLBinUtils::ConvertIntToString(static_funcs.size())+ " functions");
	

	RLBinUtils::RLBin_Static("\n____________________________________________________________");
	RLBinUtils::RLBin_Static("                        Disassembly");
	RLBinUtils::RLBin_Static("____________________________________________________________");

	for(it=disassembled.begin(); it!=disassembled.end(); ++it)
	{
		if(CheckList(static_funcs, *it))
		{
			RLBinUtils::RLBin_Static("______________________________");
		}
		Disassembler::Get()->PrintInst(*it, T_STATIC);
	}
}

void StatUnit::AddDataRefs()
{
	SectionInfo code;
	SectionInfo data;
	for(std::list<SectionInfo>::iterator it = Modules::Get()->GetMainModule()->sections.begin(); 
		it != Modules::Get()->GetMainModule()->sections.end(); it++)
	{
		if(it->name == ".text")
		{
			code = *it;
		}
		if(it->name == ".rdata")
		{
			data = *it;
		}
	}

	byte * pstart = (byte *) data.base;
	byte * pend = (byte *) (data.base+data.size);
	for(byte *p = pstart; p<pend; p++)
	{
		ADDRESS code_pointer = *(ADDRESS *)p;
		if((code_pointer>code.base)&&(code_pointer<=(code.base+code.size)))
		{
			if(!CheckList(to_be_disassembled, code_pointer))
		    {
		    	if(IsValidInstAndTarget(code_pointer))
    			{
    				//RLBinUtils::RLBin_Static("PUSHTBD " + RLBinUtils::ConvertHexToString(code_pointer));
		    		to_be_disassembled.push_back(code_pointer);
		    	}	
		    }
		}
	}

}

bool StatUnit::IsValidInstAndTarget(ADDRESS address)
{
	if(!Disassembler::Get()->IsValidInst(address))
	{
		RLBinUtils::RLBin_Debug("Impossible to disassemble at Address " + RLBinUtils::ConvertHexToString(address), __FILENAME__, __LINE__);
		return false;
	}

    if(Disassembler::Get()->IsInstDirectCTI(address)) // Direct Jump or call
    {
		// find out the destination of call or jump
		ADDRESS dest; 
		Disassembler::Get()->GetDirectCTIDest(address, &dest);

		if(!Modules::Get()->IsInsideMainCode(dest))
		{
			RLBinUtils::RLBin_Debug("Out of range target address " + RLBinUtils::ConvertHexToString(dest), __FILENAME__, __LINE__);
			Disassembler::Get()->PrintInst(address,T_DEBUG);
			return false;
		}
    }
	else if(Disassembler::Get()->IsInstConditionalJump(address)) // conditional jump
    {
    	ADDRESS dest[2]; 
    	Disassembler::Get()->GetConditionalCTIDest(address, dest);
    	// add dest to the list to be discovered if it's not in either list
		if(!Modules::Get()->IsInsideMainCode(dest[0]))
		{
			RLBinUtils::RLBin_Debug("Out of range target address " + RLBinUtils::ConvertHexToString(dest[0]), __FILENAME__, __LINE__);
			Disassembler::Get()->PrintInst(address,T_DEBUG);
			return false;
		}
		if(!Modules::Get()->IsInsideMainCode(dest[1]))
		{
			RLBinUtils::RLBin_Debug("Out of range target address " + RLBinUtils::ConvertHexToString(dest[0]), __FILENAME__, __LINE__);
			Disassembler::Get()->PrintInst(address,T_DEBUG);
			return false;
		}
	}
	return true;
}