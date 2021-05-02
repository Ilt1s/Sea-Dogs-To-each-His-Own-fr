#include "SD\TEXT\DIALOGS\Convict_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[0],DLG_TEXT_BASE[1],DLG_TEXT_BASE[2],DLG_TEXT_BASE[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[4],DLG_TEXT_BASE[5],DLG_TEXT_BASE[6], "Hmm...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = DLG_TEXT_BASE[7];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[8],DLG_TEXT_BASE[9],DLG_TEXT_BASE[10]);
			link.l1.go = "exit";
		break;  
	}
}