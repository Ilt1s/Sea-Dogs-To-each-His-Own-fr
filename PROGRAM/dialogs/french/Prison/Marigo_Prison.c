#include "SD\TEXT\DIALOGS\Quest_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = DLG_TEXT_PRS[19];
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = DLG_TEXT_PRS[137];
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = DLG_TEXT_PRS[138];
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = DLG_TEXT_PRS[139];
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = DLG_TEXT_PRS[20];
			link.l1 = DLG_TEXT_PRS[21];
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = DLG_TEXT_PRS[22];
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = DLG_TEXT_PRS[23];
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = DLG_TEXT_PRS[24];
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = DLG_TEXT_PRS[25];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = DLG_TEXT_PRS[26];
			link.l1 = DLG_TEXT_PRS[27];
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			dialog.text = DLG_TEXT_PRS[140];
			link.l1 = DLG_TEXT_PRS[141];
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = DLG_TEXT_PRS[142];
			link.l1 = DLG_TEXT_PRS[143];
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			dialog.text = DLG_TEXT_PRS[144];
			link.l1 = DLG_TEXT_PRS[145];
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = DLG_TEXT_PRS[146];
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = DLG_TEXT_PRS[147];
			link.l1 = DLG_TEXT_PRS[148];
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = DLG_TEXT_PRS[149];
			link.l1 = DLG_TEXT_PRS[150];
			link.l1.go = "FMQN_7";
			link.l2 = DLG_TEXT_PRS[151];
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = DLG_TEXT_PRS[152];
			link.l1 = DLG_TEXT_PRS[153];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			dialog.text = DLG_TEXT_PRS[154];
			link.l1 = DLG_TEXT_PRS[155];
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = DLG_TEXT_PRS[156];
			link.l1 = DLG_TEXT_PRS[157];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = DLG_TEXT_PRS[158];
			link.l1 = DLG_TEXT_PRS[159];
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = DLG_TEXT_PRS[160];
			link.l1 = DLG_TEXT_PRS[161];
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
