#include "SD\TEXT\DIALOGS\MayorQuests_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0]+ GetSexPhrase(DLG_TEXT_BASE[1],DLG_TEXT_BASE[2]) +DLG_TEXT_BASE[3] + GetFullName(npchar) + DLG_TEXT_BASE[4],
				DLG_TEXT_BASE[5]+ GetSexPhrase(DLG_TEXT_BASE[6],DLG_TEXT_BASE[7]) +DLG_TEXT_BASE[8] + GetFullName(npchar) + DLG_TEXT_BASE[9],
				DLG_TEXT_BASE[10]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[11] + GetFullName(npchar) + DLG_TEXT_BASE[12] + sTemp + DLG_TEXT_BASE[13],
				DLG_TEXT_BASE[14] + sTemp + " ?!", 
				DLG_TEXT_BASE[15]+ GetSexPhrase("","а") +DLG_TEXT_BASE[16] + GetFullName(npchar) + DLG_TEXT_BASE[17] + sTemp + DLG_TEXT_BASE[18]);
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[19]+ GetSexPhrase(DLG_TEXT_BASE[20],DLG_TEXT_BASE[21]) +DLG_TEXT_BASE[22],
				DLG_TEXT_BASE[23]+ GetSexPhrase(DLG_TEXT_BASE[24],DLG_TEXT_BASE[25]) +DLG_TEXT_BASE[26],
				DLG_TEXT_BASE[27]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29], DLG_TEXT_BASE[30]);
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[31], DLG_TEXT_BASE[32], DLG_TEXT_BASE[33]);
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[34]+ GetSexPhrase(DLG_TEXT_BASE[35],DLG_TEXT_BASE[36]) +DLG_TEXT_BASE[37],
				DLG_TEXT_BASE[38]+ GetSexPhrase(DLG_TEXT_BASE[39],DLG_TEXT_BASE[40]) +" !",
				DLG_TEXT_BASE[41]+ GetSexPhrase(DLG_TEXT_BASE[42],DLG_TEXT_BASE[43]) +".");
			Link.l1 = DLG_TEXT_BASE[44];
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашел, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = DLG_TEXT_BASE[45];
			link.l1 = DLG_TEXT_BASE[46]+pchar.GenQuest.TakePassenger.Name+DLG_TEXT_BASE[47];
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = DLG_TEXT_BASE[48];
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = DLG_TEXT_BASE[50];
			link.l1 = DLG_TEXT_BASE[51];
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = DLG_TEXT_BASE[52];
			link.l1 = DLG_TEXT_BASE[53];
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = DLG_TEXT_BASE[54];
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = DLG_TEXT_BASE[55];
			link.l1 = DLG_TEXT_BASE[56]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[57];
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = DLG_TEXT_BASE[58];
			link.l1 = DLG_TEXT_BASE[59]+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+DLG_TEXT_BASE[60];
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = DLG_TEXT_BASE[61];
			link.l1 = DLG_TEXT_BASE[62];
			link.l1.go = "Fugitive_city_fight";
			link.l2 = DLG_TEXT_BASE[63];
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+drand(25));
			TakeNItems(pchar, "jewelry7", 2+drand(5));
			PlaySound("interface\important_item.wav");
			Log_Info(DLG_TEXT_BASE[66]);
			dialog.text = DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[68];
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = DLG_TEXT_BASE[69];
			link.l1 = DLG_TEXT_BASE[70];
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = DLG_TEXT_BASE[71];
			link.l1 = DLG_TEXT_BASE[72] +pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[73];
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75]+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+DLG_TEXT_BASE[76];
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = DLG_TEXT_BASE[77];
			link.l1 = DLG_TEXT_BASE[78];
			link.l1.go = "Fugitive_city_fight";
			link.l2 = DLG_TEXT_BASE[79];
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+drand(40));
			TakeNItems(pchar, "jewelry53", 400+drand(100));
			PlaySound("interface\important_item.wav");
			Log_Info(DLG_TEXT_BASE[80]);
			dialog.text = DLG_TEXT_BASE[81];
			link.l1 = DLG_TEXT_BASE[82];
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[84]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[85]+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+DLG_TEXT_BASE[86];
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hic !"+RandSwear()+DLG_TEXT_BASE[87]+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = DLG_TEXT_BASE[88];
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = DLG_TEXT_BASE[89];
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+drand(30));
			TakeNItems(pchar, "jewelry6", 100+drand(50));
			PlaySound("interface\important_item.wav");
			Log_Info(DLG_TEXT_BASE[90]);
			dialog.text = DLG_TEXT_BASE[91];
			link.l1 = DLG_TEXT_BASE[92];
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = DLG_TEXT_BASE[93];
			link.l1 = DLG_TEXT_BASE[94];
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
