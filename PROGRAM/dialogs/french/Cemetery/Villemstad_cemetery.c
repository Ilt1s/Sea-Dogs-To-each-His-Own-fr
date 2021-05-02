#include "SD\TEXT\DIALOGS\Quest_cemeteryman.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CE[0], DLG_TEXT_CE[1]), DLG_TEXT_CE[2] + GetAddress_Form(NPChar) + " ?", DLG_TEXT_CE[3], DLG_TEXT_CE[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CE[5], DLG_TEXT_CE[6]), DLG_TEXT_CE[7],
                      DLG_TEXT_CE[8], DLG_TEXT_CE[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}