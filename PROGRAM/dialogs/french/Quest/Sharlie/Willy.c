#include "SD\TEXT\DIALOGS\Quest\Sharlie\Willy.h"
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
		
		case "catoche":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = TimeGreeting()+DLG_TEXT_Q[3];
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("VOICE\Russian\sharlie\Willie Paterson.wav");
			dialog.text = DLG_TEXT_Q[18]+TimeGreeting()+DLG_TEXT_Q[19];
			link.l1 = TimeGreeting()+DLG_TEXT_Q[20];
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = DLG_TEXT_Q[27];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = DLG_TEXT_Q[28];
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[29];
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = DLG_TEXT_Q[30];
				link.l1 = DLG_TEXT_Q[31];
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[32];
				link.l1 = DLG_TEXT_Q[33];
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = DLG_TEXT_Q[34];
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}