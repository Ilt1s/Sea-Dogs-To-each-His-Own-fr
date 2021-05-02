#include "SD\TEXT\DIALOGS\Quest_Citizen.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CZ[0], DLG_TEXT_CZ[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CZ[2], DLG_TEXT_CZ[3]);
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase(DLG_TEXT_CZ[10],DLG_TEXT_CZ[11],DLG_TEXT_CZ[12]);
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = DLG_TEXT_CZ[26];
				link.l1.go = "svenson";
			}
			link.l2 = DLG_TEXT_CZ[13];
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase(DLG_TEXT_CZ[14],DLG_TEXT_CZ[15],DLG_TEXT_CZ[16]);
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = DLG_TEXT_CZ[27];
				link.l1.go = "svenson_house";
			}
			link.l2 = DLG_TEXT_CZ[17];
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple(DLG_TEXT_CZ[28],DLG_TEXT_CZ[29]+DLG_TEXT_CZ[30]);
			link.l1 = DLG_TEXT_CZ[31];
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple(DLG_TEXT_CZ[32],DLG_TEXT_CZ[33]);
			link.l1 = DLG_TEXT_CZ[34];
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}