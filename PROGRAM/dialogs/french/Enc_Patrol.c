#include "SD\TEXT\DIALOGS\Enc_Patrol.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0] + XI_ConvertString("Colony" + npchar.city + "Dat") + DLG_TEXT_BASE[1], DLG_TEXT_BASE[2] + NationNamePeople(sti(pchar.nation))+ DLG_TEXT_BASE[3] + NationNameAblative(sti(npchar.nation)) + DLG_TEXT_BASE[4]);
				}
				else
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[5] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[6], DLG_TEXT_BASE[7] + NationNamePeople(sti(pchar.nation))+ DLG_TEXT_BASE[8] + XI_ConvertString("Colony" + npchar.city + "Dat") + DLG_TEXT_BASE[9]);
				}
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11]);
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[12] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[13],
					DLG_TEXT_BASE[14] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[15],
					DLG_TEXT_BASE[16] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[17] + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[18],
				DLG_TEXT_BASE[19] + GetAddress_Form(NPChar) + "?",
				DLG_TEXT_BASE[20]);
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[21],
				DLG_TEXT_BASE[22] + GetAddress_Form(NPChar) + "?");
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[23], DLG_TEXT_BASE[24]);
			Link.l1.go = "Node_3";	
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[25] + GetAddress_Form(NPChar) + ".",
				DLG_TEXT_BASE[26]);
			Link.l1 = DLG_TEXT_BASE[27];
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[28],
				DLG_TEXT_BASE[29],
				DLG_TEXT_BASE[30]);
			Link.l1 = DLG_TEXT_BASE[31];
			Link.l1.go = "Exit";		
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = DLG_TEXT_BASE[41];
					link.l1 = DLG_TEXT_BASE[42];
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = DLG_TEXT_BASE[43] + GetFullName(pchar) + DLG_TEXT_BASE[44];
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = DLG_TEXT_BASE[45] + GetFullName(pchar) + DLG_TEXT_BASE[46];
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = DLG_TEXT_BASE[47];
					link.l1 = DLG_TEXT_BASE[48];
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = DLG_TEXT_BASE[49] + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = DLG_TEXT_BASE[50];
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = DLG_TEXT_BASE[51] + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = DLG_TEXT_BASE[52];
			link.l1 = DLG_TEXT_BASE[53];
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = DLG_TEXT_BASE[54];
			link.l1 = DLG_TEXT_BASE[55];
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = DLG_TEXT_BASE[56];
				break;
				case 2:
					sItemName = DLG_TEXT_BASE[57];
				break;
				case 3:
					sItemName = DLG_TEXT_BASE[58];
				break;
				case 4:
					sItemName = DLG_TEXT_BASE[59];
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = DLG_TEXT_BASE[60] + sItemName + DLG_TEXT_BASE[61];
			link.l1 = GetName(NAMETYPE_MAIN , pchar.questTemp.ReasonToFast.p3, NAME_NOM) + DLG_TEXT_BASE[62];
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = DLG_TEXT_BASE[63];
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = DLG_TEXT_BASE[66] + sti(pchar.questTemp.ReasonToFast.p5) + DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[68];
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = DLG_TEXT_BASE[69];
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = DLG_TEXT_BASE[70];
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = DLG_TEXT_BASE[71]  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером 
			AddDialogExitQuest("pchar_back_to_player");	
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = DLG_TEXT_BASE[74] + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + DLG_TEXT_BASE[75]+ GetSexPhrase(DLG_TEXT_BASE[76],DLG_TEXT_BASE[77]) +DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = DLG_TEXT_BASE[80] + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) +" '" + sTemp1 + DLG_TEXT_BASE[81] + GetGoodsNameAlt(iShipGoods) + DLG_TEXT_BASE[82];
					link.l1 = DLG_TEXT_BASE[83] + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // сокровища губернатора
					switch(rand(3))
					{
						case 0:
							sTemp1 = DLG_TEXT_BASE[84];
						break;
						case 1:
							sTemp1 = DLG_TEXT_BASE[85];
						break;
						case 2:
							sTemp1 = DLG_TEXT_BASE[86];
						break;
						case 3:
							sTemp1 = DLG_TEXT_BASE[87];
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = DLG_TEXT_BASE[88];
						break;
						case 1:
							sTemp2 = DLG_TEXT_BASE[89];
						break;
						case 2:
							sTemp2 = DLG_TEXT_BASE[90];
						break;
						case 3:
							sTemp2 = DLG_TEXT_BASE[91];
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = DLG_TEXT_BASE[92] + sTemp1 + DLG_TEXT_BASE[93]+ pchar.questTemp.ReasonToFast.password +DLG_TEXT_BASE[94]+ sTemp2 +"'.";
					link.l1 = DLG_TEXT_BASE[95] + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = DLG_TEXT_BASE[96];
				link.l1 = DLG_TEXT_BASE[97];
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[98];
				link.l1 = DLG_TEXT_BASE[99];
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; //Ќ«√ не начисл€ютс€
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не мен€ть
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = DLG_TEXT_BASE[102];
			link.l1 = DLG_TEXT_BASE[103];
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = DLG_TEXT_BASE[104];
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = "Arrgh !";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = DLG_TEXT_BASE[106]+ GetSexPhrase(DLG_TEXT_BASE[107],DLG_TEXT_BASE[108]) +"...";
			link.l1 = "Arrgh !";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}