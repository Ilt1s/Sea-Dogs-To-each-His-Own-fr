#include "SD\TEXT\DIALOGS\Common_population.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[190];
			link.l1 = DLG_TEXT_BASE[191];
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[192],DLG_TEXT_BASE[193]);
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = DLG_TEXT_BASE[194];
					link.l1 = DLG_TEXT_BASE[195];
					link.l1.go = "passenger";
					link.l2 = DLG_TEXT_BASE[196];
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[197],DLG_TEXT_BASE[198],DLG_TEXT_BASE[199]);
				link.l1 = DLG_TEXT_BASE[200]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[201];
				link.l1.go = "question";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[202],DLG_TEXT_BASE[203]);
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = DLG_TEXT_BASE[204];
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = DLG_TEXT_BASE[205];
				link.l1 = DLG_TEXT_BASE[206];
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = DLG_TEXT_BASE[207];
				link.l1 = DLG_TEXT_BASE[208];
				link.l1.go = "exit_quest";
				link.l2 = DLG_TEXT_BASE[209];
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+drand(5)*10;
				dialog.text = DLG_TEXT_BASE[210]+sti(pchar.GenQuest.Marginpassenger.Dublon)+DLG_TEXT_BASE[211];
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = DLG_TEXT_BASE[212];
					link.l1.go = "passenger_4";
				}
				link.l2 = DLG_TEXT_BASE[213];
				link.l2.go = "passenger_3";
				link.l3 = DLG_TEXT_BASE[214];
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = DLG_TEXT_BASE[215];
				link.l1 = DLG_TEXT_BASE[216];
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = DLG_TEXT_BASE[217];
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = DLG_TEXT_BASE[218];
					link.l1.go = "passenger_4";
				}
				link.l2 = DLG_TEXT_BASE[219];
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+drand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = DLG_TEXT_BASE[220]+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+DLG_TEXT_BASE[221]+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+DLG_TEXT_BASE[222]+pchar.GenQuest.Marginpassenger.ShipName+DLG_TEXT_BASE[223]+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+DLG_TEXT_BASE[224]+pchar.GenQuest.Marginpassenger.Text+DLG_TEXT_BASE[225]+pchar.GenQuest.Marginpassenger.q1Name+DLG_TEXT_BASE[226]+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Gen"))+DLG_TEXT_BASE[227]+DLG_TEXT_BASE[232]+pchar.GenQuest.Marginpassenger.Text1+DLG_TEXT_BASE[228]+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+DLG_TEXT_BASE[229]+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+DLG_TEXT_BASE[230]+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+DLG_TEXT_BASE[231];
				link.l1 = DLG_TEXT_BASE[233];
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = DLG_TEXT_BASE[234]+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+DLG_TEXT_BASE[235];
				link.l1 = DLG_TEXT_BASE[236];
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[237],DLG_TEXT_BASE[238]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[239],DLG_TEXT_BASE[240],DLG_TEXT_BASE[241]);
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[242],DLG_TEXT_BASE[243],DLG_TEXT_BASE[244]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[245],DLG_TEXT_BASE[246],DLG_TEXT_BASE[247]);
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (drand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = DLG_TEXT_BASE[248];
		switch (drand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[249];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[250];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[251];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[252];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[253];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[254];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[255];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[256];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[257];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[258];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = DLG_TEXT_BASE[259];
		switch (drand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[260];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[261];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[262];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[263];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[264];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[265];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[266];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[267];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = DLG_TEXT_BASE[268];
				pchar.GenQuest.Marginpassenger.Text1 = DLG_TEXT_BASE[269];
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 4) pchar.GenQuest.Marginpassenger.ShipType = SHIP_BARQUE;
	if (sti(pchar.rank) >= 4 && sti(pchar.rank) < 7) pchar.GenQuest.Marginpassenger.ShipType = SHIP_BARKENTINE + rand(makeint(SHIP_FLEUT - SHIP_BARKENTINE));
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 16) pchar.GenQuest.Marginpassenger.ShipType = SHIP_GALEON_L;
	if (sti(pchar.rank) >= 16) pchar.GenQuest.Marginpassenger.ShipType = SHIP_NAVIO + rand(makeint(SHIP_GALEON_H - SHIP_NAVIO));
}
