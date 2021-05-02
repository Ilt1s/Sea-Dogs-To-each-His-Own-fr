#include "SD\TEXT\DIALOGS\Quest_lighthouse.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_LI[0], DLG_TEXT_LI[1]), DLG_TEXT_LI[2] + GetAddress_Form(NPChar) + " ?", DLG_TEXT_LI[3], DLG_TEXT_LI[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_LI[5], DLG_TEXT_LI[6]), DLG_TEXT_LI[7],
                      DLG_TEXT_LI[8], DLG_TEXT_LI[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}



