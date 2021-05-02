#include "SD\TEXT\DIALOGS\Common_population.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[33], 
				DLG_TEXT_BASE[34], 
				DLG_TEXT_BASE[35],
                DLG_TEXT_BASE[36], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[37], 
				DLG_TEXT_BASE[38],
                DLG_TEXT_BASE[39], 
				DLG_TEXT_BASE[40], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[41]+npchar.dialog.Filename;
				link.l1 = DLG_TEXT_BASE[42];
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[43],DLG_TEXT_BASE[44]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[45],DLG_TEXT_BASE[46],DLG_TEXT_BASE[47]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
