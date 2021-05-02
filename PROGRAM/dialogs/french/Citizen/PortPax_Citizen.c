#include "SD\TEXT\DIALOGS\Quest_Citizen.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CZ[0], DLG_TEXT_CZ[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CZ[2], DLG_TEXT_CZ[3]);
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = DLG_TEXT_CZ[49]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_CZ[50];
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
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
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase(DLG_TEXT_CZ[51],DLG_TEXT_CZ[52],DLG_TEXT_CZ[53]);
			link.l1 = LinkRandPhrase(DLG_TEXT_CZ[54],DLG_TEXT_CZ[55],DLG_TEXT_CZ[56]);
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

