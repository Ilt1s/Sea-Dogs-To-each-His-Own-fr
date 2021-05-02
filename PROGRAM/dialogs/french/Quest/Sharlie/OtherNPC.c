#include "SD\TEXT\DIALOGS\OtherNPC.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = DLG_TEXT_BASE[2];
			link.l1 = DLG_TEXT_BASE[3];
			link.l1.go = "Startsailor_1";			
		break;
		
		case "Startsailor_1":
			dialog.text = DLG_TEXT_BASE[4];
			link.l1 = DLG_TEXT_BASE[5];
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = DLG_TEXT_BASE[6];
			link.l1 = DLG_TEXT_BASE[7];
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = DLG_TEXT_BASE[8];
			link.l1 = DLG_TEXT_BASE[9];
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = DLG_TEXT_BASE[10];
			link.l1 = DLG_TEXT_BASE[11];
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = DLG_TEXT_BASE[12];
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			DoQuestReloadToLocation("Fortfrance_town", "reload", "reload1", "Sharlie_onLand");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = DLG_TEXT_BASE[13];
			link.l1 = DLG_TEXT_BASE[14];
			link.l1.go = "Sharlie_arest_1";			
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
			DoQuestFunctionDelay("Puancie_InJail", 10.0);
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = DLG_TEXT_BASE[15];
				link.l1 = TimeGreeting()+DLG_TEXT_BASE[16];
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = DLG_TEXT_BASE[17];
				link.l1 = DLG_TEXT_BASE[18];
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = DLG_TEXT_BASE[19];
				link.l1 = DLG_TEXT_BASE[20];
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[21];
				link.l1 = DLG_TEXT_BASE[22];
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			dialog.text = DLG_TEXT_BASE[23];
			link.l1 = DLG_TEXT_BASE[24];
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = DLG_TEXT_BASE[25];
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = DLG_TEXT_BASE[27];
			link.l1 = DLG_TEXT_BASE[28];
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = DLG_TEXT_BASE[29];
			link.l1 = DLG_TEXT_BASE[30];
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = DLG_TEXT_BASE[33];
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "reload", "reload7_back", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			dialog.text = DLG_TEXT_BASE[34];
			link.l1 = DLG_TEXT_BASE[35];
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			dialog.text = DLG_TEXT_BASE[36];
			link.l1 = DLG_TEXT_BASE[37];
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = DLG_TEXT_BASE[38];
			link.l1 = DLG_TEXT_BASE[39]+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+DLG_TEXT_BASE[40];
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = DLG_TEXT_BASE[41]+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = DLG_TEXT_BASE[44];
			link.l1 = DLG_TEXT_BASE[45];
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = DLG_TEXT_BASE[46];
			if (sti(Pchar.money) >= 8000)
			{
				link.l1 = DLG_TEXT_BASE[47];
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = DLG_TEXT_BASE[48];
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = DLG_TEXT_BASE[49];
				link.l1 = DLG_TEXT_BASE[50];
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -8000);
				dialog.text = DLG_TEXT_BASE[51];
				link.l1 = DLG_TEXT_BASE[52];
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = DLG_TEXT_BASE[53];
			link.l1 = DLG_TEXT_BASE[54];
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = DLG_TEXT_BASE[55];
			if (sti(Pchar.money) < 8000)
			{
				link.l1 = DLG_TEXT_BASE[56];
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[57];
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[58],DLG_TEXT_BASE[59],DLG_TEXT_BASE[60]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[61], DLG_TEXT_BASE[62]);
			link.l1.go = "skipertalker_1";
			link.l2 = DLG_TEXT_BASE[63];
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[64], DLG_TEXT_BASE[65]);
			link.l1 = DLG_TEXT_BASE[66]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[67];
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[77];
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = DLG_TEXT_BASE[80];
			link.l1 = "...";
			link.l1.go = "Folke_5";
		break;
		
		case "Folke_5":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = DLG_TEXT_BASE[81];
			link.l1 = DLG_TEXT_BASE[82];
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[84];
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = DLG_TEXT_BASE[85];
				link.l1 = DLG_TEXT_BASE[86];
				link.l1.go = "Folke_10";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[87];
				link.l1 = DLG_TEXT_BASE[88];
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = DLG_TEXT_BASE[89];
			if (bOk)
			{
				link.l1 = DLG_TEXT_BASE[90];
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[91];
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = DLG_TEXT_BASE[92];
				link.l1 = DLG_TEXT_BASE[93];
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[94];
				link.l1 = DLG_TEXT_BASE[95];
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = DLG_TEXT_BASE[96];
			if (bOk)
			{
				link.l1 = DLG_TEXT_BASE[97];
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[98];
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = DLG_TEXT_BASE[99];
				link.l1 = DLG_TEXT_BASE[100];
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[101];
				link.l1 = DLG_TEXT_BASE[102];
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = DLG_TEXT_BASE[103];
			if (bOk)
			{
				link.l1 = DLG_TEXT_BASE[104];
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[105];
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = DLG_TEXT_BASE[106];
			link.l1 = DLG_TEXT_BASE[107];
			link.l1.go = "Folke_13";
		break;
		
		case "Folke_13":
			dialog.text = DLG_TEXT_BASE[108];
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			AddQuestRecord("Sharlie", "15");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			npchar.quest.OfficerPrice = 20;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 30;
			npchar.greeting = "Gr_Officer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
		break;
		// штурман
		
		// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = DLG_TEXT_BASE[109]+GetFullName(pchar)+" ?";
			link.l1 = DLG_TEXT_BASE[110];
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = DLG_TEXT_BASE[111]+GetFullName(npchar)+DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = DLG_TEXT_BASE[114];
			link.l1 = DLG_TEXT_BASE[115];
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = DLG_TEXT_BASE[116];
			link.l1 = DLG_TEXT_BASE[117];
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = DLG_TEXT_BASE[118];
			link.l1 = DLG_TEXT_BASE[119];
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = DLG_TEXT_BASE[120];
			link.l1 = DLG_TEXT_BASE[121];
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "Seabattle_pirate_open", -1);
			AddQuestRecord("Sharlie", "11");
		break;
		// пират-обманщик
		
		// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = DLG_TEXT_BASE[122];
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = DLG_TEXT_BASE[124];
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;
		
		// страж истины
		case "spanish":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = DLG_TEXT_BASE[127];
			link.l1 = DLG_TEXT_BASE[128];
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = DLG_TEXT_BASE[129];
			link.l1 = DLG_TEXT_BASE[130];
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = DLG_TEXT_BASE[131];
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = DLG_TEXT_BASE[133];
			link.l1 = DLG_TEXT_BASE[134];
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = DLG_TEXT_BASE[135];
			link.l1 = DLG_TEXT_BASE[136];
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = DLG_TEXT_BASE[137];
			link.l1 = DLG_TEXT_BASE[138];
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = DLG_TEXT_BASE[139];
			link.l1 = DLG_TEXT_BASE[140];
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = DLG_TEXT_BASE[141];
			link.l1 = DLG_TEXT_BASE[142];
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = DLG_TEXT_BASE[143];
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = DLG_TEXT_BASE[145];
			link.l1 = DLG_TEXT_BASE[146];
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = DLG_TEXT_BASE[147];
			link.l1 = DLG_TEXT_BASE[148];
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = DLG_TEXT_BASE[149];
			link.l1 = DLG_TEXT_BASE[150];
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = DLG_TEXT_BASE[151];
			link.l1 = DLG_TEXT_BASE[152];
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = DLG_TEXT_BASE[153];
			link.l1 = DLG_TEXT_BASE[154];
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
		// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+DLG_TEXT_BASE[155]+GetFullName(pchar)+" ?";
			link.l1 = DLG_TEXT_BASE[156];
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = DLG_TEXT_BASE[157];
			link.l1 = DLG_TEXT_BASE[158];
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = DLG_TEXT_BASE[159];
			link.l1 = DLG_TEXT_BASE[160];
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = DLG_TEXT_BASE[161];
			link.l1 = DLG_TEXT_BASE[162];
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = DLG_TEXT_BASE[163];
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
		// падре Адриан
		case "adrian":
			dialog.text = DLG_TEXT_BASE[164];
			link.l1 = DLG_TEXT_BASE[165];
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = DLG_TEXT_BASE[166];
			link.l1 = DLG_TEXT_BASE[167];
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = DLG_TEXT_BASE[168];
			link.l1 = DLG_TEXT_BASE[169];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[170];
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = DLG_TEXT_BASE[171];
			link.l1 = DLG_TEXT_BASE[172];
			link.l1.go = "potion";
			link.l2 = DLG_TEXT_BASE[173];
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = DLG_TEXT_BASE[174];
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = DLG_TEXT_BASE[175];
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = DLG_TEXT_BASE[176];
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = DLG_TEXT_BASE[177];
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = DLG_TEXT_BASE[178];
				link.l4.go = "potion4";
			}
			link.l5 = DLG_TEXT_BASE[179];
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = DLG_TEXT_BASE[180];
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = DLG_TEXT_BASE[181];
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[182];
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = DLG_TEXT_BASE[183];
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = DLG_TEXT_BASE[184];
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[185];
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = DLG_TEXT_BASE[186];
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = DLG_TEXT_BASE[187];
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[188];
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = DLG_TEXT_BASE[189];
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = DLG_TEXT_BASE[190];
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[191];
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[192];
			link.l1 = DLG_TEXT_BASE[193];
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
		// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = DLG_TEXT_BASE[194]+GetFullName(pchar)+" ?";
			link.l1 = DLG_TEXT_BASE[195];
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = DLG_TEXT_BASE[196];
			link.l1 = DLG_TEXT_BASE[197];
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = DLG_TEXT_BASE[198];
			link.l1 = DLG_TEXT_BASE[199];
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = DLG_TEXT_BASE[200];
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = DLG_TEXT_BASE[201];
			link.l1 = DLG_TEXT_BASE[202];
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = DLG_TEXT_BASE[203];
			link.l1 = DLG_TEXT_BASE[204];
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
		// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = DLG_TEXT_BASE[205]+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = DLG_TEXT_BASE[206];
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[207];
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = DLG_TEXT_BASE[208];
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = DLG_TEXT_BASE[209];
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[210];
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = DLG_TEXT_BASE[211];
			link.l1 = DLG_TEXT_BASE[212];
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = DLG_TEXT_BASE[213];
			link.l1 = DLG_TEXT_BASE[214];
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = DLG_TEXT_BASE[215];
			link.l1 = DLG_TEXT_BASE[216];
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = DLG_TEXT_BASE[217];
			link.l1 = DLG_TEXT_BASE[218];
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = DLG_TEXT_BASE[219];
			link.l1 = DLG_TEXT_BASE[220];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = DLG_TEXT_BASE[221];
			link.l1 = DLG_TEXT_BASE[222];
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = DLG_TEXT_BASE[223];
			link.l1 = DLG_TEXT_BASE[224];
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		// командир абордажников
		case "newcastle_officer":
			dialog.text = DLG_TEXT_BASE[225];
			link.l1 = DLG_TEXT_BASE[226];
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = DLG_TEXT_BASE[227];
			link.l1 = DLG_TEXT_BASE[228];
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = DLG_TEXT_BASE[229];
			link.l1 = DLG_TEXT_BASE[230];
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;
		
		case "Europe":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = DLG_TEXT_BASE[231];
			link.l1 = DLG_TEXT_BASE[232];
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[233], DLG_TEXT_BASE[234]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[235], DLG_TEXT_BASE[236], DLG_TEXT_BASE[237]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}