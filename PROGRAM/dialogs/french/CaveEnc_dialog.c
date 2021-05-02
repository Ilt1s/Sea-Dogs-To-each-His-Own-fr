#include "SD\TEXT\DIALOGS\CaveEnc_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (drand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7], DLG_TEXT_BASE[8], DLG_TEXT_BASE[9], npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10],DLG_TEXT_BASE[11],DLG_TEXT_BASE[12]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[13],DLG_TEXT_BASE[14],DLG_TEXT_BASE[15]);
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[16],DLG_TEXT_BASE[17],DLG_TEXT_BASE[18]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[19],DLG_TEXT_BASE[20],DLG_TEXT_BASE[21]);
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23], DLG_TEXT_BASE[24], DLG_TEXT_BASE[25], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[26], DLG_TEXT_BASE[27], DLG_TEXT_BASE[28], DLG_TEXT_BASE[29], npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (drand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[30]+npchar.name+DLG_TEXT_BASE[31], DLG_TEXT_BASE[32], DLG_TEXT_BASE[33], DLG_TEXT_BASE[34], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[35], DLG_TEXT_BASE[36], DLG_TEXT_BASE[37], DLG_TEXT_BASE[38], npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[39],DLG_TEXT_BASE[40],DLG_TEXT_BASE[41]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[42],DLG_TEXT_BASE[43],DLG_TEXT_BASE[44]);
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[45],DLG_TEXT_BASE[46],DLG_TEXT_BASE[47]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[48],DLG_TEXT_BASE[49],DLG_TEXT_BASE[50]);
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}