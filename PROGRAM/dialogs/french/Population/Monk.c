#include "SD\TEXT\DIALOGS\Common_population.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = DLG_TEXT_BASE[270];
					link.l1 = DLG_TEXT_BASE[271];
					link.l1.go = "donation";
					link.l2 = DLG_TEXT_BASE[272];
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = DLG_TEXT_BASE[273];
					link.l1 = DLG_TEXT_BASE[274];
					link.l1.go = "passenger";
					link.l2 = DLG_TEXT_BASE[275];
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = DLG_TEXT_BASE[276];
					link.l1 = DLG_TEXT_BASE[277];
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[278],DLG_TEXT_BASE[279],DLG_TEXT_BASE[280]),LinkRandPhrase(DLG_TEXT_BASE[281],DLG_TEXT_BASE[282],DLG_TEXT_BASE[283]));
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[284],DLG_TEXT_BASE[285],DLG_TEXT_BASE[286]);
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[287],DLG_TEXT_BASE[288]);
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = DLG_TEXT_BASE[289];
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = DLG_TEXT_BASE[290];
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase(DLG_TEXT_BASE[291],DLG_TEXT_BASE[292],DLG_TEXT_BASE[293]);
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[294],DLG_TEXT_BASE[295],DLG_TEXT_BASE[296]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[297],DLG_TEXT_BASE[298],DLG_TEXT_BASE[299]);
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[300],DLG_TEXT_BASE[301]);
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = DLG_TEXT_BASE[302];
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = DLG_TEXT_BASE[303];
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase(DLG_TEXT_BASE[304],DLG_TEXT_BASE[305],DLG_TEXT_BASE[306]);
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = DLG_TEXT_BASE[307]+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+DLG_TEXT_BASE[308];
				link.l1 = DLG_TEXT_BASE[309]+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = DLG_TEXT_BASE[310];
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = DLG_TEXT_BASE[311]+DLG_TEXT_BASE[312]+NationNameGenitive(sti(npchar.nation))+DLG_TEXT_BASE[313];
				link.l1 = DLG_TEXT_BASE[314];
				link.l1.go = "Churchbooks";
				link.l2 = DLG_TEXT_BASE[315];
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[316],DLG_TEXT_BASE[317]);
			link.l1 = DLG_TEXT_BASE[318];
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = DLG_TEXT_BASE[319]+sTemp+"";
			link.l1 = DLG_TEXT_BASE[320];
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = DLG_TEXT_BASE[321];
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = DLG_TEXT_BASE[322];
				link.l1 = DLG_TEXT_BASE[323];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[324];
				link.l1 = DLG_TEXT_BASE[325];
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = DLG_TEXT_BASE[326];
				link.l1 = DLG_TEXT_BASE[327];
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[328];
				link.l1 = DLG_TEXT_BASE[329];
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = DLG_TEXT_BASE[330];
				link.l1 = DLG_TEXT_BASE[331];
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[332];
				link.l1 = DLG_TEXT_BASE[333];
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = DLG_TEXT_BASE[334];
				link.l1 = DLG_TEXT_BASE[335];
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[336];
				link.l1 = DLG_TEXT_BASE[337];
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = DLG_TEXT_BASE[338];
			link.l1 = DLG_TEXT_BASE[339];
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = DLG_TEXT_BASE[340];
			link.l1 = DLG_TEXT_BASE[341];
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam(GetConvertStr("Monk_1", "SetLaunchFrameFormParam.txt")+ NewStr() +GetConvertStr("Monk_2", "SetLaunchFrameFormParam.txt"), "Monk_RemoveSlaves", 0, 4);//GetConvertStr("Monk_1", "SetLaunchFrameFormParam.txt")
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 6;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = DLG_TEXT_BASE[344]+iTemp+DLG_TEXT_BASE[349];
					pchar.GenQuest.Shipshine.Money = 5000*(6-iTemp);
				break;
				case 2:
					sTemp = DLG_TEXT_BASE[345]+iTemp+DLG_TEXT_BASE[349];
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(6-iTemp)));
				break;
				case 3:
					sTemp = DLG_TEXT_BASE[346]+iTemp+DLG_TEXT_BASE[349];
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(6-iTemp)));
				break;
				case 4:
					sTemp = DLG_TEXT_BASE[347]+iTemp+DLG_TEXT_BASE[349];
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(6-iTemp)));
				break;
				case 5:
					sTemp = DLG_TEXT_BASE[348]+iTemp+DLG_TEXT_BASE[349];
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(6-iTemp)));
				break;
			}
			dialog.text = DLG_TEXT_BASE[350];
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = DLG_TEXT_BASE[351]+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+DLG_TEXT_BASE[352];
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = DLG_TEXT_BASE[353];
				link.l1.go = "shipshine_2";
			}
			link.l2 = DLG_TEXT_BASE[354];
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = DLG_TEXT_BASE[355];
			link.l1 = DLG_TEXT_BASE[356];
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam(GetConvertStr("Monk_3", "SetLaunchFrameFormParam.txt")+ NewStr() +GetConvertStr("Monk_4", "SetLaunchFrameFormParam.txt"), "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = DLG_TEXT_BASE[359];
			link.l1 = DLG_TEXT_BASE[360];
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = DLG_TEXT_BASE[361]+DLG_TEXT_BASE[645];
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = DLG_TEXT_BASE[362];
				link.l1.go = "capellan_2";
			}
			link.l2 = DLG_TEXT_BASE[363];
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = DLG_TEXT_BASE[364]+DLG_TEXT_BASE[644];
			link.l1 = DLG_TEXT_BASE[365];
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = DLG_TEXT_BASE[366];
			link.l1 = DLG_TEXT_BASE[367];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[368];
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = DLG_TEXT_BASE[369];
			link.l1 = DLG_TEXT_BASE[370];
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = DLG_TEXT_BASE[371];
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			dialog.text = DLG_TEXT_BASE[372] + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+DLG_TEXT_BASE[373]+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+DLG_TEXT_BASE[374]+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+DLG_TEXT_BASE[375]+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+DLG_TEXT_BASE[376];
			link.l1 = DLG_TEXT_BASE[377];
			link.l1.go = "passenger_1";
			link.l2 = DLG_TEXT_BASE[378];
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = DLG_TEXT_BASE[379];
			link.l1 = DLG_TEXT_BASE[380];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = DLG_TEXT_BASE[381];
			link.l1 = DLG_TEXT_BASE[382];
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + DLG_TEXT_BASE[404] + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = DLG_TEXT_BASE[383];
			link.l1 = DLG_TEXT_BASE[384];
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = DLG_TEXT_BASE[385];
			link.l1 = DLG_TEXT_BASE[386];
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = DLG_TEXT_BASE[387]+NationNameGenitive(sti(npchar.nation))+DLG_TEXT_BASE[388];
			link.l1 = DLG_TEXT_BASE[389];
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (drand(9))
	{
		case 0: sText = DLG_TEXT_BASE[390]+LinkRandPhrase(DLG_TEXT_BASE[391],DLG_TEXT_BASE[392],DLG_TEXT_BASE[393])+DLG_TEXT_BASE[394] break;
		case 1: sText = DLG_TEXT_BASE[395] break;
		case 2: sText = DLG_TEXT_BASE[396] break;
		case 3: sText = DLG_TEXT_BASE[397] break;
		case 4: sText = DLG_TEXT_BASE[398] break;
		case 5: sText = DLG_TEXT_BASE[399] break;
		case 6: sText = DLG_TEXT_BASE[400] break;
		case 7: sText = DLG_TEXT_BASE[401] break;
		case 8: sText = DLG_TEXT_BASE[402] break;
		case 9: sText = DLG_TEXT_BASE[403] break;
	}
	return sText;
}