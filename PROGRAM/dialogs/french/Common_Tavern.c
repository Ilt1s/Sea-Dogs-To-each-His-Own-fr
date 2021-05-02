#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "SD\interface\ship.c"
#include "SD\TEXT\DIALOGS\Common_Tavern.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], "Courez, "+ GetSexPhrase("mon gars","petite") +DLG_TEXT_BASE[2]),
					LinkRandPhrase("Que voulez-vous, "+ GetSexPhrase("canaille", "peau de vache") +DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]),
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[272], DLG_TEXT_BASE[273]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[274], DLG_TEXT_BASE[275]);
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				dialog.text = DLG_TEXT_BASE[276];
				Link.l1 = DLG_TEXT_BASE[277];
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				dialog.text = DLG_TEXT_BASE[278];
				Link.l1 = ""+npchar.name + DLG_TEXT_BASE[279];
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = DLG_TEXT_BASE[280];
				Link.l1 = DLG_TEXT_BASE[281];
				Link.l1.go = "quests";
				link.l2 = DLG_TEXT_BASE[282];
                link.l2.go = "room";
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = DLG_TEXT_BASE[508];
				Link.l1 = DLG_TEXT_BASE[509];
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = DLG_TEXT_BASE[510];
				Link.l1 = "...";
				Link.l1.go = "exit";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[283] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[284],DLG_TEXT_BASE[285] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[286],DLG_TEXT_BASE[287] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[288]), LinkRandPhrase(DLG_TEXT_BASE[289] + XI_ConvertString(NPChar.City + "TavernName") + "' ?",DLG_TEXT_BASE[290]+GetFullName(npchar)+DLG_TEXT_BASE[291] + XI_ConvertString(NPChar.City + "TavernName") + "'.",DLG_TEXT_BASE[292] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[293]+GetFullName(npchar)+DLG_TEXT_BASE[294]), LinkRandPhrase(DLG_TEXT_BASE[295] + XI_ConvertString(NPChar.City + "TavernName") + "' !",DLG_TEXT_BASE[296] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[297],DLG_TEXT_BASE[298]+GetFullName(npchar)+DLG_TEXT_BASE[299] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[300]),LinkRandPhrase(DLG_TEXT_BASE[301] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[302],DLG_TEXT_BASE[303] + XI_ConvertString(NPChar.City + "TavernName") + "'.",DLG_TEXT_BASE[304] + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[305]));
				Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[306]+GetFullName(pchar)+DLG_TEXT_BASE[307],""+GetFullName(pchar)+DLG_TEXT_BASE[308],DLG_TEXT_BASE[32]+GetFullName(pchar)+DLG_TEXT_BASE[309]);
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = DLG_TEXT_BASE[312] + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = DLG_TEXT_BASE[313];
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = DLG_TEXT_BASE[314];
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = DLG_TEXT_BASE[310] + GetSexPhrase("sir","demoiselle") +"?";
						link.l1 = DLG_TEXT_BASE[311];
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[315],"Oh ! Mais si ce n'est pas "+GetFullName(pchar)+DLG_TEXT_BASE[316],"Oh, "+GetAddress_Form(NPChar)+DLG_TEXT_BASE[317]),LinkRandPhrase("Oh, c'est le capitaine "+GetFullName(pchar)+DLG_TEXT_BASE[318],"Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[319],DLG_TEXT_BASE[320]+GetFullName(pchar)+DLG_TEXT_BASE[321]),LinkRandPhrase(DLG_TEXT_BASE[322],DLG_TEXT_BASE[323]+GetFullName(pchar)+DLG_TEXT_BASE[324],"O-ho-ho ! C'est "+GetFullName(pchar)+DLG_TEXT_BASE[325])),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+DLG_TEXT_BASE[326],DLG_TEXT_BASE[327],DLG_TEXT_BASE[328]+GetFullName(pchar)+DLG_TEXT_BASE[329]),LinkRandPhrase(DLG_TEXT_BASE[330],"Salutation, capitaine "+GetFullName(pchar)+DLG_TEXT_BASE[331],DLG_TEXT_BASE[332]+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[333]),LinkRandPhrase(DLG_TEXT_BASE[334],""+GetFullName(pchar)+DLG_TEXT_BASE[335],DLG_TEXT_BASE[336]+GetFullName(pchar)+DLG_TEXT_BASE[337])));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[338],DLG_TEXT_BASE[339]),RandPhraseSimple(DLG_TEXT_BASE[340],DLG_TEXT_BASE[341])),RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[342],DLG_TEXT_BASE[343]),RandPhraseSimple(DLG_TEXT_BASE[344],DLG_TEXT_BASE[345])));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[35]+pchar.name+".","Taverne '" + XI_ConvertString(NPChar.City + "TavernName") + DLG_TEXT_BASE[31],DLG_TEXT_BASE[34]+pchar.name+DLG_TEXT_BASE[36]);
				Link.l1 = DLG_TEXT_BASE[37];
				Link.l1.go = "crew hire";
				Link.l2 = DLG_TEXT_BASE[38];
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = DLG_TEXT_BASE[39];
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase(DLG_TEXT_BASE[346], DLG_TEXT_BASE[347], DLG_TEXT_BASE[348]);
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = DLG_TEXT_BASE[349]+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[350];
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = DLG_TEXT_BASE[351]+pchar.GenQuest.Sunplace.Trader.Enemyname+DLG_TEXT_BASE[352];
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = npchar.name + DLG_TEXT_BASE[353];
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = npchar.name + DLG_TEXT_BASE[354];
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = DLG_TEXT_BASE[355] + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = DLG_TEXT_BASE[356]+pchar.GenQuest.Marginpassenger.q2Name+DLG_TEXT_BASE[357];
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			
				link.l3 = pcharrepphrase(DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]);
				link.l3.go = "room";
				Link.l4 = DLG_TEXT_BASE[42] + NPChar.name + DLG_TEXT_BASE[43];
				Link.l4.go = "exit";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = DLG_TEXT_BASE[310] + GetSexPhrase("sir","demoiselle") +"?";
				link.l1 = DLG_TEXT_BASE[311];
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = DLG_TEXT_BASE[44]+GetFullName(pchar)+DLG_TEXT_BASE[45]+GetFullName(npchar)+DLG_TEXT_BASE[46] 
			Link.l1 = DLG_TEXT_BASE[47] + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + DLG_TEXT_BASE[48];
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = DLG_TEXT_BASE[49];
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase(DLG_TEXT_BASE[346], DLG_TEXT_BASE[347], DLG_TEXT_BASE[348]);
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
				link.l16 = DLG_TEXT_BASE[349]+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[350];
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
				link.l17 = DLG_TEXT_BASE[351]+pchar.GenQuest.Sunplace.Trader.Enemyname+DLG_TEXT_BASE[352];
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = npchar.name + DLG_TEXT_BASE[353];
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = npchar.name + DLG_TEXT_BASE[354];
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = DLG_TEXT_BASE[355] + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = DLG_TEXT_BASE[356]+pchar.GenQuest.Marginpassenger.q2Name+DLG_TEXT_BASE[357];
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				
			link.l3 = pcharrepphrase(DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]);
			link.l3.go = "room";
			Link.l4 = DLG_TEXT_BASE[52];
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = DLG_TEXT_BASE[53];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[54], DLG_TEXT_BASE[55]);
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = DLG_TEXT_BASE[56];
				link.l1 = DLG_TEXT_BASE[57];
				link.l1.go = "room";
				link.l2 = DLG_TEXT_BASE[58];
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = DLG_TEXT_BASE[59];
					link.l1 = DLG_TEXT_BASE[60];
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = DLG_TEXT_BASE[61] + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = DLG_TEXT_BASE[62];
						link.l1.go = "exit";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = DLG_TEXT_BASE[33];
									link.l1 = "Je vois...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = DLG_TEXT_BASE[63];
			//link.l1 = DLG_TEXT_BASE[64];
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[65],DLG_TEXT_BASE[66],
                                    DLG_TEXT_BASE[67]);
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = DLG_TEXT_BASE[68];
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = DLG_TEXT_BASE[358] + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = DLG_TEXT_BASE[359] + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = DLG_TEXT_BASE[360]; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = DLG_TEXT_BASE[361] + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = DLG_TEXT_BASE[362] + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = DLG_TEXT_BASE[363] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = DLG_TEXT_BASE[361] + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = DLG_TEXT_BASE[362] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = DLG_TEXT_BASE[364] + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = DLG_TEXT_BASE[365];
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = DLG_TEXT_BASE[366]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[367];
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l99 = DLG_TEXT_BASE[70];
			link.l99.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[368] + pchar.GenQuest.Hold_GenQuest.Name + DLG_TEXT_BASE[369],
						DLG_TEXT_BASE[370],
						DLG_TEXT_BASE[371]);
					link.l1 = DLG_TEXT_BASE[372];
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (drand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Visitez " + pchar.GenQuest.Hold_GenQuest.foundStr + DLG_TEXT_BASE[373];
					link.l1 = DLG_TEXT_BASE[374];
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple(DLG_TEXT_BASE[368] + pchar.GenQuest.Hold_GenQuest.Name + DLG_TEXT_BASE[370],
						DLG_TEXT_BASE[375]),
						RandPhraseSimple(DLG_TEXT_BASE[376],
						DLG_TEXT_BASE[377]),
						DLG_TEXT_BASE[378] + pchar.GenQuest.Hold_GenQuest.Name + DLG_TEXT_BASE[379]);
					link.l1 = DLG_TEXT_BASE[380];	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = DLG_TEXT_BASE[381];	
					link.l1 = DLG_TEXT_BASE[382];
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = DLG_TEXT_BASE[383]+
				DLG_TEXT_BASE[384];
			link.l1 = DLG_TEXT_BASE[385];	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[386],DLG_TEXT_BASE[387],DLG_TEXT_BASE[388]);
			link.l1 = DLG_TEXT_BASE[389];
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = DLG_TEXT_BASE[390];
			link.l1 = DLG_TEXT_BASE[391];
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = DLG_TEXT_BASE[392];
			link.l1 = DLG_TEXT_BASE[393];
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = DLG_TEXT_BASE[394]+
				DLG_TEXT_BASE[395];
			link.l1 = DLG_TEXT_BASE[396];	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = DLG_TEXT_BASE[397] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[398];
			link.l1 = DLG_TEXT_BASE[399];
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = DLG_TEXT_BASE[400] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[401];
			link.l1 = DLG_TEXT_BASE[402];
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Oui, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + DLG_TEXT_BASE[403];
			link.l1 = DLG_TEXT_BASE[404];
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = DLG_TEXT_BASE[405];
			link.l1 = DLG_TEXT_BASE[406];
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "Vous, " + GetAddress_Form(pchar) + DLG_TEXT_BASE[407] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[408];
			link.l1 = DLG_TEXT_BASE[409];
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = DLG_TEXT_BASE[410] + pchar.GenQuest.CaptainComission.CapName + DLG_TEXT_BASE[411] + GetAddress_Form(pchar) + ".";
			link.l1 = DLG_TEXT_BASE[412];
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = DLG_TEXT_BASE[413];
			link.l1 = DLG_TEXT_BASE[414];
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = DLG_TEXT_BASE[415];
			link.l1 = "Oh Bien... "+ GetSexPhrase(DLG_TEXT_BASE[416],"Je vois") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = DLG_TEXT_BASE[417];
			link.l1 = DLG_TEXT_BASE[418];
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = DLG_TEXT_BASE[419]+ GetSexPhrase(DLG_TEXT_BASE[420],DLG_TEXT_BASE[421]) +DLG_TEXT_BASE[422];
				link.l1 = DLG_TEXT_BASE[423];
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[424]+ GetSexPhrase(DLG_TEXT_BASE[425],DLG_TEXT_BASE[426]) +DLG_TEXT_BASE[427];
				link.l1 = DLG_TEXT_BASE[428];
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = DLG_TEXT_BASE[429];
			link.l1 = DLG_TEXT_BASE[430];
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = DLG_TEXT_BASE[431];
			link.l1 = DLG_TEXT_BASE[432];
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = DLG_TEXT_BASE[433];
			link.l1 = DLG_TEXT_BASE[434];
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = DLG_TEXT_BASE[435];
				link.l1 = DLG_TEXT_BASE[436];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[437];
				link.l1	= DLG_TEXT_BASE[438];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[439];
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[71] + NationNameGenitive(sti(pchar.nation)) + "!", DLG_TEXT_BASE[72] + NationNameAblative(sti(pchar.nation)) + DLG_TEXT_BASE[73]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[74], DLG_TEXT_BASE[75]);
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[77], DLG_TEXT_BASE[78]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[79], DLG_TEXT_BASE[80]);
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = DLG_TEXT_BASE[95];
				link.l1 = DLG_TEXT_BASE[97];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[82];
			link.l1.go = "work_1";
			link.l2 = DLG_TEXT_BASE[102];
			link.l2.go = "work_2";
			link.l3 = DLG_TEXT_BASE[98];
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = DLG_TEXT_BASE[81];
				link.l1 = DLG_TEXT_BASE[85];
                link.l1.go = "ConvoyAreYouSure";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = DLG_TEXT_BASE[83];
					link.l1 = DLG_TEXT_BASE[84];
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (drand(6) > 1)
				{
					dialog.Text = DLG_TEXT_BASE[89];
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[90], DLG_TEXT_BASE[91]);
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[92];
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[93], DLG_TEXT_BASE[94]);
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = DLG_TEXT_BASE[86];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]);
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase(DLG_TEXT_BASE[98], DLG_TEXT_BASE[99], DLG_TEXT_BASE[100]);
			Link.l1 = DLG_TEXT_BASE[103];
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase(DLG_TEXT_BASE[104], DLG_TEXT_BASE[105], DLG_TEXT_BASE[101]);
			Link.l1 = DLG_TEXT_BASE[106];
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = DLG_TEXT_BASE[107] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[108];
				link.l1 = DLG_TEXT_BASE[109];
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = DLG_TEXT_BASE[69];
				link.l1 = DLG_TEXT_BASE[109];
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = DLG_TEXT_BASE[107] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[108];
				link.l1 = DLG_TEXT_BASE[109];
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = DLG_TEXT_BASE[107] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[108];
				link.l1 = DLG_TEXT_BASE[109];
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = DLG_TEXT_BASE[112];
				if (sti(pchar.money) >= 100)
				{
					link.l1 = DLG_TEXT_BASE[113];
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[114];
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = DLG_TEXT_BASE[115];
				link.l1 = DLG_TEXT_BASE[116];
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = DLG_TEXT_BASE[112];
					if (sti(pchar.money) >= 100)
					{
						link.l1 = DLG_TEXT_BASE[113];
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
					link.l1 = DLG_TEXT_BASE[114];
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = DLG_TEXT_BASE[115];
					link.l1 = DLG_TEXT_BASE[116];
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"
			dialog.text = DLG_TEXT_BASE[117];
			if(!isDay())
			{
				link.l1 = DLG_TEXT_BASE[118];
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[119];
				link.l1.go = "room_night";
				link.l2 = DLG_TEXT_BASE[120];
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = DLG_TEXT_BASE[121];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT_BASE[122];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT_BASE[123],
            DLG_TEXT_BASE[124]);
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = DLG_TEXT_BASE[125];
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = DLG_TEXT_BASE[126];
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = DLG_TEXT_BASE[127];
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase(DLG_TEXT_BASE[128],
            DLG_TEXT_BASE[129]);
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = DLG_TEXT_BASE[130];
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = DLG_TEXT_BASE[131];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT_BASE[132];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT_BASE[133],
            DLG_TEXT_BASE[134]);
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = DLG_TEXT_BASE[135];
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = DLG_TEXT_BASE[136];
				link.l1 = DLG_TEXT_BASE[137];
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && drand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && drand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = DLG_TEXT_BASE[138];
				link.l1 = DLG_TEXT_BASE[139];
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = DLG_TEXT_BASE[140];
			link.l1 = DLG_TEXT_BASE[141];
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = DLG_TEXT_BASE[440];
			link.l1 = DLG_TEXT_BASE[441];
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = DLG_TEXT_BASE[442]+ GetSexPhrase("monsieur","mademoiselle") +".";
			link.l1 = DLG_TEXT_BASE[443];
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Je vous demande pardon "+ GetSexPhrase("mister le","miss la") +DLG_TEXT_BASE[444];
			link.l1 = DLG_TEXT_BASE[445];
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +DLG_TEXT_BASE[446];
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = DLG_TEXT_BASE[447];
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[448];
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" capitaine.";
				link.l1 = DLG_TEXT_BASE[449];
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Non, mis"+ GetSexPhrase("ter","s") +DLG_TEXT_BASE[450];
			link.l1 = DLG_TEXT_BASE[451];
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Parce que, mis"+ GetSexPhrase("ter","s") +DLG_TEXT_BASE[452];
			link.l1 = DLG_TEXT_BASE[453];
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = DLG_TEXT_BASE[454]+ GetSexPhrase("ter","s") +DLG_TEXT_BASE[455] + PChar.GenQuest.ChurchQuest_1.CapFullName + DLG_TEXT_BASE[456];
			link.l1 = DLG_TEXT_BASE[457];
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+ GetSexPhrase("ter","s") +"... Mis"+ GetSexPhrase("ter","s") +DLG_TEXT_BASE[458];
			link.l1 = DLG_TEXT_BASE[459];
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+ DLG_TEXT_BASE[460];
			link.l1 = DLG_TEXT_BASE[461]+pchar.GenQuest.Device.Shipyarder.Describe+DLG_TEXT_BASE[462];
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = DLG_TEXT_BASE[463];
				link.l1 = DLG_TEXT_BASE[464];
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[465];
				link.l1 = DLG_TEXT_BASE[466];
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+DLG_TEXT_BASE[467];
				link.l1 = DLG_TEXT_BASE[468];
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+DLG_TEXT_BASE[469];
				link.l1 = DLG_TEXT_BASE[470];
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = DLG_TEXT_BASE[471];
			link.l1 = DLG_TEXT_BASE[472];
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = DLG_TEXT_BASE[473];
					link.l1 = DLG_TEXT_BASE[474];
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = DLG_TEXT_BASE[475];
					link.l1 = DLG_TEXT_BASE[476];
					link.l1.go = "Fernando_Sea";
				}
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[477];
				link.l1 = DLG_TEXT_BASE[478];
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = DLG_TEXT_BASE[479];
			link.l1 = "Merci, " + npchar.name + ".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, monsieur, "+pchar.GenQuest.Marginpassenger.q2Name+" est mort il y a "+LinkRandPhrase("un mois","trois semaines","deux mois")+". "+LinkRandPhrase(DLG_TEXT_BASE[480],DLG_TEXT_BASE[481],DLG_TEXT_BASE[482])+DLG_TEXT_BASE[483];
				link.l1 = DLG_TEXT_BASE[484] + npchar.name + ".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+DLG_TEXT_BASE[485];
				link.l1 = DLG_TEXT_BASE[486];
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[487]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[488], DLG_TEXT_BASE[489], DLG_TEXT_BASE[490], DLG_TEXT_BASE[491], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[492], DLG_TEXT_BASE[493], DLG_TEXT_BASE[494], DLG_TEXT_BASE[495], npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[496], DLG_TEXT_BASE[497], DLG_TEXT_BASE[498], DLG_TEXT_BASE[499], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[500], DLG_TEXT_BASE[501], DLG_TEXT_BASE[502], DLG_TEXT_BASE[503], npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = DLG_TEXT_BASE[504];
			link.l1 = DLG_TEXT_BASE[505];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "citiz_31", "man", "man", 10, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
		break;
		
		case "Sharlie_skiper":
			dialog.text = DLG_TEXT_BASE[506];
			link.l1 = DLG_TEXT_BASE[507];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		break;
		//<-- Бремя гасконца
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = DLG_TEXT_BASE[511]+sld.name+DLG_TEXT_BASE[512];
			link.l1 = DLG_TEXT_BASE[513];
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}
