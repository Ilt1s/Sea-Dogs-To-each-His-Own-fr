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
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = DLG_TEXT_STR[133];
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = DLG_TEXT_STR[526];
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && GetCharacterItem(pchar, "gold_dublon") >= 50)
            {
                link.l1 = DLG_TEXT_STR[527];
                link.l1.go = "mtraxx_4_1";
			}			
		break;

		case "Jamaica_ratF_1":
			dialog.text = DLG_TEXT_STR[134];
			link.l1 = DLG_TEXT_STR[135];
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = DLG_TEXT_STR[136];
			link.l1 = DLG_TEXT_STR[137];
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = DLG_TEXT_STR[138];
			link.l1 = DLG_TEXT_STR[139];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = DLG_TEXT_STR[528];
			link.l1 = DLG_TEXT_STR[529];
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = DLG_TEXT_STR[530];
			link.l1 = DLG_TEXT_STR[531];
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = DLG_TEXT_STR[532];
			link.l1 = DLG_TEXT_STR[533];
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = DLG_TEXT_STR[534];
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = DLG_TEXT_STR[535];
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = DLG_TEXT_STR[536];
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveItems(pchar, "gold_dublon", 50);
			Log_Info(DLG_TEXT_STR[537]);
			PlaySound("interface\important_item.wav");
            dialog.text = DLG_TEXT_STR[538];
			link.l1 = DLG_TEXT_STR[539];
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = DLG_TEXT_STR[540];
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
