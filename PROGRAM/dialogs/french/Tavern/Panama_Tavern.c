#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[73]+ GetCityName(npchar.city) +DLG_TEXT_STR[74],
                          DLG_TEXT_STR[75], DLG_TEXT_STR[76],
                          DLG_TEXT_STR[77], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[78] + NPChar.name + DLG_TEXT_STR[79], DLG_TEXT_STR[80],
                      DLG_TEXT_STR[81], DLG_TEXT_STR[82], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = DLG_TEXT_STR[140];
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = DLG_TEXT_STR[521];
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[141], DLG_TEXT_STR[142], DLG_TEXT_STR[143], DLG_TEXT_STR[144], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[145], DLG_TEXT_STR[146], DLG_TEXT_STR[147], DLG_TEXT_STR[148] + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = DLG_TEXT_STR[149];
			link.l1 = DLG_TEXT_STR[150];
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = DLG_TEXT_STR[522];
			link.l1 = DLG_TEXT_STR[523];
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = DLG_TEXT_STR[524];
			link.l1 = DLG_TEXT_STR[525];
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

