#include "SD\TEXT\DIALOGS\Quest_Citizen.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CZ[0], DLG_TEXT_CZ[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CZ[2], DLG_TEXT_CZ[3]);
		    link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = DLG_TEXT_CZ[35]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_CZ[36];
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = DLG_TEXT_CZ[37]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_CZ[38];
                link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких ЌЏ‘, по квестам
			dialog.text = DLG_TEXT_CZ[4]+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = DLG_TEXT_CZ[5];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[6];
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = DLG_TEXT_CZ[7];
            link.l1 = DLG_TEXT_CZ[8];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[9];
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = DLG_TEXT_CZ[39];
				link.l1 = DLG_TEXT_CZ[40];
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_CZ[41],DLG_TEXT_CZ[42],DLG_TEXT_CZ[43]);
				link.l1 = DLG_TEXT_CZ[44];
				link.l1.go = "exit";
				pchar.questTemp.Sharlie.Citcount = sti(pchar.questTemp.Sharlie.Citcount)+1;
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_CZ[45],DLG_TEXT_CZ[46],DLG_TEXT_CZ[47]);
			link.l1 = DLG_TEXT_CZ[48];
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}