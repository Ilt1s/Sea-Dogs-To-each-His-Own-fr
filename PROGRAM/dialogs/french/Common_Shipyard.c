// boal 08/04/06 общий диалог верфи
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "SD\TEXT\DIALOGS\Common_Shipyard.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = DLG_TEXT_BASE[166];
					Link.l1 = DLG_TEXT_BASE[167];
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = DLG_TEXT_BASE[168];
					Link.l1 = DLG_TEXT_BASE[169];
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = DLG_TEXT_BASE[170];
				Link.l1 = DLG_TEXT_BASE[171];
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = DLG_TEXT_BASE[650];
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = DLG_TEXT_BASE[651];
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = DLG_TEXT_BASE[652];
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = DLG_TEXT_BASE[653];
					link.l1 = DLG_TEXT_BASE[654];
					link.l1.go = "FMQM_oil_4";
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = DLG_TEXT_BASE[655];
				link.l1 = DLG_TEXT_BASE[656]; 
				link.l1.go = "mtraxx_x";
				break;
			}			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[172],DLG_TEXT_BASE[173],DLG_TEXT_BASE[174]), LinkRandPhrase(DLG_TEXT_BASE[175],DLG_TEXT_BASE[176],DLG_TEXT_BASE[177]), LinkRandPhrase(DLG_TEXT_BASE[178],DLG_TEXT_BASE[179],DLG_TEXT_BASE[180]),LinkRandPhrase(DLG_TEXT_BASE[181],DLG_TEXT_BASE[182],DLG_TEXT_BASE[183]));
				Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[184]+GetFullName(pchar)+DLG_TEXT_BASE[185],DLG_TEXT_BASE[186]+GetFullName(pchar)+DLG_TEXT_BASE[187]+pchar.ship.name+"'.",DLG_TEXT_BASE[188]+GetFullName(pchar)+DLG_TEXT_BASE[189]+pchar.ship.name+DLG_TEXT_BASE[190]);
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[191]+GetFullName(pchar)+DLG_TEXT_BASE[192],DLG_TEXT_BASE[193]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[194],DLG_TEXT_BASE[195]+GetFullName(pchar)+DLG_TEXT_BASE[196]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[197]),LinkRandPhrase(DLG_TEXT_BASE[198],DLG_TEXT_BASE[199]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[200],DLG_TEXT_BASE[201]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[202]),LinkRandPhrase(DLG_TEXT_BASE[203]+GetFullName(pchar)+DLG_TEXT_BASE[204],DLG_TEXT_BASE[205]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[206],DLG_TEXT_BASE[207])),LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[208]+GetFullName(pchar)+DLG_TEXT_BASE[209],DLG_TEXT_BASE[210]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[211]+GetFullName(pchar)+DLG_TEXT_BASE[212],"Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[213]),LinkRandPhrase(""+GetAddress_Form(NPChar)+DLG_TEXT_BASE[214],"Oh, "+GetAddress_Form(NPChar)+DLG_TEXT_BASE[215],DLG_TEXT_BASE[216]+GetFullName(pchar)+DLG_TEXT_BASE[217]),LinkRandPhrase(DLG_TEXT_BASE[218]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[219],"Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[220],DLG_TEXT_BASE[221]+XI_ConvertString("Colony"+npchar.City+"Acc")+DLG_TEXT_BASE[222])));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[223],DLG_TEXT_BASE[224]),RandPhraseSimple(DLG_TEXT_BASE[225],DLG_TEXT_BASE[226])),RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[227],DLG_TEXT_BASE[228]),RandPhraseSimple(DLG_TEXT_BASE[229],DLG_TEXT_BASE[230])));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = DLG_TEXT_BASE[28];
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = DLG_TEXT_BASE[231];
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = DLG_TEXT_BASE[232];
			    link.l15.go = "Tasks";
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = DLG_TEXT_BASE[233]+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+DLG_TEXT_BASE[234];
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = DLG_TEXT_BASE[235]+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
				{
					link.l12 = DLG_TEXT_BASE[133];
					link.l12.go = "SailsGerald";
				}
				Link.l2 = DLG_TEXT_BASE[41];
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = DLG_TEXT_BASE[42];
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple(DLG_TEXT_BASE[43] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[44]);
					link.l7.go = "IntelligenceForAll";
				}
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = DLG_TEXT_BASE[33];
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }				
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = DLG_TEXT_BASE[236]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = DLG_TEXT_BASE[237]; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = DLG_TEXT_BASE[238];
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = DLG_TEXT_BASE[36];
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = DLG_TEXT_BASE[37];
				Link.l1 = DLG_TEXT_BASE[38] + GetFullName(NPChar) + DLG_TEXT_BASE[39];
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = DLG_TEXT_BASE[40];
					link.l13.go = "Cannons";
				}									
				link.l15 = DLG_TEXT_BASE[239];
			    link.l15.go = "Tasks";
				
				if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
				{
					link.l12 = DLG_TEXT_BASE[133];
					link.l12.go = "SailsGerald";
				}
				Link.l2 = DLG_TEXT_BASE[29];		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = DLG_TEXT_BASE[30];
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple(DLG_TEXT_BASE[31] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[32]);
					link.l7.go = "IntelligenceForAll";
				}
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = DLG_TEXT_BASE[33];
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }				
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = DLG_TEXT_BASE[240]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = DLG_TEXT_BASE[241]; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = DLG_TEXT_BASE[242];
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = DLG_TEXT_BASE[243];
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = DLG_TEXT_BASE[46];
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = DLG_TEXT_BASE[244];
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[245],
			          DLG_TEXT_BASE[246],
					  DLG_TEXT_BASE[247]);
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 6)
				{
					dialog.Text = DLG_TEXT_BASE[248];
					Link.l1 = DLG_TEXT_BASE[249];
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = DLG_TEXT_BASE[250];
					Link.l1 = DLG_TEXT_BASE[251];
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = DLG_TEXT_BASE[252] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				s2 = s2 + DLG_TEXT_BASE[253];
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + DLG_TEXT_BASE[254];
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + DLG_TEXT_BASE[255];
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + DLG_TEXT_BASE[256];
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + DLG_TEXT_BASE[257];
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = DLG_TEXT_BASE[258];
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = DLG_TEXT_BASE[259];
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = DLG_TEXT_BASE[260];
						Link.l3.go = "ship_tunning_not_now_1";											
					}	
					else
					{
						Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[261],
						                         DLG_TEXT_BASE[262],
												 DLG_TEXT_BASE[263]);
						Link.l1.go = "ship_tunning_not_now_1";					
					}
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = DLG_TEXT_BASE[264];
							Link.l1.go = "ship_c_quantity";
						}	
						if(GetPossibilityCannonsUpgrade(pchar, false) > 0)
						{
							Link.l2 = DLG_TEXT_BASE[265];
							Link.l2.go = "ship_tunning_Capacity";
						}
						Link.l3 = DLG_TEXT_BASE[266];
						Link.l3.go = "ship_tunning_not_now_1";											
					}
					else
					{
						Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[267],
						                        DLG_TEXT_BASE[268],
												 DLG_TEXT_BASE[269]);
						Link.l1.go = "ship_tunning_not_now_1";					
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = DLG_TEXT_BASE[270];
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = DLG_TEXT_BASE[271];
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = DLG_TEXT_BASE[272];
						Link.l3.go = "ship_tunning_not_now_1";											
					}	
					else
					{
						Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[273],
						                         DLG_TEXT_BASE[274],
												 DLG_TEXT_BASE[275]);
						Link.l1.go = "ship_tunning_not_now_1";					
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = DLG_TEXT_BASE[276];
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = DLG_TEXT_BASE[277];
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = DLG_TEXT_BASE[278];
						Link.l3.go = "ship_tunning_not_now_1";											
					}
					else
					{
						Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[279],
						                         DLG_TEXT_BASE[280],
												 DLG_TEXT_BASE[281]);
						Link.l1.go = "ship_tunning_not_now_1";					
					}												
				}								
			}
			else
			{
				dialog.Text = DLG_TEXT_BASE[282];
			    Link.l1 = DLG_TEXT_BASE[283];
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = DLG_TEXT_BASE[284] + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + DLG_TEXT_BASE[285] + Material + ".";
			s2 = s2 + DLG_TEXT_BASE[286] + WorkPrice + DLG_TEXT_BASE[287];			
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[288];
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = DLG_TEXT_BASE[289];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = DLG_TEXT_BASE[290];
			    link.l1 = LinkRandPhrase(DLG_TEXT_BASE[291],
										 DLG_TEXT_BASE[292],
										 DLG_TEXT_BASE[293]);
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[294] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				DLG_TEXT_BASE[295] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[296] + NPChar.Tuning.Money + DLG_TEXT_BASE[297]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[298];
				link.l1 = DLG_TEXT_BASE[299];
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = DLG_TEXT_BASE[300];
			    Link.l1 = DLG_TEXT_BASE[301];
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = DLG_TEXT_BASE[302];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = GetSexPhrase("Monsieur","Madame") +DLG_TEXT_BASE[303];
			    Link.l1 = DLG_TEXT_BASE[304];
			    Link.l1.go = "Exit";
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[305];
			    link.l1 = DLG_TEXT_BASE[306];
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text =DLG_TEXT_BASE[307] + sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[308];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[309]+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}			
	        shTo.Tuning.Capacity = true;
			
			makearef(refShip, pchar.Ship);
			if(CheckAttribute(refShip,"CannonDiff")) 	iCannonDiff = sti(refShip.CannonDiff);
			else										iCannonDiff = 0;
			
			iCannonDiff += 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;					
				if(i >= sti(shTo.cannonr) - iCannonDiff)	
				{
					refShip.Cannons.Borts.cannonr.damages.(attr) = 2.0; 
				}
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i >= sti(shTo.cannonl) - iCannonDiff)	
				{
					refShip.Cannons.Borts.cannonl.damages.(attr) = 2.0; 
				}
			}	
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;

			shTo.DontTuning.Cannon = true;
			
	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[310];
			Link.l1 = DLG_TEXT_BASE[311];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = DLG_TEXT_BASE[312] + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + DLG_TEXT_BASE[313]+ Material + ".";
			s2 = s2 +DLG_TEXT_BASE[314] + WorkPrice + DLG_TEXT_BASE[315];						
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[316];
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = DLG_TEXT_BASE[317];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = DLG_TEXT_BASE[318];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[319],
										 DLG_TEXT_BASE[320],
										 DLG_TEXT_BASE[321]);
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[322] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				DLG_TEXT_BASE[323] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[324] + NPChar.Tuning.Money + DLG_TEXT_BASE[325]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[326];
				link.l1 = DLG_TEXT_BASE[327];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = DLG_TEXT_BASE[328];
			    Link.l1 = DLG_TEXT_BASE[329];
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = DLG_TEXT_BASE[330];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") + DLG_TEXT_BASE[331];
			    Link.l1 = DLG_TEXT_BASE[332];
			    Link.l1.go = "Exit";			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[333];
			    link.l1 = DLG_TEXT_BASE[334];
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = DLG_TEXT_BASE[335]+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[336];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_BASE[337] + sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
			else
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}		
	        shTo.Tuning.SpeedRate = true;
			
			shTo.WindAgainstSpeed   	= stf(shTo.WindAgainstSpeed) + 0.15 * stf(shTo.WindAgainstSpeed);
			shTo.DontTuning.WindAgainst = true;
	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[338];
			Link.l1 = DLG_TEXT_BASE[339];
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = DLG_TEXT_BASE[340] + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + DLG_TEXT_BASE[341]+ Material + ".";
			s2 = s2 +DLG_TEXT_BASE[342] + WorkPrice + DLG_TEXT_BASE[343];										
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[344];
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = DLG_TEXT_BASE[345];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = DLG_TEXT_BASE[346];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[347],
										 DLG_TEXT_BASE[348],
										 DLG_TEXT_BASE[349]);			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[350] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				DLG_TEXT_BASE[351] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[352] + NPChar.Tuning.Money + DLG_TEXT_BASE[353]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[354];
				link.l1 = DLG_TEXT_BASE[355];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = DLG_TEXT_BASE[356];
			    Link.l1 = DLG_TEXT_BASE[357];
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = DLG_TEXT_BASE[358];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") +DLG_TEXT_BASE[359];
			    Link.l1 = DLG_TEXT_BASE[360];
			    Link.l1.go = "Exit";			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[361];
			    link.l1 = DLG_TEXT_BASE[362];
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = DLG_TEXT_BASE[363] + sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[364];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[365] + sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	
			
			shTo.MinCrew = sti(shTo.MinCrew) + makeint(sti(shTo.MinCrew) * 0.15);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
			shTo.DontTuning.MinCrew = true;	
	        shTo.Tuning.TurnRate = true;
            NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[366];
			Link.l1 = DLG_TEXT_BASE[367];
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = DLG_TEXT_BASE[368] + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " hommes.";			
			s2 = s2 + DLG_TEXT_BASE[369]+ Material + ".";
			s2 = s2 + DLG_TEXT_BASE[370] + WorkPrice + DLG_TEXT_BASE[371];									
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[372];
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = DLG_TEXT_BASE[373];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = DLG_TEXT_BASE[374];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[375],
										 DLG_TEXT_BASE[376],
										 DLG_TEXT_BASE[377]);
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[378] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				DLG_TEXT_BASE[379] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[380] + NPChar.Tuning.Money + DLG_TEXT_BASE[381]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[382];
				link.l1 = DLG_TEXT_BASE[383];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = DLG_TEXT_BASE[384];
			    Link.l1 = DLG_TEXT_BASE[385];
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = DLG_TEXT_BASE[386];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") + DLG_TEXT_BASE[387];
			    Link.l1 = DLG_TEXT_BASE[388];				
			    Link.l1.go = "Exit";
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[389];
			    link.l1 = DLG_TEXT_BASE[390];
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = DLG_TEXT_BASE[391]+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[392];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[393]+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
			
			shTo.HP = sti(shTo.HP) - makeint(sti(shTo.HP) * 0.15);
			shTo.BaseHP = sti(shTo.HP);
			shTo.DontTuning.HP = true;	
	       
            NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[394];
			Link.l1 = DLG_TEXT_BASE[395];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = DLG_TEXT_BASE[396] + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " hommes.";			
			s2 = s2 + DLG_TEXT_BASE[397]+ Material + ".";
			s2 = s2 + DLG_TEXT_BASE[398] + WorkPrice + DLG_TEXT_BASE[399];									
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[400];
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = DLG_TEXT_BASE[401];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = DLG_TEXT_BASE[402];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[403],
										 DLG_TEXT_BASE[404],
										 DLG_TEXT_BASE[405]);
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[406] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				DLG_TEXT_BASE[407] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[408] + NPChar.Tuning.Money + DLG_TEXT_BASE[409]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[410];
				link.l1 = DLG_TEXT_BASE[411];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = DLG_TEXT_BASE[412];
			    Link.l1 = DLG_TEXT_BASE[413];
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = DLG_TEXT_BASE[414];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") +DLG_TEXT_BASE[415];
			    Link.l1 =DLG_TEXT_BASE[416];
			    Link.l1.go = "Exit";			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[417];
			    link.l1 = DLG_TEXT_BASE[418];
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = DLG_TEXT_BASE[419]+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[420];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[421]+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			shTo.TurnRate = (stf(shTo.TurnRate) - stf(shTo.TurnRate) * 0.15);
			shTo.DontTuning.TurnRate = true;
	       
            NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[422];
			Link.l1 = DLG_TEXT_BASE[423];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = DLG_TEXT_BASE[424] + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + DLG_TEXT_BASE[425]+ Material + ".";
			s2 = s2 + DLG_TEXT_BASE[426] + WorkPrice + DLG_TEXT_BASE[427];									
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[428];
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = DLG_TEXT_BASE[429];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = DLG_TEXT_BASE[430];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[431],
										 DLG_TEXT_BASE[432],
										 DLG_TEXT_BASE[433]);
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[434] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				DLG_TEXT_BASE[435] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[436] + NPChar.Tuning.Money + DLG_TEXT_BASE[437]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[438];
				link.l1 = DLG_TEXT_BASE[439];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = DLG_TEXT_BASE[440];
			    Link.l1 = DLG_TEXT_BASE[441];
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = DLG_TEXT_BASE[442];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") + DLG_TEXT_BASE[443];
			    Link.l1 = DLG_TEXT_BASE[444];
			    Link.l1.go = "Exit";			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[445];
			    link.l1 = DLG_TEXT_BASE[446];
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = DLG_TEXT_BASE[447] + sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[448];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[449] + sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}	
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);
			
	        shTo.MaxCrew = sti(shTo.MaxCrew) - makeint(sti(shTo.MaxCrew) * 0.15);
			shTo.DontTuning.MaxCrew = true;	
			
            NextDiag.TempNode = "First time";
			
			dialog.Text = DLG_TEXT_BASE[450];
			Link.l1 = DLG_TEXT_BASE[451];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed) * 90.0);
			s2 = DLG_TEXT_BASE[452] + makeint(fTmp) + DLG_TEXT_BASE[453];
			s2 = s2 + DLG_TEXT_BASE[454]+ Material + ",";
			s2 = s2 + DLG_TEXT_BASE[455] + WorkPrice + DLG_TEXT_BASE[456];									
            dialog.Text = s2;
			Link.l1 = DLG_TEXT_BASE[457];
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = DLG_TEXT_BASE[458];
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    		
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = DLG_TEXT_BASE[459];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[460],
										 DLG_TEXT_BASE[461],
										 DLG_TEXT_BASE[462]);
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[463] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				DLG_TEXT_BASE[464] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[465] + NPChar.Tuning.Money + DLG_TEXT_BASE[466]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = DLG_TEXT_BASE[467];
				link.l1 = DLG_TEXT_BASE[468];
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = DLG_TEXT_BASE[469];
			    Link.l1 = DLG_TEXT_BASE[470];
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = DLG_TEXT_BASE[471];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") + DLG_TEXT_BASE[472];
			    Link.l1 = DLG_TEXT_BASE[473];
			    Link.l1.go = "Exit";
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = DLG_TEXT_BASE[474];
			    link.l1 = DLG_TEXT_BASE[475];
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = DLG_TEXT_BASE[476]+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[477];
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[478]+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
	        shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) - 0.15 * stf(shTo.WindAgainstSpeed);			
	        shTo.Tuning.WindAgainst = true;
			
			shTo.SpeedRate = (stf(shTo.SpeedRate) - stf(shTo.SpeedRate)* 0.15);
			shTo.DontTuning.SpeedRate = true;	
	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[479];
			Link.l1 = DLG_TEXT_BASE[480];
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = DLG_TEXT_BASE[481] + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + DLG_TEXT_BASE[482] + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + DLG_TEXT_BASE[483]+ Material + ",";
			s2 = s2 + DLG_TEXT_BASE[484] + WorkPrice + DLG_TEXT_BASE[485];						
			dialog.Text = s2;		
			Link.l1 = DLG_TEXT_BASE[486];
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = DLG_TEXT_BASE[487];
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			if(GetCharacterItem(pchar,"gold_dublon") >= amount)		    		
			{
				TakeNItems(pchar,"gold_dublon", -amount);								
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = DLG_TEXT_BASE[488];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[489],
										 DLG_TEXT_BASE[490],
										 DLG_TEXT_BASE[491]);
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[492] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				DLG_TEXT_BASE[493] + NPChar.Tuning.Matherial + DLG_TEXT_BASE[494] + NPChar.Tuning.Money + DLG_TEXT_BASE[495]);				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = DLG_TEXT_BASE[496];
				link.l1 = DLG_TEXT_BASE[497];
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = DLG_TEXT_BASE[498];
				Link.l1 = DLG_TEXT_BASE[499];
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = DLG_TEXT_BASE[500];
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = GetSexPhrase("Monsieur","Madame") +DLG_TEXT_BASE[501];
			    Link.l1 = DLG_TEXT_BASE[502];
				Link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = DLG_TEXT_BASE[503];
				link.l1 = DLG_TEXT_BASE[504];
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = DLG_TEXT_BASE[505]+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = DLG_TEXT_BASE[506];
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_BASE[507]+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			shTo.Capacity = sti(shTo.Capacity) - makeint(sti(shTo.Capacity) * 0.15);
			shTo.DontTuning.Capacity = true;
			
			NextDiag.TempNode = "First time";
			dialog.Text = DLG_TEXT_BASE[508];
			Link.l1 = DLG_TEXT_BASE[509];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (drand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = DLG_TEXT_BASE[510]+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+DLG_TEXT_BASE[511]+DLG_TEXT_BASE[512];
					link.l1 = DLG_TEXT_BASE[513];
					link.l1.go = "Findship";
					link.l2 = DLG_TEXT_BASE[514];
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (drand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (crand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = DLG_TEXT_BASE[515];
							pchar.GenQuest.Device.Shipyarder.Describe = DLG_TEXT_BASE[516];
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = DLG_TEXT_BASE[517];
							pchar.GenQuest.Device.Shipyarder.Describe = DLG_TEXT_BASE[518];
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = DLG_TEXT_BASE[519];
							pchar.GenQuest.Device.Shipyarder.Describe = DLG_TEXT_BASE[520];
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = DLG_TEXT_BASE[521];
							pchar.GenQuest.Device.Shipyarder.Describe = DLG_TEXT_BASE[522];
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = DLG_TEXT_BASE[523];
							pchar.GenQuest.Device.Shipyarder.Describe = DLG_TEXT_BASE[524];
						break; 
					}
					dialog.text = DLG_TEXT_BASE[525]+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[526]+DLG_TEXT_BASE[527];
					link.l1 = DLG_TEXT_BASE[528];
					link.l1.go = "Device";
					link.l2 = DLG_TEXT_BASE[529];
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = DLG_TEXT_BASE[530];
			link.l1 = DLG_TEXT_BASE[531];
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = DLG_TEXT_BASE[532];
			link.l1 = DLG_TEXT_BASE[533]+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = DLG_TEXT_BASE[534]+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+DLG_TEXT_BASE[535];
			link.l1 = DLG_TEXT_BASE[536] + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 2) iType = SHIP_SCHOONER; 
			if (sti(pchar.rank) >= 2 && sti(pchar.rank) < 5) iType = SHIP_BRIGANTINE; 
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 7) iType = SHIP_BRIG; 
			if (sti(pchar.rank) >= 7) iType = SHIP_CORVETTE + rand(makeint(SHIP_GALEON_H - SHIP_CORVETTE)); 
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = DLG_TEXT_BASE[537]+pchar.GenQuest.Device.Shipyarder.Describe+DLG_TEXT_BASE[538];
			link.l1 = DLG_TEXT_BASE[539];
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Gen"));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = DLG_TEXT_BASE[540];
			link.l1 = DLG_TEXT_BASE[541];
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = DLG_TEXT_BASE[542]+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+DLG_TEXT_BASE[543];
			link.l1 = DLG_TEXT_BASE[544];
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = DLG_TEXT_BASE[545];
				link.l1 = DLG_TEXT_BASE[546];
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = DLG_TEXT_BASE[547]+ GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType, "Name") + "Gen")) +DLG_TEXT_BASE[548];
			link.l1 = DLG_TEXT_BASE[549];
			link.l1.go = "Device_complete_4";
			link.l2 = DLG_TEXT_BASE[550];
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		case "Device_complete_5":
			dialog.text = DLG_TEXT_BASE[551];
			link.l1 = DLG_TEXT_BASE[552];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = DLG_TEXT_BASE[553];
				link.l1 = DLG_TEXT_BASE[554];
				link.l1.go = "exit";
			}
			else
			{
				sTemp = DLG_TEXT_BASE[555];
				sTemp = sTemp + DLG_TEXT_BASE[556] + sti(pchar.questTemp.different.GiveShipLetters.price2) + DLG_TEXT_BASE[557];
				dialog.text = sTemp;
				link.l1	= DLG_TEXT_BASE[558];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[559] + GetFullName(NPChar) + DLG_TEXT_BASE[560];
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = DLG_TEXT_BASE[561];
			link.l1 = DLG_TEXT_BASE[562];
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = DLG_TEXT_BASE[563]+DLG_TEXT_BASE[564];
			link.l1 = DLG_TEXT_BASE[565];
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = DLG_TEXT_BASE[566]+DLG_TEXT_BASE[567];
			link.l1 = DLG_TEXT_BASE[568];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = DLG_TEXT_BASE[569];
				link.l1 = DLG_TEXT_BASE[570];
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[571]+ GetSexPhrase(DLG_TEXT_BASE[572],DLG_TEXT_BASE[573]) +DLG_TEXT_BASE[574];
				link.l1 = DLG_TEXT_BASE[575];
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = DLG_TEXT_BASE[576];
			link.l1 = DLG_TEXT_BASE[577];
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text =+DLG_TEXT_BASE[578];
			link.l1 = DLG_TEXT_BASE[579];
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
			dialog.text = DLG_TEXT_BASE[580];
			link.l1 = DLG_TEXT_BASE[581];
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
		
		case "shipyard":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[47],
				                                                     DLG_TEXT_BASE[48]),
													  pcharrepphrase(DLG_TEXT_BASE[49] +GetFullName(pchar)+ DLG_TEXT_BASE[50],
													                 DLG_TEXT_BASE[51]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[52],
				                                                 DLG_TEXT_BASE[53] +GetFullName(npchar)+ DLG_TEXT_BASE[54]),
												  pcharrepphrase(DLG_TEXT_BASE[55],
												                 DLG_TEXT_BASE[56]));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[57],
				                                                     DLG_TEXT_BASE[58]),
													  pcharrepphrase(DLG_TEXT_BASE[59] +GetFullName(pchar)+ DLG_TEXT_BASE[60],
													                 DLG_TEXT_BASE[61]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[62],
				                                                 DLG_TEXT_BASE[63] +GetFullName(npchar)+ DLG_TEXT_BASE[64]),
												  pcharrepphrase(DLG_TEXT_BASE[65],
												                 DLG_TEXT_BASE[66]));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = DLG_TEXT_BASE[582] +
				              FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  DLG_TEXT_BASE[583] +
							  FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  DLG_TEXT_BASE[584];
							  
			    link.l1 = DLG_TEXT_BASE[585];
			    link.l1.go = "SailsColorChoose";
			    link.l2 = DLG_TEXT_BASE[586];
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = DLG_TEXT_BASE[587]; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = DLG_TEXT_BASE[588];
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[57],
				                                                     DLG_TEXT_BASE[58]),
													  pcharrepphrase(DLG_TEXT_BASE[59] +GetFullName(pchar)+ DLG_TEXT_BASE[60],
													                 DLG_TEXT_BASE[61]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[62],
				                                                 DLG_TEXT_BASE[63] +GetFullName(npchar)+ DLG_TEXT_BASE[64]),
												  pcharrepphrase(DLG_TEXT_BASE[65],
												                 DLG_TEXT_BASE[66]));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = DLG_TEXT_BASE[589] + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = DLG_TEXT_BASE[590]+GetSailsType(6) + ".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = DLG_TEXT_BASE[591]+GetSailsType(7)  + ".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = DLG_TEXT_BASE[592]+GetSailsType(8)  + ".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = DLG_TEXT_BASE[593]+GetSailsType(9)  + ".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = DLG_TEXT_BASE[594]+GetSailsType(10)  + ".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = DLG_TEXT_BASE[595]+GetSailsType(11)  + ".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = DLG_TEXT_BASE[596];
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = DLG_TEXT_BASE[597]+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+DLG_TEXT_BASE[598]+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+DLG_TEXT_BASE[599]+ FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) +DLG_TEXT_BASE[600];

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = DLG_TEXT_BASE[601];
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = DLG_TEXT_BASE[602];
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = DLG_TEXT_BASE[603];
		    Link.l9 = DLG_TEXT_BASE[604];
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = DLG_TEXT_BASE[605] + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = SailsColors[i].name;
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = DLG_TEXT_BASE[606];
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[607];
			    Link.l9 = DLG_TEXT_BASE[608];
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = DLG_TEXT_BASE[609]+ GetStrSmallRegister(SailsColors[sti(NPChar.SailsColorIdx)].name);
		    Link.l9 = DLG_TEXT_BASE[610];
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = DLG_TEXT_BASE[611];
				    Link.l9 = DLG_TEXT_BASE[612];
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[613];
			    Link.l9 = DLG_TEXT_BASE[614];
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = DLG_TEXT_BASE[615];
			link.l1 = DLG_TEXT_BASE[616];
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = DLG_TEXT_BASE[617]+DLG_TEXT_BASE[618];
				link.l1 = DLG_TEXT_BASE[619];
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = DLG_TEXT_BASE[620];
			link.l1 = DLG_TEXT_BASE[621];
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = DLG_TEXT_BASE[622]+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = DLG_TEXT_BASE[623];
			dialog.text = DLG_TEXT_BASE[624]+DLG_TEXT_BASE[625]+sTemp+DLG_TEXT_BASE[626];
			if (sti(Pchar.money) >= 17000)
			{
				link.l1 = DLG_TEXT_BASE[627];
				link.l1.go = "Sharlie_4";
			}
			link.l2 = DLG_TEXT_BASE[628];
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = DLG_TEXT_BASE[629];
				Link.l1 = DLG_TEXT_BASE[630];
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = DLG_TEXT_BASE[631];
					link.l1 = DLG_TEXT_BASE[632];
					link.l1.go = "Sharlie_6";
				}
				else
			{
				dialog.text = DLG_TEXT_BASE[633];
				if (sti(Pchar.money) >= 17000)
				{
					link.l1 = DLG_TEXT_BASE[634];
					link.l1.go = "Sharlie_4";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[635];
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -17000);
			dialog.text = DLG_TEXT_BASE[636];
			link.l1 = DLG_TEXT_BASE[637];
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 700, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			AddCharacterGoods(pchar, GOOD_BALLS, 50);
			AddCharacterGoods(pchar, GOOD_GRAPES, 50);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 50);
			AddCharacterGoods(pchar, GOOD_BOMBS, 50);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = DLG_TEXT_BASE[638];
					link.l1 = DLG_TEXT_BASE[639];
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[640];
					link.l1 = DLG_TEXT_BASE[641];
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = DLG_TEXT_BASE[642]+DLG_TEXT_BASE[643];
			link.l1 = DLG_TEXT_BASE[644];
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = DLG_TEXT_BASE[645];
			link.l1 = DLG_TEXT_BASE[646];
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipHand(SHIP_SLOOP, 6, 700, 50, 790, 20000, 13.1, 50.1, 1.25);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.ship.HP = sti(pchar.ship.HP) - makeint(sti(pchar.ship.HP)/2);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
		break;
		
		case "Sharlie_shipwait":
			dialog.text = DLG_TEXT_BASE[647];
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = DLG_TEXT_BASE[648];
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[649];
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = DLG_TEXT_BASE[657];
			link.l1 = DLG_TEXT_BASE[658];
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = DLG_TEXT_BASE[659];
			link.l1 = DLG_TEXT_BASE[660];
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = DLG_TEXT_BASE[661];
			link.l1 = DLG_TEXT_BASE[662];
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = DLG_TEXT_BASE[663];
			link.l1 = DLG_TEXT_BASE[664];
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = DLG_TEXT_BASE[665];
			link.l1 = DLG_TEXT_BASE[666];
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = DLG_TEXT_BASE[667];
			link.l1 = DLG_TEXT_BASE[668];
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = DLG_TEXT_BASE[669];
			link.l1 = DLG_TEXT_BASE[670];
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;		
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) == 1) iRank = 0;
	if (sti(pchar.rank) > 1 && sti(pchar.rank) <= 2) iRank = 1;
	if (sti(pchar.rank) > 2 && sti(pchar.rank) <= 4) iRank = 2;
	if (sti(pchar.rank) > 4 && sti(pchar.rank) <= 7) iRank = 3;
	if (sti(pchar.rank) > 7 && sti(pchar.rank) <= 10) iRank = 4;
	if (sti(pchar.rank) > 10 && sti(pchar.rank) <= 18) iRank = 5;
	
	switch (iRank)
	{
		case 0:  
			pchar.GenQuest.Findship.Shipyarder.ShipType = SHIP_SCHOONER + rand(makeint(SHIP_BARQUE - SHIP_SCHOONER));
		break; 		
		case 1:  
			pchar.GenQuest.Findship.Shipyarder.ShipType = SHIP_BARKENTINE + rand(makeint(SHIP_SHNYAVA- SHIP_BARKENTINE));
		break;
		case 2:  
			pchar.GenQuest.Findship.Shipyarder.ShipType = SHIP_FLEUT + rand(makeint(SHIP_CARAVEL - SHIP_FLEUT));
		break;
		case 3:  
			pchar.GenQuest.Findship.Shipyarder.ShipType = SHIP_PINNACE + rand(makeint(SHIP_CARACCA - SHIP_PINNACE));	
		break;
		case 4:  
			pchar.GenQuest.Findship.Shipyarder.ShipType = SHIP_SCHOONER_W + rand(makeint(SHIP_POLACRE - SHIP_SCHOONER_W));
		break;
		case 5:  
			pchar.GenQuest.Findship.Shipyarder.ShipType = SHIP_NAVIO + rand(makeint(SHIP_FRIGATE_H - SHIP_NAVIO));
		break;
	}
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	int Material 	= makeint((20 * (7 - shipClass) + 15 * MOD_SKILL_ENEMY_RATE + drand(shipMinCrew)) * fQuestShip);
	int WorkPrice 	= makeint(fQuestShip * shipPrice/500.0);
		
	if(Material < 1) 		Material 	= 1;
	if(WorkPrice < 10) 		WorkPrice 	= 10;
	
	if(MaterialNum == 1) return Material;	
	if(MaterialNum == 2) return WorkPrice;
	
	return 0;
}
