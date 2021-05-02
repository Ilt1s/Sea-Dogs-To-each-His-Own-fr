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
			link.l1 = DLG_TEXT_CZ[18];
			link.l1.go = "fadey";
			link.l2 = DLG_TEXT_CZ[13];
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase(DLG_TEXT_CZ[14],DLG_TEXT_CZ[15],DLG_TEXT_CZ[16]);
            link.l1 = DLG_TEXT_CZ[19];
			link.l1.go = "fadey_house";
			link.l2 = DLG_TEXT_CZ[17];
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple(DLG_TEXT_CZ[20],DLG_TEXT_CZ[21]);
			link.l1 = DLG_TEXT_CZ[22];
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple(DLG_TEXT_CZ[23],DLG_TEXT_CZ[24]);
			link.l1 = DLG_TEXT_CZ[25];
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

