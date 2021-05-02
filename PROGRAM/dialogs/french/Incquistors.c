#include "SD\TEXT\DIALOGS\Incquistors.h"
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
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
					link.l1 = DLG_TEXT_BASE[2];
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BASE[5], DLG_TEXT_BASE[6]),
							DLG_TEXT_BASE[7], DLG_TEXT_BASE[8],
							RandPhraseSimple(DLG_TEXT_BASE[9], DLG_TEXT_BASE[10]), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]), 
							DLG_TEXT_BASE[13], DLG_TEXT_BASE[14], RandPhraseSimple(DLG_TEXT_BASE[15], DLG_TEXT_BASE[16]), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);					
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = DLG_TEXT_BASE[17];
					link.l1 = DLG_TEXT_BASE[18];
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23]);	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[24], DLG_TEXT_BASE[25], DLG_TEXT_BASE[26]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[27], DLG_TEXT_BASE[28]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[30], DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[33], DLG_TEXT_BASE[34]);
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
