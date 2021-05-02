#include "SD\TEXT\DIALOGS\Quest_Portman.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[0], DLG_TEXT_PRT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_PRT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_PRT[3],
                          DLG_TEXT_PRT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[5], DLG_TEXT_PRT[6]), DLG_TEXT_PRT[7],
                      DLG_TEXT_PRT[8], DLG_TEXT_PRT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Ѕрем€ гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			link.l1 = DLG_TEXT_PRT[68];
			link.l1.go = "Sharlie";
		}
		//<-- Ѕрем€ гасконца
		// Jason Долго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = DLG_TEXT_PRT[133];
			link.l1.go = "LH_letter";
		}		
		break;
		
		case "Sharlie":
			dialog.text = DLG_TEXT_PRT[69]+DLG_TEXT_PRT[70];
			link.l1 = DLG_TEXT_PRT[71];
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = DLG_TEXT_PRT[72]+DLG_TEXT_PRT[73];
			link.l1 = DLG_TEXT_PRT[74];
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = DLG_TEXT_PRT[75];
			link.l1 = DLG_TEXT_PRT[76];
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
		break;
				
		// Jason Долго и счастливо
		case "LH_letter":
			dialog.text = DLG_TEXT_PRT[134];
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = DLG_TEXT_PRT[135];
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = DLG_TEXT_PRT[136];
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

