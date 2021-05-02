#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(DLG_TEXT_STR[0], DLG_TEXT_STR[1], DLG_TEXT_STR[2]),
					LinkRandPhrase(DLG_TEXT_STR[3], DLG_TEXT_STR[4], DLG_TEXT_STR[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_STR[6], DLG_TEXT_STR[7]),
					RandPhraseSimple(DLG_TEXT_STR[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_STR[9], "Heh, " + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_STR[10]));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + DLG_TEXT_STR[11] + GetAddress_Form(NPChar) + DLG_TEXT_STR[12]+GetFullName(npchar)+DLG_TEXT_STR[13];
				Link.l1 = DLG_TEXT_STR[14] + GetFullName(pchar) + DLG_TEXT_STR[15]+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_STR[16]+GetFullName(pchar)+DLG_TEXT_STR[17];
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = DLG_TEXT_STR[18]+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = DLG_TEXT_STR[19];
				link.l2.go = "room";
				link.l3 = LinkRandPhrase(DLG_TEXT_STR[20],DLG_TEXT_STR[21],DLG_TEXT_STR[22]);
				link.l3.go = "rumours_tavern";
				link.l4 = DLG_TEXT_STR[23]+npchar.name+DLG_TEXT_STR[24];
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = DLG_TEXT_STR[25];
			link.l1 = DLG_TEXT_STR[26];
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = DLG_TEXT_STR[27]+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = DLG_TEXT_STR[28];
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = DLG_TEXT_STR[29]+DLG_TEXT_STR[30]+DLG_TEXT_STR[31]+DLG_TEXT_STR[32];
			link.l1 = DLG_TEXT_STR[33];			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = DLG_TEXT_STR[34];
				link.l1 = DLG_TEXT_STR[35];			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = DLG_TEXT_STR[36];
				link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_STR[37],DLG_TEXT_STR[38],DLG_TEXT_STR[39]), LinkRandPhrase(DLG_TEXT_STR[40],DLG_TEXT_STR[41],DLG_TEXT_STR[42]));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.MinentownSex"))
			{
				dialog.text = DLG_TEXT_STR[43];
				link.l1 = DLG_TEXT_STR[44];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_STR[45];
			if(!isDay())
			{
				link.l1 = DLG_TEXT_STR[46];
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = DLG_TEXT_STR[47];
				link.l1.go = "room_night";
				link.l2 = DLG_TEXT_STR[48];
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = DLG_TEXT_STR[49];
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = DLG_TEXT_STR[50];
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = DLG_TEXT_STR[51];
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = DLG_TEXT_STR[52];
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = DLG_TEXT_STR[53];
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = DLG_TEXT_STR[54];
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = DLG_TEXT_STR[55];
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = DLG_TEXT_STR[56];
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = DLG_TEXT_STR[57];
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = DLG_TEXT_STR[58];
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = DLG_TEXT_STR[59];
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = DLG_TEXT_STR[60];
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = DLG_TEXT_STR[61];
			link.l1 = DLG_TEXT_STR[62];
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.MinentownSex = "true";
			LocatorReloadEnterDisable("Minentown_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("Minentown_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\Minentown_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Minentown_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = DLG_TEXT_STR[63]+npchar.name+DLG_TEXT_STR[64]+npchar.name+DLG_TEXT_STR[65];
			link.l1 = DLG_TEXT_STR[66];
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_STR[67], DLG_TEXT_STR[68], DLG_TEXT_STR[69]);
			link.l1 = LinkRandPhrase(DLG_TEXT_STR[70], DLG_TEXT_STR[71], DLG_TEXT_STR[72]);
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
