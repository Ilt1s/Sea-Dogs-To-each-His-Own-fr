#include "SD\TEXT\DIALOGS\Quest_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = DLG_TEXT_STR[77];
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = DLG_TEXT_STR[78];
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = DLG_TEXT_STR[79];
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = DLG_TEXT_STR[80];
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = DLG_TEXT_STR[81];
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			dialog.text = DLG_TEXT_STR[82]+DLG_TEXT_STR[83];
			link.l1 = DLG_TEXT_STR[84];
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = DLG_TEXT_STR[85];
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			dialog.text = DLG_TEXT_STR[86];
			link.l1 = "Hmm...";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = DLG_TEXT_STR[87]+DLG_TEXT_STR[88];
			link.l1 = DLG_TEXT_STR[89];
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
		break;
		
		case "Sharlie_storehelper_2":
			dialog.text = DLG_TEXT_STR[90];
			link.l1 = DLG_TEXT_STR[91];
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = DLG_TEXT_STR[92];
			link.l1 = DLG_TEXT_STR[93];
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = DLG_TEXT_STR[94];
			link.l1 = DLG_TEXT_STR[95]+npchar.name+DLG_TEXT_STR[96];
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = DLG_TEXT_STR[97]+DLG_TEXT_STR[98];
			link.l1 = DLG_TEXT_STR[99];
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = DLG_TEXT_STR[100];
			link.l1 = DLG_TEXT_STR[101];
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = DLG_TEXT_STR[102]+DLG_TEXT_STR[103]+DLG_TEXT_STR[104];
			link.l1 = DLG_TEXT_STR[105];
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = DLG_TEXT_STR[106];
			link.l1 = DLG_TEXT_STR[107];
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = DLG_TEXT_STR[108];
			link.l1 = DLG_TEXT_STR[109]+npchar.name+DLG_TEXT_STR[110];
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			AddQuestRecord("SharlieA", "3");
			pchar.quest.storehelper.win_condition.l1 = "Timer";
			pchar.quest.storehelper.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.storehelper.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.storehelper.function = "StorehelperOver";
			pchar.questTemp.Sharlie.Storehelper = "hire";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = DLG_TEXT_STR[111];
			link.l1 = DLG_TEXT_STR[112];
			link.l1.go = "Sharlie_storehelper_12";
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "wait";
			DialogExit();
			pchar.quest.storehelper5.win_condition.l1 = "Timer";
			pchar.quest.storehelper5.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.storehelper5.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper5.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper5.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper5.function = "StorehelperFinal";
			AddQuestRecord("SharlieA", "5");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = DLG_TEXT_STR[113];
					link.l1 = DLG_TEXT_STR[114];
					link.l1.go = "Sharlie_storehelper_14";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = DLG_TEXT_STR[115];
					link.l1 = DLG_TEXT_STR[116];
					link.l1.go = "Sharlie_storehelper_14";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = DLG_TEXT_STR[117];
					link.l1 = DLG_TEXT_STR[118];
					link.l1.go = "Sharlie_storehelper_14";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = DLG_TEXT_STR[119];
			link.l1 = DLG_TEXT_STR[120];
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = DLG_TEXT_STR[121];
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info(DLG_TEXT_STR[122]);
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}

