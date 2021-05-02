#include "SD\TEXT\DIALOGS\Quest\LineMiniQuests\FMQ_Martinique.h"
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "An obvious bug. Tell the devs about it.";
			link.l1 = "Oh, I will.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			dialog.text = TimeGreeting()+DLG_TEXT_Q[0]+GetFullName(npchar)+DLG_TEXT_Q[1];
			link.l1 = DLG_TEXT_Q[2];
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = DLG_TEXT_Q[3]+sTemp+DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5]+GetFullName(npchar)+" ?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			dialog.text = DLG_TEXT_Q[6]+GetFullName(sld)+DLG_TEXT_Q[7];
			link.l1 = DLG_TEXT_Q[8];
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("VOICE\Russian\soldier_arest_4.wav");
			dialog.text = DLG_TEXT_Q[9];
			link.l1 = "Eh...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("VOICE\Russian\soldier\soldier arest-02.wav");
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20]+GetFullName(characterFromId("FortFrance_shipyarder"))+DLG_TEXT_Q[21];
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "officer_13";
			link.l2 = DLG_TEXT_Q[26];
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			dialog.text = DLG_TEXT_Q[30];
			link.l1 = DLG_TEXT_Q[31];
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = DLG_TEXT_Q[32]+GetFullName(pchar)+DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = DLG_TEXT_Q[51]+GetFullName(characterFromId("FortFrance_shipyarder"))+DLG_TEXT_Q[52]+GetFullName(characterFromId("FortFrance_shipyarder"))+DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = DLG_TEXT_Q[55]+pchar.name+DLG_TEXT_Q[56]+GetFullName(characterFromId("FortFrance_shipyarder"))+DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = DLG_TEXT_Q[59]+pchar.name+DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = DLG_TEXT_Q[62]+GetFullName(characterFromId("FortFrance_shipyarder"))+DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = DLG_TEXT_Q[65]+pchar.name+DLG_TEXT_Q[66]+GetFullName(characterFromId("FortFrance_shipyarder"))+DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			dialog.text = DLG_TEXT_Q[71]+GetFullName(pchar)+" !";
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "pirate_1";
		break;
		
		case "pirate_1":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
