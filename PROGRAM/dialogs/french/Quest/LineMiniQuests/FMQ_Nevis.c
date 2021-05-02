#include "SD\TEXT\DIALOGS\Quest\LineMiniQuests\FMQ_Nevis.h"
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
		
		case "seafox":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = TimeGreeting()+DLG_TEXT_Q[0]+GetFullName(npchar)+DLG_TEXT_Q[1];
			link.l1 = DLG_TEXT_Q[2]+GetFullName(pchar)+DLG_TEXT_Q[3];
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "seafox_3";
			link.l2 = DLG_TEXT_Q[8];
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info(DLG_TEXT_Q[11]);
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "FMQN_SailMaarten", 10.0);
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
		break;
		
		case "seafox_6":
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("VOICE\Russian\soldier_common_4.wav");
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47]
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			PlaySound("Ambient\Land\cough_01.wav");
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = ""+RandSwear()+" !!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = DLG_TEXT_Q[55];
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = DLG_TEXT_Q[56];
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[57];
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("VOICE\Russian\Gr_hovernor01.wav");
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = DLG_TEXT_Q[64];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("VOICE\Russian\QuestMan05.wav");
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("VOICE\Russian\QuestMan05.wav");
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("VOICE\Russian\soldier_common_2.wav");
			dialog.text = DLG_TEXT_Q[73]+GetFullName(pchar)+" ?";
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("VOICE\Russian\hol_gov_complete.wav");
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("VOICE\Russian\hol_gov_quest.wav");
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("VOICE\Russian\hol_gov_common.wav");
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = DLG_TEXT_Q[100];
			if (GetCharacterItem(pchar, "gold_dublon") >= 24)
			{
				link.l1 = DLG_TEXT_Q[101];
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[102];
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			sld.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = DLG_TEXT_Q[103];
			if (GetCharacterItem(pchar, "gold_dublon") >= 24)
			{
				link.l1 = DLG_TEXT_Q[104];
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[105];
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveItems(pchar, "gold_dublon", 24);
			Log_Info(DLG_TEXT_Q[106]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[107];
			link.l1 = DLG_TEXT_Q[108];
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = DLG_TEXT_Q[109];
			link.l1 = DLG_TEXT_Q[110];
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
