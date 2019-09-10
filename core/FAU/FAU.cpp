/**
 * @file FAU.cpp
 * @brief Defines the body of functions in FAU class.
 */

#include "..\include\FAU\FAU.h"

// inititalizing the only instace of class 
FAU* FAU::s_instance = NULL;

FAU* FAU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of FAU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new FAU();
	return s_instance;
}

FAU* FAU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("FAU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void FAU::Initialize(void) 
{
	count__new_code = 0;
	count__handle_missed = 0;	
	count__check_0xC3 = 0;
	count__check_0xF2C3 = 0;
	count__check_0xC2 = 0;
	count__check_0xFFD = 0;	
	count__check_0xFF5 = 0;	
	count__check_0x3EFFE = 0;
	count__check_0xFF15 = 0;
	count__check_0xFF25 = 0;
	count__check_0xFF2485 = 0;
	count__total = 0;	
	return;
}

void FAU::PrintCounters(void) 
{
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed                            : " + RLBinUtils::ConvertIntToString(count__total));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring Ret C3 Check  ) : " + RLBinUtils::ConvertIntToString(count__check_0xC3));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring Ret F2C3 Check) : " + RLBinUtils::ConvertIntToString(count__check_0xF2C3));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring Ret C2 Check  ) : " + RLBinUtils::ConvertIntToString(count__check_0xC2));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring IAT FF15 Check) : " + RLBinUtils::ConvertIntToString(count__check_0xFF15));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring IAT FF25 Check) : " + RLBinUtils::ConvertIntToString(count__check_0xFF25));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring FFD Check     ) : " + RLBinUtils::ConvertIntToString(count__check_0xFFD));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring FF5 Check     ) : " + RLBinUtils::ConvertIntToString(count__check_0xFF5));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring 3EFFE Check   ) : " + RLBinUtils::ConvertIntToString(count__check_0x3EFFE));	
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Recurring FF2485 Check  ) : " + RLBinUtils::ConvertIntToString(count__check_0xFF2485));	
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (New Code Discovery      ) : " + RLBinUtils::ConvertIntToString(count__new_code));
	RLBinUtils::RLBin_OptStat("# of Exceptions Executed (Mishandled Check        ) : " + RLBinUtils::ConvertIntToString(count__handle_missed));
	return;
}