#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[83], DLG_TEXT_STR[84] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_STR[85] + GetAddress_Form(NPChar) + "...", DLG_TEXT_STR[86],
                          DLG_TEXT_STR[87], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[88], DLG_TEXT_STR[89]), DLG_TEXT_STR[90],
                      DLG_TEXT_STR[91], DLG_TEXT_STR[92], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";				
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = DLG_TEXT_STR[242] + npchar.name + DLG_TEXT_STR[243];
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = DLG_TEXT_STR[244];
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "Vous savez, " + npchar.name + DLG_TEXT_STR[245];
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = DLG_TEXT_STR[246];
			link.l1 = DLG_TEXT_STR[247];
			link.l1.go = "storehelper_1";
			npchar.quest.storehelper = "true";
		break;
		
		case "storehelper_1":
			dialog.text = DLG_TEXT_STR[248];
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = DLG_TEXT_STR[249];
				link.l1.go = "storehelper_2";
			}
			link.l2 = DLG_TEXT_STR[250];
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = DLG_TEXT_STR[251];
			link.l1 = DLG_TEXT_STR[252] + npchar.name + ".";
			link.l1.go = "storehelper_3";
		break;
		
		case "storehelper_3":
			DialogExit();
			pchar.quest.storehelper1.win_condition.l1 = "Timer";
			pchar.quest.storehelper1.win_condition.l1.date.hour  = sti(GetTime() + 1);
			pchar.quest.storehelper1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l2 = "location";
			pchar.quest.storehelper1.win_condition.l2.location = "lefransua_tavern";
			pchar.quest.storehelper1.function = "Storehelper_hire";
		break;
		
		case "storehelper_exit":
			dialog.text = DLG_TEXT_STR[253];
			link.l1 = DLG_TEXT_STR[254];
			link.l1.go = "exit";
			pchar.quest.storehelper.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			dialog.text = DLG_TEXT_STR[255];
			link.l1 = DLG_TEXT_STR[256];
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = DLG_TEXT_STR[257];
			link.l1 = DLG_TEXT_STR[258];
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = DLG_TEXT_STR[259];
			link.l1 = DLG_TEXT_STR[260];
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = DLG_TEXT_STR[261];
			link.l1 = DLG_TEXT_STR[262];
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
		break;
		
		case "Portugal":
			dialog.text = DLG_TEXT_STR[263];
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

