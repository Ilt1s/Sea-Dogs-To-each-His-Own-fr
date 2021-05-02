#include "SD\TEXT\DIALOGS\Quest\HollandGambit\Merdok.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = DLG_TEXT_Q[2];
				link.l1 = DLG_TEXT_Q[3];
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = DLG_TEXT_Q[6];
				link.l1 = DLG_TEXT_Q[7];
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = DLG_TEXT_Q[8];
				link.l1 = DLG_TEXT_Q[9];
				link.l1.go = "Knippel";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = DLG_TEXT_Q[10];
				link.l1 = DLG_TEXT_Q[11];
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "Merdok_talk";
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = DLG_TEXT_Q[16];
					link.l1 = DLG_TEXT_Q[17];
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = DLG_TEXT_Q[18] + pchar.name + " !";
					link.l1 = DLG_TEXT_Q[19];
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = DLG_TEXT_Q[20];
					link.l1 = DLG_TEXT_Q[21];
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = DLG_TEXT_Q[22] + pchar.name + DLG_TEXT_Q[23];
					link.l1 = DLG_TEXT_Q[24];
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = DLG_TEXT_Q[25];
					link.l1 = DLG_TEXT_Q[26];
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = DLG_TEXT_Q[27];
					link.l1 = DLG_TEXT_Q[28];
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = DLG_TEXT_Q[29];
					link.l1 = DLG_TEXT_Q[30];
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = DLG_TEXT_Q[31];
					link.l1 = DLG_TEXT_Q[32];
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = DLG_TEXT_Q[33];
					link.l1 = DLG_TEXT_Q[34];
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "" + pchar.name + DLG_TEXT_Q[35];
					link.l1 = DLG_TEXT_Q[36];
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					dialog.text = DLG_TEXT_Q[37] + pchar.name + DLG_TEXT_Q[38];
					link.l1 = DLG_TEXT_Q[39];
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					dialog.text = DLG_TEXT_Q[40] + pchar.name + DLG_TEXT_Q[41];
					link.l1 = DLG_TEXT_Q[42];
					link.l1.go = "Final";
					break;
				}
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "exit";
			break;
			}
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("VOICE\Russian\hambit\John Mardock-07.wav");
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("VOICE\Russian\hambit\John Mardock-02.wav");
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = DLG_TEXT_Q[71];
				link.l1 = DLG_TEXT_Q[72];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[73];
				link.l1 = DLG_TEXT_Q[74];
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = DLG_TEXT_Q[83];
			link.l1 = DLG_TEXT_Q[84];
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = DLG_TEXT_Q[97];
			link.l1 = DLG_TEXT_Q[98];
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = DLG_TEXT_Q[102];
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = DLG_TEXT_Q[103];
			link.l1 = DLG_TEXT_Q[104];
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			dialog.text = DLG_TEXT_Q[107];
			link.l1 = DLG_TEXT_Q[108];
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = DLG_TEXT_Q[109];
			link.l1 = DLG_TEXT_Q[110];
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = DLG_TEXT_Q[113] + pchar.name + DLG_TEXT_Q[114];
			link.l1 = DLG_TEXT_Q[115];
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = DLG_TEXT_Q[116];
			link.l1 = DLG_TEXT_Q[117];
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "Abigile_6";
		break;
		
		case "Abigile_6":
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
		break;
		
		case "Abigile_7_1":
			dialog.text = DLG_TEXT_Q[124];
			link.l1 = DLG_TEXT_Q[125];
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = DLG_TEXT_Q[126];
			link.l1 = DLG_TEXT_Q[127];
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = "" + pchar.name + "...";
			link.l1 = DLG_TEXT_Q[132]
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = DLG_TEXT_Q[135];
			link.l1 = DLG_TEXT_Q[136];
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = DLG_TEXT_Q[137];
			link.l1 = DLG_TEXT_Q[138];
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			dialog.text = DLG_TEXT_Q[139];
			link.l1 = DLG_TEXT_Q[140];
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = DLG_TEXT_Q[141];
			link.l1 = DLG_TEXT_Q[142];
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = DLG_TEXT_Q[143] + pchar.name + DLG_TEXT_Q[144];
				link.l1 = DLG_TEXT_Q[145];
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[146] + pchar.name + " !";
				link.l1 = DLG_TEXT_Q[147];
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			dialog.text = DLG_TEXT_Q[148];
			link.l1 = DLG_TEXT_Q[149];
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = DLG_TEXT_Q[150];
			link.l1 = DLG_TEXT_Q[151];
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			dialog.text = DLG_TEXT_Q[152];
			link.l1 = DLG_TEXT_Q[153];
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = DLG_TEXT_Q[154];
			link.l1 = DLG_TEXT_Q[155];
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = DLG_TEXT_Q[156];
			link.l1 = DLG_TEXT_Q[157];
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = DLG_TEXT_Q[159];
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = DLG_TEXT_Q[160];
			link.l1 = DLG_TEXT_Q[161];
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = DLG_TEXT_Q[162];
			link.l1 = DLG_TEXT_Q[163];
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = DLG_TEXT_Q[164];
			link.l1 = DLG_TEXT_Q[165];
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = DLG_TEXT_Q[168] + pchar.name + DLG_TEXT_Q[169];
			link.l1 = DLG_TEXT_Q[170];
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = DLG_TEXT_Q[171];
			link.l1 = DLG_TEXT_Q[172];
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[173];
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = DLG_TEXT_Q[174];
			link.l1 = DLG_TEXT_Q[175];
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = DLG_TEXT_Q[176];
			link.l1 = DLG_TEXT_Q[177];
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = DLG_TEXT_Q[178] + pchar.name + DLG_TEXT_Q[179];
			link.l1 = DLG_TEXT_Q[180];
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = DLG_TEXT_Q[181];
			link.l1 = DLG_TEXT_Q[182];
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = DLG_TEXT_Q[183];
			link.l1 = DLG_TEXT_Q[184];
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = DLG_TEXT_Q[185];
			link.l1 = DLG_TEXT_Q[186];
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = DLG_TEXT_Q[187];
			link.l1 = DLG_TEXT_Q[188];
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = DLG_TEXT_Q[189];
			link.l1 = DLG_TEXT_Q[190];
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = DLG_TEXT_Q[191];
			link.l1 = DLG_TEXT_Q[192];
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = DLG_TEXT_Q[195];
			link.l1 = DLG_TEXT_Q[196];
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_SetStat(pchar, 10, 1);
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = DLG_TEXT_Q[199];
			link.l1 = DLG_TEXT_Q[200];
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = DLG_TEXT_Q[201];
			link.l1 = DLG_TEXT_Q[202];
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = DLG_TEXT_Q[203] + pchar.name + " !";
			link.l1 = DLG_TEXT_Q[204];
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hm...";
			link.l1 = DLG_TEXT_Q[207];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_Q[208];
			link.l1 = DLG_TEXT_Q[209];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_Q[210];
			link.l1 = DLG_TEXT_Q[211];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = DLG_TEXT_Q[212];
			link.l1 = DLG_TEXT_Q[213];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = DLG_TEXT_Q[214];
			link.l1 = DLG_TEXT_Q[215];
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = DLG_TEXT_Q[216];
			link.l1 = DLG_TEXT_Q[217];
			link.l1.go = "alchemy_exit";
			link.l2 = DLG_TEXT_Q[218];
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = DLG_TEXT_Q[219];
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = DLG_TEXT_Q[220];
			link.l1 = DLG_TEXT_Q[221];
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = DLG_TEXT_Q[222];
			link.l1 = DLG_TEXT_Q[223];
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = DLG_TEXT_Q[224];
			link.l1 = DLG_TEXT_Q[225];
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = DLG_TEXT_Q[226];
			link.l1 = DLG_TEXT_Q[227];
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = DLG_TEXT_Q[228];
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info(DLG_TEXT_Q[229]);
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[230];
			link.l1 = DLG_TEXT_Q[231];
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info(DLG_TEXT_Q[232]);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[233]+ GetSexPhrase(DLG_TEXT_Q[234],DLG_TEXT_Q[235]) +"!!!", DLG_TEXT_Q[236], DLG_TEXT_Q[237]);
			link.l1 = DLG_TEXT_Q[238];
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}