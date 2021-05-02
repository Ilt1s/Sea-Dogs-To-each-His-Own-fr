#include "SD\TEXT\DIALOGS\Quest\Sharlie\Maldonado.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = DLG_TEXT_Q[2]+GetFullName(pchar)+"...";
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = DLG_TEXT_Q[26];
			link.l1 = DLG_TEXT_Q[27];
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}