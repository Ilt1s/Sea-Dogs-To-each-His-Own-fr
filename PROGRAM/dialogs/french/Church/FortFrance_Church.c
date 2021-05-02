#include "SD\TEXT\DIALOGS\Quest_church.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[0], DLG_TEXT_CHR[1]), DLG_TEXT_CHR[2], DLG_TEXT_CHR[3],
                          DLG_TEXT_CHR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[5], DLG_TEXT_CHR[6]), DLG_TEXT_CHR[7],
                      DLG_TEXT_CHR[8], DLG_TEXT_CHR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = DLG_TEXT_CHR[86];
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = DLG_TEXT_CHR[87];
			link.l1 = DLG_TEXT_CHR[88];
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = DLG_TEXT_CHR[89];
			link.l1 = DLG_TEXT_CHR[90];
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

