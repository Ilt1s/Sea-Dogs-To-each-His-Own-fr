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
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase(DLG_TEXT_BASE[167],DLG_TEXT_BASE[168]) +DLG_TEXT_BASE[169], 
				DLG_TEXT_BASE[170]+ GetSexPhrase(DLG_TEXT_BASE[171],DLG_TEXT_BASE[172]) +".", 
				""+ GetSexPhrase(DLG_TEXT_BASE[173],DLG_TEXT_BASE[174]) +"",
                DLG_TEXT_BASE[175] + GetSexPhrase(DLG_TEXT_BASE[176],DLG_TEXT_BASE[177]) + DLG_TEXT_BASE[178], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[179], 
				DLG_TEXT_BASE[180],
                DLG_TEXT_BASE[181], 
				DLG_TEXT_BASE[182], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[183];
				link.l1 = DLG_TEXT_BASE[184];
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[185],DLG_TEXT_BASE[186]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[187],DLG_TEXT_BASE[188],DLG_TEXT_BASE[189]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
