#include "SD\TEXT\DIALOGS\Pearl_dialog.h"
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
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[71] + GetFullName(npchar) + DLG_TEXT_BASE[72], 
				DLG_TEXT_BASE[73], 
				DLG_TEXT_BASE[74],
                DLG_TEXT_BASE[75], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[76], 
				DLG_TEXT_BASE[77],
                DLG_TEXT_BASE[78], 
				DLG_TEXT_BASE[79], npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = DLG_TEXT_BASE[83] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[86];
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = DLG_TEXT_BASE[87];
				link.l1 = DLG_TEXT_BASE[88];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[89];
				link.l1 = DLG_TEXT_BASE[90];
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[91], 
				DLG_TEXT_BASE[92], 
				DLG_TEXT_BASE[93]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[94], DLG_TEXT_BASE[95]);
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[96], 
				DLG_TEXT_BASE[97], 
				DLG_TEXT_BASE[98],
                DLG_TEXT_BASE[99], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[100], 
				DLG_TEXT_BASE[101],
                DLG_TEXT_BASE[102], 
				DLG_TEXT_BASE[103], npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = DLG_TEXT_BASE[104];
			link.l1 = DLG_TEXT_BASE[105];
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Baissez cette arme capitaine, vous allez avoir des ennuis sinon !";
			link.l1 = LinkRandPhrase("Bien.", "D'accord.", "Ne vous tracassez pas pour si peu...");
			link.l1.go = "exit";
		break;  

	}
}
