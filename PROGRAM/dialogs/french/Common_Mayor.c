#include "SD\TEXT\DIALOGS\Common_Mayor.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool   bOk;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
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
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10]));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = DLG_TEXT_BASE[526];
					link.l1 = DLG_TEXT_BASE[527];
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = DLG_TEXT_BASE[526];
					link.l1 = DLG_TEXT_BASE[527];
					link.l1.go = "quests";
					break;
				}
                dialog.text = DLG_TEXT_BASE[12];
				link.l1 = DLG_TEXT_BASE[13];
				link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = DLG_TEXT_BASE[14] + GetFullName(pchar) + DLG_TEXT_BASE[15];
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = DLG_TEXT_BASE[16];
				    link.l1.go = "arestFree_1";
                }
				link.l2 = DLG_TEXT_BASE[17];
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = DLG_TEXT_BASE[19];
				link.l1 = DLG_TEXT_BASE[20];
				link.l1.go = "fight"; 
				break;
			}			
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = DLG_TEXT_BASE[528];
				link.l1 = DLG_TEXT_BASE[529];
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = DLG_TEXT_BASE[530];
					link.l1 = DLG_TEXT_BASE[531];
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[532];
					link.l1 = DLG_TEXT_BASE[533];
					link.l1.go = "quests";
					link.l2 = DLG_TEXT_BASE[534];
					link.l2.go = "exit";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && pchar.model == "Sharle_6")
			{
    			dialog.text = DLG_TEXT_BASE[890];
				link.l1 = DLG_TEXT_BASE[891];
				link.l1.go = "exit";
				link.l8 = DLG_TEXT_BASE[892];
				link.l8.go = "Play_Game";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && pchar.model == "Sharle_6")
			{
    			dialog.text = DLG_TEXT_BASE[893];
				link.l1 = DLG_TEXT_BASE[894];
				link.l1.go = "exit"; 
				link.l8 = DLG_TEXT_BASE[895];
				link.l8.go = "Play_Game";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && pchar.model == "Sharle_6")
			{
    			dialog.text = DLG_TEXT_BASE[896];
				link.l1 = DLG_TEXT_BASE[897];
				link.l1.go = "exit"; 
				link.l8 = DLG_TEXT_BASE[898];
				link.l8.go = "Play_Game";
				break;
			}					
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = DLG_TEXT_BASE[535];
				link.l1 = DLG_TEXT_BASE[536];
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[21] + GetFullName(npchar) +
                              DLG_TEXT_BASE[22]+ GetCityName(NPChar.city) + DLG_TEXT_BASE[23] + NationKingsName(npchar)+
                              DLG_TEXT_BASE[24] + GetAddress_Form(NPChar) + ".";
				link.l1 = DLG_TEXT_BASE[25] + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = DLG_TEXT_BASE[26];
                        link.l1 = DLG_TEXT_BASE[27];
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = DLG_TEXT_BASE[28]+NationNamePeople(sti(aData.nation))+DLG_TEXT_BASE[29];
                        link.l1 = DLG_TEXT_BASE[30];
                        link.l1.go = "siege_task";
                        link.l2 = DLG_TEXT_BASE[31];
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                        //--> слухи
                        SiegeRumour(DLG_TEXT_BASE[32]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[33]+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = DLG_TEXT_BASE[34]+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[35]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[36]+(sti(aData.iSquadronPower)*1000)+DLG_TEXT_BASE[37];
                        link.l1 = DLG_TEXT_BASE[38] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[39];
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 100 && sti(pchar.questTemp.HorseQty) > 5)
						{
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = DLG_TEXT_BASE[40];
								link.l1 = DLG_TEXT_BASE[41];
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[42],
                                      DLG_TEXT_BASE[43] +GetAddress_Form(NPChar)+"?");
        				link.l1 = DLG_TEXT_BASE[44] + NationNameGenitive(sti(NPChar.nation));
        				link.l1.go = "work";
						
						// Warship Генер "Pirates on an uninhabited island" - сдаем пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + DLG_TEXT_BASE[537] + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + DLG_TEXT_BASE[538];
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = DLG_TEXT_BASE[45];
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = DLG_TEXT_BASE[539] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + DLG_TEXT_BASE[540] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[541];
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = DLG_TEXT_BASE[542] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[543];
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = DLG_TEXT_BASE[544] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[545];
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + DLG_TEXT_BASE[546] + pchar.GenQuest.ShipWreck.Name + DLG_TEXT_BASE[547] + pchar.GenQuest.ShipWreck.BadName + ". " +
										DLG_TEXT_BASE[548] + (30 - iDay) + DLG_TEXT_BASE[549];
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + DLG_TEXT_BASE[550] + 
										DLG_TEXT_BASE[551] + (30 - iDay) + DLG_TEXT_BASE[552];
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = DLG_TEXT_BASE[46];
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = DLG_TEXT_BASE[47];
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = DLG_TEXT_BASE[48];
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = DLG_TEXT_BASE[49];
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = DLG_TEXT_BASE[553]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Justice for sale" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + DLG_TEXT_BASE[554] + PChar.GenQuest.JusticeOnSale.ShipName + DLG_TEXT_BASE[555] + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + DLG_TEXT_BASE[556];
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = DLG_TEXT_BASE[557];
							link.l16.go = "Regata";
						}
        			//	link.l7 = DLG_TEXT_BASE[50] + NationNameGenitive(sti(NPChar.nation)) + ".";
        			//	link.l7.go = "Where_guber";
        				link.l8 = DLG_TEXT_BASE[51];
        			    link.l8.go = "Play_Game";
        				link.l10 = DLG_TEXT_BASE[52];
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = DLG_TEXT_BASE[558] + FindRussianMoneyString(qty) + ".";
			link.l1 = DLG_TEXT_BASE[559];
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = DLG_TEXT_BASE[560];
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = DLG_TEXT_BASE[561];
			link.l1 = DLG_TEXT_BASE[562];
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = DLG_TEXT_BASE[563]+ GetSexPhrase("monsieur","mademoiselle") +DLG_TEXT_BASE[564]+DLG_TEXT_BASE[565];
				link.l1 = DLG_TEXT_BASE[566];
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = DLG_TEXT_BASE[567]+DLG_TEXT_BASE[568];
				link.l2 = DLG_TEXT_BASE[569];
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = GetSexPhrase("Monsieur","Mademoiselle") +DLG_TEXT_BASE[570];
				link.l3 = DLG_TEXT_BASE[571];
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = DLG_TEXT_BASE[572] + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + DLG_TEXT_BASE[573];
				link.l1 = DLG_TEXT_BASE[574];
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = DLG_TEXT_BASE[575]+DLG_TEXT_BASE[576];
				link.l2 = DLG_TEXT_BASE[577];
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = DLG_TEXT_BASE[578];
				link.l3 = DLG_TEXT_BASE[579];
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = DLG_TEXT_BASE[580];
			link.l1 = DLG_TEXT_BASE[581];
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = DLG_TEXT_BASE[582];
			link.l1 = DLG_TEXT_BASE[583];
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = DLG_TEXT_BASE[584];
			link.l1 = DLG_TEXT_BASE[585];
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = DLG_TEXT_BASE[586];
			link.l1 = DLG_TEXT_BASE[587];
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = DLG_TEXT_BASE[588];
			link.l1 = DLG_TEXT_BASE[589];			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = DLG_TEXT_BASE[590];
			link.l1 = DLG_TEXT_BASE[591];
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = DLG_TEXT_BASE[592] +
				DLG_TEXT_BASE[593] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + DLG_TEXT_BASE[594] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[595];
			link.l1 = DLG_TEXT_BASE[596];
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = DLG_TEXT_BASE[597] +
				DLG_TEXT_BASE[598]+DLG_TEXT_BASE[599];
			link.l1 = DLG_TEXT_BASE[600];
			link.l1.go = "CapComission_Mayor5";
			link.l2 = DLG_TEXT_BASE[601];
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = DLG_TEXT_BASE[602]; 
			link.l1 = DLG_TEXT_BASE[603] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[604];
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = DLG_TEXT_BASE[605];
			link.l1 = DLG_TEXT_BASE[606];
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = DLG_TEXT_BASE[607];
			link.l1 = DLG_TEXT_BASE[608];
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = DLG_TEXT_BASE[609];
			link.l1 = DLG_TEXT_BASE[610];
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = DLG_TEXT_BASE[611]+DLG_TEXT_BASE[612]+DLG_TEXT_BASE[613] + GetFullName(pchar) + ".";
			link.l1 = DLG_TEXT_BASE[614];
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = DLG_TEXT_BASE[615];
			link.l1 = RandPhraseSimple(RandPhraseSimple("Au Nord","A l'Ouest"),RandPhraseSimple("A l'Est","Au Sud")) + " de " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + DLG_TEXT_BASE[616];
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = DLG_TEXT_BASE[617] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[618];
			link.l1 = DLG_TEXT_BASE[619];
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = DLG_TEXT_BASE[620]+ GetSexPhrase("monsieur","mademoiselle") +" " + GetFullName(pchar) + DLG_TEXT_BASE[621] + 
				DLG_TEXT_BASE[622]+DLG_TEXT_BASE[623];
			link.l1 = DLG_TEXT_BASE[624];	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[625],"Capitaine " + GetFullName(pchar) + DLG_TEXT_BASE[626]);
				link.l1 = DLG_TEXT_BASE[627];
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[628] + pchar.GenQuest.ShipWreck.Name + DLG_TEXT_BASE[629];
				link.l1 = DLG_TEXT_BASE[630];
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
		break;
		
		case "ShipWreck2":
			dialog.text = DLG_TEXT_BASE[631];
			link.l1 = DLG_TEXT_BASE[632];
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = DLG_TEXT_BASE[53]+
				DLG_TEXT_BASE[54];
			link.l1 = DLG_TEXT_BASE[55];
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = DLG_TEXT_BASE[56];
			link.l1 = DLG_TEXT_BASE[57];
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = DLG_TEXT_BASE[58];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "TakeRing_5";
			link.l2 = DLG_TEXT_BASE[62] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[63];
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo(DLG_TEXT_BASE[66] + sld.startLocation + DLG_TEXT_BASE[67] + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[77] + GetAddress_Form(NPChar) + ".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = DLG_TEXT_BASE[78];
                    link.l1 = DLG_TEXT_BASE[79];
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = DLG_TEXT_BASE[80]+NationNamePeople(sti(aData.nation))+DLG_TEXT_BASE[81];
                    link.l1 = DLG_TEXT_BASE[82];
                    link.l1.go = "siege_task";
                    link.l2 = DLG_TEXT_BASE[83];
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                    //--> слухи
                    SiegeRumour(DLG_TEXT_BASE[84]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[85]+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = DLG_TEXT_BASE[86]+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[87]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[88]+(sti(aData.iSquadronPower)*1000)+DLG_TEXT_BASE[89];
                    link.l1 = DLG_TEXT_BASE[90] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[91];
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = DLG_TEXT_BASE[92];
        			link.l1 = DLG_TEXT_BASE[93] + NationNameGenitive(sti(NPChar.nation));
        			link.l1.go = "work";
					
					// Warship Генер "Пираты на необитайке" - сдаем пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + DLG_TEXT_BASE[633] + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + DLG_TEXT_BASE[634];
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = DLG_TEXT_BASE[94];
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = DLG_TEXT_BASE[635] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + DLG_TEXT_BASE[636] + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[637];
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = DLG_TEXT_BASE[638] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[639];
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = DLG_TEXT_BASE[640] + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + DLG_TEXT_BASE[641];
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + DLG_TEXT_BASE[642] + pchar.GenQuest.ShipWreck.Name + DLG_TEXT_BASE[643] + pchar.GenQuest.ShipWreck.BadName + ". " +
									DLG_TEXT_BASE[644] + (30 - iDay) + DLG_TEXT_BASE[645];
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + DLG_TEXT_BASE[646] + pchar.GenQuest.ShipWreck.ShipTypeName + DLG_TEXT_BASE[647] + 
									DLG_TEXT_BASE[648] + (30 - iDay) + DLG_TEXT_BASE[649];
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = DLG_TEXT_BASE[650]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = DLG_TEXT_BASE[651] + PChar.GenQuest.JusticeOnSale.ShipName + DLG_TEXT_BASE[652] + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = DLG_TEXT_BASE[95];
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = DLG_TEXT_BASE[653];
						link.l4.go = "Regata";
					}
        			link.l5 = DLG_TEXT_BASE[97];
        			link.l5.go = "Play_Game";
        			link.l10 = DLG_TEXT_BASE[98] + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "Card_Game";
   			link.l2 = DLG_TEXT_BASE[101];
			link.l2.go = "Dice_Game";
			link.l10 = DLG_TEXT_BASE[102];
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				if (pchar.model == "Sharle_6") dialog.text = DLG_TEXT_BASE[899]; // Jason НСО
                else dialog.text = DLG_TEXT_BASE[103];
    			link.l1 = DLG_TEXT_BASE[104];
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = DLG_TEXT_BASE[105];
	    			link.l1 = DLG_TEXT_BASE[106];
	    			link.l1.go = "Cards_begin";
	    			link.l2 = DLG_TEXT_BASE[107];
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[108];
	    			link.l1 = DLG_TEXT_BASE[109];
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = GetConvertStr("CARDS_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[110];
			link.l1.go = "Cards_begin";
			link.l3 = DLG_TEXT_BASE[111];
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "Cards_Node_100";
			link.l2 = DLG_TEXT_BASE[114];
			link.l2.go = "Cards_Node_500";
			link.l3 = DLG_TEXT_BASE[115];
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[116];
                link.l1 = DLG_TEXT_BASE[117];
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[118] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[119];
                link.l1 = DLG_TEXT_BASE[120];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[121];
                link.l1 = DLG_TEXT_BASE[122];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[125];
                link.l1 = DLG_TEXT_BASE[126];
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[127];
                link.l1 = DLG_TEXT_BASE[128];
			    link.l1.go = "Cards_Node_100";
				link.l2 = DLG_TEXT_BASE[129];
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[130] + GetAddress_Form(npchar) + DLG_TEXT_BASE[131];
                link.l1 = DLG_TEXT_BASE[132];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[133];
                link.l1 = DLG_TEXT_BASE[134];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[135];
			link.l1 = DLG_TEXT_BASE[136];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                if (pchar.model == "Sharle_6") dialog.text = DLG_TEXT_BASE[899]; // Jason НСО
                else dialog.text = DLG_TEXT_BASE[137];
    			link.l1 = DLG_TEXT_BASE[138];
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = DLG_TEXT_BASE[139];
	    			link.l1 = DLG_TEXT_BASE[140];
	    			link.l1.go = "Dice_begin";
	    			link.l2 = DLG_TEXT_BASE[141];
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[142];
	    			link.l1 = DLG_TEXT_BASE[143];
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = GetConvertStr("DICE_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "Dice_begin";
			link.l3 = DLG_TEXT_BASE[145];
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = DLG_TEXT_BASE[146];
			link.l1 = DLG_TEXT_BASE[147];
			link.l1.go = "Dice_Node_100";
			link.l2 = DLG_TEXT_BASE[148];
			link.l2.go = "Dice_Node_500";
			link.l3 = DLG_TEXT_BASE[149];
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[150];
                link.l1 = DLG_TEXT_BASE[151];
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[152] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[153];
                link.l1 = DLG_TEXT_BASE[154];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[155];
                link.l1 = DLG_TEXT_BASE[156];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[157];
			link.l1 = DLG_TEXT_BASE[158];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[159];
                link.l1 = DLG_TEXT_BASE[160];
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[161];
                link.l1 = DLG_TEXT_BASE[162];
			    link.l1.go = "Dice_Node_100";
				link.l2 = DLG_TEXT_BASE[163];
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[164] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[165];
                link.l1 = DLG_TEXT_BASE[166];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[167];
                link.l1 = DLG_TEXT_BASE[168];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[169];
			link.l1 = DLG_TEXT_BASE[170];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.snd = "Voice\CHMA\CHMA004";
			dialog.text = DLG_TEXT_BASE[171];
			link.l1 = DLG_TEXT_BASE[172];
			link.l1.go = "exit";
		break;

		case "Where_guber":
            offref = characterFromID(NationShortName(sti(NPChar.nation))+"_guber");

            if (NPChar.location == offref.location)
            {
                dialog.text = DLG_TEXT_BASE[173] + RandPhraseSimple(DLG_TEXT_BASE[174], DLG_TEXT_BASE[175]) + DLG_TEXT_BASE[176]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                              DLG_TEXT_BASE[177];
    			link.l1 = DLG_TEXT_BASE[178];
    			link.l1.go = "exit";
            }
            else
            {
                if (bBettaTestMode || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) > rand(5) || CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))))// когда патен всегда
                {
                    cn = FindLocation(offref.location);
                	if(cn < 0)
                    {
                        attrLoc = "error";
                        dialog.text = DLG_TEXT_BASE[179] + RandPhraseSimple(DLG_TEXT_BASE[180], DLG_TEXT_BASE[181]) + DLG_TEXT_BASE[182]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                      DLG_TEXT_BASE[183];
                    }
                	else
                	{
                	    attrLoc = locations[cn].islandId;
                	    if (attrLoc == "Mein")
                	    {
        			    	dialog.text = DLG_TEXT_BASE[184] + RandPhraseSimple(DLG_TEXT_BASE[185], DLG_TEXT_BASE[186]) + DLG_TEXT_BASE[187]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(DLG_TEXT_BASE[188],
                                            DLG_TEXT_BASE[189],
                                            DLG_TEXT_BASE[190]) + DLG_TEXT_BASE[191] + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
						else
						{
						    dialog.text = DLG_TEXT_BASE[192] + RandPhraseSimple(DLG_TEXT_BASE[193], DLG_TEXT_BASE[194]) + DLG_TEXT_BASE[195]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(DLG_TEXT_BASE[196],
                                            DLG_TEXT_BASE[197],
                                            DLG_TEXT_BASE[198]) + GetConvertStr(attrLoc, "LocLables.txt") + DLG_TEXT_BASE[199] + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
                    }
        			link.l1 = DLG_TEXT_BASE[200];
        			link.l1.go = "exit";
    			}
    			else
    			{
                    dialog.text = DLG_TEXT_BASE[201];
        			link.l1 = DLG_TEXT_BASE[202];
        			link.l1.go = "exit";
    			}
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = DLG_TEXT_BASE[203];
        	link.l1 = DLG_TEXT_BASE[204];
        	link.l1.go = "exit";

			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[212] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen") + DLG_TEXT_BASE[213], 
						DLG_TEXT_BASE[214] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Dat") + DLG_TEXT_BASE[215]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[216], DLG_TEXT_BASE[217]+ GetAddress_Form(NPChar) + ".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[218] + GetFullName(arName) + DLG_TEXT_BASE[219], 
								DLG_TEXT_BASE[220] + GetFullName(arName) + DLG_TEXT_BASE[221], 
								DLG_TEXT_BASE[222] + GetFullName(arName) + DLG_TEXT_BASE[223]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[224] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[225]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[226] + GetFullName(arName) + DLG_TEXT_BASE[227] + GetAddress_Form(NPChar) + ".",
								DLG_TEXT_BASE[228] + GetFullName(arName) + DLG_TEXT_BASE[229]);
							link.l1 = DLG_TEXT_BASE[230] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[231] + GetFullName(arName) + DLG_TEXT_BASE[232], DLG_TEXT_BASE[233] + GetFullName(arName) + DLG_TEXT_BASE[234]);
							link.l1 = DLG_TEXT_BASE[235] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[236];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[237] + GetFullName(arName) + DLG_TEXT_BASE[238], DLG_TEXT_BASE[239] + GetFullName(arName) + DLG_TEXT_BASE[240]);
							link.l1 = DLG_TEXT_BASE[241] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 80);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[654], 
								DLG_TEXT_BASE[655], 
								DLG_TEXT_BASE[656]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[657] + GetAddress_FormToNPC(NPChar) + ".", DLG_TEXT_BASE[658]+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[659] + GetAddress_Form(NPChar) + ".",
								DLG_TEXT_BASE[660]);
							link.l1 = DLG_TEXT_BASE[661] + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[662], DLG_TEXT_BASE[663]);
							link.l1 = DLG_TEXT_BASE[664] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[665];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[666], DLG_TEXT_BASE[667]);
							link.l1 = "Oui, " + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[668];
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 100);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 50);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[669], 
								DLG_TEXT_BASE[670], 
								DLG_TEXT_BASE[671]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[672] + GetAddress_FormToNPC(NPChar) + ".", DLG_TEXT_BASE[673]+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[674] + GetAddress_Form(NPChar) + ".",
								DLG_TEXT_BASE[675]);
							link.l1 = DLG_TEXT_BASE[676] + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[677], DLG_TEXT_BASE[678]);
							link.l1 = DLG_TEXT_BASE[679] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[680];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[681], DLG_TEXT_BASE[682]);
							link.l1 = "Oui, " + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[683];
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 120);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 50);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[279], 
								DLG_TEXT_BASE[280], 
								DLG_TEXT_BASE[281]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[282] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[283]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[284],
								DLG_TEXT_BASE[285]);
							link.l1 = DLG_TEXT_BASE[286] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[684], DLG_TEXT_BASE[685]);
							link.l1 = DLG_TEXT_BASE[686] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[687];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[688], DLG_TEXT_BASE[689]);
							link.l1 = "Oui, " + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[690];
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 150);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 50);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[691], 
								DLG_TEXT_BASE[692], 
								DLG_TEXT_BASE[693]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[694] + GetAddress_FormToNPC(NPChar) + ".", DLG_TEXT_BASE[695]+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[696] + GetAddress_Form(NPChar) + ".",
								DLG_TEXT_BASE[697]);
							link.l1 = DLG_TEXT_BASE[698] + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[699], DLG_TEXT_BASE[700]);
							link.l1 = DLG_TEXT_BASE[701] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[702];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[703], DLG_TEXT_BASE[704]);
							link.l1 = "Oui, " + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[705];
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 150);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 100);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[267], 
								DLG_TEXT_BASE[268], 
								DLG_TEXT_BASE[269]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[270] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[271]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";	
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[272],
								DLG_TEXT_BASE[273]);
							link.l1 = DLG_TEXT_BASE[274] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[706], DLG_TEXT_BASE[707]);
							link.l1 = DLG_TEXT_BASE[708] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[709];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[710], DLG_TEXT_BASE[711]);
							link.l1 = "Oui, " + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[712];
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 100);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[713], 
								DLG_TEXT_BASE[714], 
								DLG_TEXT_BASE[715]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[716] + GetAddress_FormToNPC(NPChar) + ".", DLG_TEXT_BASE[717]+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[718] + GetAddress_Form(NPChar) + ".",
								DLG_TEXT_BASE[719]);
							link.l1 = DLG_TEXT_BASE[720] + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[721], DLG_TEXT_BASE[722]);
							link.l1 = DLG_TEXT_BASE[723] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[724]+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+DLG_TEXT_BASE[725];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[726]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[727], DLG_TEXT_BASE[728]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[729]);
							link.l1 = DLG_TEXT_BASE[730] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[731];
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 100);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple(DLG_TEXT_BASE[256],
									DLG_TEXT_BASE[257]);
								link.l1 = DLG_TEXT_BASE[258] + GetAddress_Form(NPChar) + ".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase(DLG_TEXT_BASE[259], 
									DLG_TEXT_BASE[260], 
									DLG_TEXT_BASE[261]);
								link.l1 = RandPhraseSimple(DLG_TEXT_BASE[262] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[263]+ GetAddress_Form(NPChar) + ".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[264], DLG_TEXT_BASE[265]);
							link.l1 = DLG_TEXT_BASE[266];
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = DLG_TEXT_BASE[303] + GetFullName(&Characters[i])
					+ DLG_TEXT_BASE[304];
				link.l1 = DLG_TEXT_BASE[305];
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[306], 
						DLG_TEXT_BASE[307], 
						DLG_TEXT_BASE[308]);
					link.l1 = DLG_TEXT_BASE[309] + GetAddress_Form(NPChar) + ".";
					link.l1.go = "exit";
				}
				else 
				{
					i = dRand(7);
					switch (i)
					{					
						//========== квест уничтожения банды ============ //Jason: оставляем, как классику
						case 0:
							pchar.GenQuest.DestroyGang.Terms = dRand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((dRand(6)+4)*250)+(sti(pchar.rank)*300+2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = DLG_TEXT_BASE[310] + XI_ConvertString("Colony"+npchar.city+"Gen") + DLG_TEXT_BASE[311] + GetFullName(arName) + DLG_TEXT_BASE[312];
							link.l1 = DLG_TEXT_BASE[313];
							link.l1.go = "DestroyGang";
						break;
						//========== пробраться во вражеский город ============//Jason: оставляем, как годный
						case 1:
							pchar.GenQuest.Intelligence.Terms = dRand(10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((dRand(4) + 6) * 1000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = GetSpyColony(npchar); //враждебная колония
                            sTemp = DLG_TEXT_BASE[318] + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = DLG_TEXT_BASE[319] + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc") + sTemp + DLG_TEXT_BASE[320];
							link.l1 = DLG_TEXT_BASE[321] + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + DLG_TEXT_BASE[322];
							link.l1.go = "Intelligence";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = DLG_TEXT_BASE[732];
							link.l1 = DLG_TEXT_BASE[733];
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = DLG_TEXT_BASE[734];
							link.l1 = DLG_TEXT_BASE[735];
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = DLG_TEXT_BASE[736];
							link.l1 = DLG_TEXT_BASE[737];
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = DLG_TEXT_BASE[738];
							link.l1 = DLG_TEXT_BASE[739];
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = DLG_TEXT_BASE[740];
							link.l1 = DLG_TEXT_BASE[741];
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = DLG_TEXT_BASE[742];
							link.l1 = DLG_TEXT_BASE[743];
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[328], DLG_TEXT_BASE[329], DLG_TEXT_BASE[330]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[331], DLG_TEXT_BASE[332]+ GetAddress_Form(NPChar) + ". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = DLG_TEXT_BASE[335];

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = DLG_TEXT_BASE[336];
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  DLG_TEXT_BASE[337] + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + DLG_TEXT_BASE[338] + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + DLG_TEXT_BASE[339] + FindRussianMoneyString(qty) + DLG_TEXT_BASE[340];
                    /*if (CheckAttribute(NPChar, "from_sea"))
                    {
                        link.l2 = DLG_TEXT_BASE[341];
			            link.l2.go = "sell_prisoner_DeathExec";
			        } */
                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + DLG_TEXT_BASE[342] + FindRussianMoneyString(qty) + ".";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = DLG_TEXT_BASE[343] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = DLG_TEXT_BASE[344];
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = DLG_TEXT_BASE[351];
			link.l1 = DLG_TEXT_BASE[352];
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // все, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = DLG_TEXT_BASE[744];
                Link.l1 = DLG_TEXT_BASE[745];
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = DLG_TEXT_BASE[353];
                Link.l1 = DLG_TEXT_BASE[354];
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернем диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = DLG_TEXT_BASE[355];
                Link.l2 = DLG_TEXT_BASE[356];
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = DLG_TEXT_BASE[357];
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = DLG_TEXT_BASE[358];
	    				}
	    				else
	    				{
	    					Link.l1 = DLG_TEXT_BASE[359];
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = DLG_TEXT_BASE[360];
				}
				else
				{
	            	Link.l2 = DLG_TEXT_BASE[361];
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = DLG_TEXT_BASE[362] + NationNameGenitive(sti(NPChar.nation)) + DLG_TEXT_BASE[363];
	                Link.l1 = DLG_TEXT_BASE[364];
	                Link.l1.go = "City_patent";
	                Link.l2 = DLG_TEXT_BASE[365] + NationNameGenitive(sti(PChar.nation)) + DLG_TEXT_BASE[366] + NationKingsCrown(PChar) + "!";
	                Link.l2.go = "City_nation";
	                Link.l3 = DLG_TEXT_BASE[367];
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = DLG_TEXT_BASE[746];
			Link.l1 = DLG_TEXT_BASE[747];
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info(DLG_TEXT_BASE[368]);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = DLG_TEXT_BASE[369];
			Link.l1 = DLG_TEXT_BASE[370];
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = DLG_TEXT_BASE[371];
            Link.l1 = DLG_TEXT_BASE[372];
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернем диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = DLG_TEXT_BASE[373];
            Link.l1 = DLG_TEXT_BASE[374];
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 200);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 200);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = DLG_TEXT_BASE[375];
            Link.l1 = DLG_TEXT_BASE[376];
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = DLG_TEXT_BASE[377];
			Link.l1 = DLG_TEXT_BASE[378];
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не дает, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернем диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = DLG_TEXT_BASE[379];
			Link.l1 = DLG_TEXT_BASE[380];
			Link.l1.go = "Strike";
			if (!CheckAttribute(NPChar, "NotHaveFort"))
			{
			    Link.l2 = DLG_TEXT_BASE[381];
			    Link.l2.go = "Death_Execution_1";
            }       
            Link.l3 = DLG_TEXT_BASE[382];
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = DLG_TEXT_BASE[383];
            link.l1 = DLG_TEXT_BASE[384] + iTotalTemp*6000 + DLG_TEXT_BASE[385];
			link.l1.go = "arestFree_2";
			link.l2 = DLG_TEXT_BASE[386];
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= drand(0) && iTotalTemp < 21)
            {
    			dialog.text = DLG_TEXT_BASE[387];
    		    link.l1 = DLG_TEXT_BASE[388];
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = DLG_TEXT_BASE[389]+ GetSexPhrase("le","la") +" au fort !";
    		    link.l1 = DLG_TEXT_BASE[390];
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = DLG_TEXT_BASE[391]+ GetSexPhrase("le","la") +" !";
		    link.l1 = DLG_TEXT_BASE[393];
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = DLG_TEXT_BASE[748];
			link.l1 = DLG_TEXT_BASE[749];
		    link.l1.go = "fight";
		break;     
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = DLG_TEXT_BASE[394] + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + DLG_TEXT_BASE[395] + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + ".";
			link.l1 = DLG_TEXT_BASE[396];
		    link.l1.go = "DestroyGang_agree";
			link.l2 = DLG_TEXT_BASE[397];
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = DLG_TEXT_BASE[398];
				link.l1 = DLG_TEXT_BASE[399];
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[400];
				link.l1 = DLG_TEXT_BASE[401] + GetAddress_Form(NPChar) + ".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			pchar.GenQuest.TakePostcureer.Nation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) pchar.GenQuest.TakePostcureer.Nation = GetEnemyNationToMainCharacter();
			pchar.GenQuest.TakePostcureer.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((dRand(5)+drand(6)+4)*1000)+(sti(pchar.rank)*500);
			dialog.text = DLG_TEXT_BASE[750]+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+DLG_TEXT_BASE[751]+pchar.GenQuest.TakePostcureer.ShipName+DLG_TEXT_BASE[752]+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+DLG_TEXT_BASE[753]+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = DLG_TEXT_BASE[754];
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = DLG_TEXT_BASE[755];
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = DLG_TEXT_BASE[756]+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+DLG_TEXT_BASE[757];
			link.l1 = DLG_TEXT_BASE[758] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			pchar.GenQuest.TakeArsenalship.Nation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) pchar.GenQuest.TakeArsenalship.Nation = GetEnemyNationToMainCharacter();
			pchar.GenQuest.TakeArsenalship.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType();
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectCureerShipType();
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка			
			pchar.GenQuest.TakeArsenalship.Money = ((dRand(5)+drand(6)+4)*900)+(sti(pchar.rank)*500);
			dialog.text = DLG_TEXT_BASE[759]+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+DLG_TEXT_BASE[760]+pchar.GenQuest.TakeArsenalship.ShipName+DLG_TEXT_BASE[761]+DLG_TEXT_BASE[762]+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+DLG_TEXT_BASE[763]+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+DLG_TEXT_BASE[764];
			link.l1 = DLG_TEXT_BASE[765];
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = DLG_TEXT_BASE[766];
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = DLG_TEXT_BASE[767]+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+DLG_TEXT_BASE[768];
			link.l1 = DLG_TEXT_BASE[769] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((dRand(5)+drand(6)+4)*1200)+(sti(pchar.rank)*500);
			dialog.text = DLG_TEXT_BASE[770]+pchar.GenQuest.TakePirateship.Name+DLG_TEXT_BASE[771];
			link.l1 = DLG_TEXT_BASE[772];
		    link.l1.go = "TakePirateship_agree";
			link.l2 = DLG_TEXT_BASE[773];
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = DLG_TEXT_BASE[774]+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+DLG_TEXT_BASE[775]+pchar.GenQuest.TakePirateship.ShipName+DLG_TEXT_BASE[776]+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+DLG_TEXT_BASE[777]+DLG_TEXT_BASE[778]+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+DLG_TEXT_BASE[779] +XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+ DLG_TEXT_BASE[780];
			link.l1 = DLG_TEXT_BASE[781]+GetAddress_FormToNPC(NPChar) +DLG_TEXT_BASE[782];
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Nation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) pchar.GenQuest.TakePassenger.Nation = GetEnemyNationToMainCharacter();
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((dRand(5)+drand(6)+4)*1100)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = DLG_TEXT_BASE[783]+pchar.GenQuest.TakePassenger.Name+". "+sText+DLG_TEXT_BASE[784];
			link.l1 = DLG_TEXT_BASE[785] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[786];
		    link.l1.go = "TakePassenger_agree";
			link.l2 = DLG_TEXT_BASE[787];
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = DLG_TEXT_BASE[788]+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+DLG_TEXT_BASE[789]+pchar.GenQuest.TakePassenger.ShipName+DLG_TEXT_BASE[790]+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+DLG_TEXT_BASE[791]+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+DLG_TEXT_BASE[792]+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+DLG_TEXT_BASE[793]+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+DLG_TEXT_BASE[794];
			link.l1 = DLG_TEXT_BASE[795] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[796];
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCureerShipType();
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCureerShipType();
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((dRand(5)+drand(6)+4)*700)+(sti(pchar.rank)*300);
			dialog.text = DLG_TEXT_BASE[797]+DLG_TEXT_BASE[798]+DLG_TEXT_BASE[799];
			link.l1 = DLG_TEXT_BASE[800] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[801];
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = DLG_TEXT_BASE[802];
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = DLG_TEXT_BASE[803]+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+DLG_TEXT_BASE[804];
			link.l1 = DLG_TEXT_BASE[805] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((dRand(5)+drand(6)+4)*1300)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = DLG_TEXT_BASE[806]+sText+DLG_TEXT_BASE[807]+DLG_TEXT_BASE[808];
			link.l1 = DLG_TEXT_BASE[809] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[810];
		    link.l1.go = "FindFugitive_agree";
			link.l2 = DLG_TEXT_BASE[811];
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = DLG_TEXT_BASE[812]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[813]+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = DLG_TEXT_BASE[814] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[815];
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = DLG_TEXT_BASE[816] + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + DLG_TEXT_BASE[817];
			link.l1 = DLG_TEXT_BASE[818];
		    link.l1.go = "Intelligence_agree";
			link.l2 = DLG_TEXT_BASE[819];
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = DLG_TEXT_BASE[414];
				link.l1 = DLG_TEXT_BASE[415];
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = DLG_TEXT_BASE[416] + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + DLG_TEXT_BASE[417] + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + 
					DLG_TEXT_BASE[418] + GetFullName(&characters[GetCharacterIndex(sTemp)]) + DLG_TEXT_BASE[419] + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + DLG_TEXT_BASE[420];
				link.l1 = DLG_TEXT_BASE[421] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[422];
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / (rand(2)+2);
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[423] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + DLG_TEXT_BASE[424], 
				DLG_TEXT_BASE[425] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + DLG_TEXT_BASE[426]);
			link.l1 = DLG_TEXT_BASE[427] + GetAddress_Form(NPChar) + ".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple(DLG_TEXT_BASE[428] + GetFullName(npchar) + DLG_TEXT_BASE[429] + GetMainCharacterNameGen() + ".", 
				DLG_TEXT_BASE[430] + GetFullName(npchar) + DLG_TEXT_BASE[431] + GetMainCharacterNameDat() + DLG_TEXT_BASE[432]), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = DLG_TEXT_BASE[450];
			link.l1 = DLG_TEXT_BASE[451] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[452];
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[453], 
				DLG_TEXT_BASE[454]);
			link.l1 = DLG_TEXT_BASE[455] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[456];
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[457] + GetFullName(npchar) + DLG_TEXT_BASE[458] + GetMainCharacterNameDat() + DLG_TEXT_BASE[459], 
				DLG_TEXT_BASE[460] + GetFullName(npchar) + DLG_TEXT_BASE[461] + GetFullName(pchar) + DLG_TEXT_BASE[462], 
				DLG_TEXT_BASE[463] + GetFullName(npchar) + DLG_TEXT_BASE[464] + GetFullName(pchar) + DLG_TEXT_BASE[465]), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[466], 
				DLG_TEXT_BASE[467]);
			link.l1 = DLG_TEXT_BASE[468] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[469];
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[470] + GetFullName(npchar) + DLG_TEXT_BASE[471] + GetMainCharacterNameDat() + DLG_TEXT_BASE[472], 
				DLG_TEXT_BASE[473] + GetFullName(npchar) + DLG_TEXT_BASE[474] + GetFullName(pchar) + DLG_TEXT_BASE[475], 
				DLG_TEXT_BASE[476] + GetFullName(npchar) + DLG_TEXT_BASE[477] + GetFullName(pchar) + DLG_TEXT_BASE[478]), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[479] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + DLG_TEXT_BASE[480], 
				DLG_TEXT_BASE[481] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + DLG_TEXT_BASE[482]);
			link.l1 = DLG_TEXT_BASE[483] + GetAddress_Form(NPChar) + ", " + RandPhraseSimple(DLG_TEXT_BASE[484], DLG_TEXT_BASE[485]);
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[486] + GetFullName(npchar) + DLG_TEXT_BASE[487] + GetMainCharacterNameGen() + ".", 
				DLG_TEXT_BASE[488] + GetFullName(npchar) + DLG_TEXT_BASE[489] + GetMainCharacterNameGen() + DLG_TEXT_BASE[490], 
				DLG_TEXT_BASE[491] + GetFullName(npchar) + DLG_TEXT_BASE[492] + GetFullName(pchar) + DLG_TEXT_BASE[493]), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[494], DLG_TEXT_BASE[495]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[496], DLG_TEXT_BASE[497]);
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 80);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = DLG_TEXT_BASE[498];
			link.l1 = DLG_TEXT_BASE[499];
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = DLG_TEXT_BASE[820];
			link.l1 = DLG_TEXT_BASE[821];
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = DLG_TEXT_BASE[822];
			link.l1 = DLG_TEXT_BASE[823];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
		break;
		
		case "Sharlie_2":
			dialog.text = DLG_TEXT_BASE[824];
			link.l1 = DLG_TEXT_BASE[825];
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			Log_Info("Nouveaux objets obtenus !");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
		break;
		//<-- Бремя гасконца
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = DLG_TEXT_BASE[827];
			link.l1 = DLG_TEXT_BASE[828];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_BASE[829];
			link.l1 = DLG_TEXT_BASE[830];
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = DLG_TEXT_BASE[831]+DLG_TEXT_BASE[832];
			link.l1 = DLG_TEXT_BASE[833];
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = DLG_TEXT_BASE[834];
			link.l1 = DLG_TEXT_BASE[835];
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = DLG_TEXT_BASE[836];
			link.l1 = DLG_TEXT_BASE[837];
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = DLG_TEXT_BASE[838];
			link.l1 = DLG_TEXT_BASE[839];
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = DLG_TEXT_BASE[840];
			link.l1 = DLG_TEXT_BASE[841];
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = DLG_TEXT_BASE[842];
			link.l1 = DLG_TEXT_BASE[843];
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = DLG_TEXT_BASE[844];
			link.l1 = DLG_TEXT_BASE[845];
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Оh " + GetAddress_Form(NPChar) + DLG_TEXT_BASE[846];
			link.l1 = DLG_TEXT_BASE[847];
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = DLG_TEXT_BASE[848];
			link.l1 = DLG_TEXT_BASE[849];
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * dRand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = DLG_TEXT_BASE[850] + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + DLG_TEXT_BASE[851];
			link.l1 = DLG_TEXT_BASE[852];
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = DLG_TEXT_BASE[853];
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = DLG_TEXT_BASE[854];
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + dRand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			dialog.text = DLG_TEXT_BASE[855];
			link.l1 = DLG_TEXT_BASE[856];
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = DLG_TEXT_BASE[857];
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = DLG_TEXT_BASE[858];
				link.l1.go = "Regata_2";
			}
			link.l2 = DLG_TEXT_BASE[859];
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = DLG_TEXT_BASE[860]+DLG_TEXT_BASE[861];
			link.l1 = DLG_TEXT_BASE[862];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = DLG_TEXT_BASE[863];
			link.l1 = DLG_TEXT_BASE[864];
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = DLG_TEXT_BASE[865] + GetFullName(pchar) + DLG_TEXT_BASE[866];
			link.l1 = DLG_TEXT_BASE[867];
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = DLG_TEXT_BASE[868];
			link.l1 = DLG_TEXT_BASE[869];
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			if (sti(pchar.rank) < 11) iGift = 0;
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 25) iGift = 1;
			if (sti(pchar.rank) >= 25) iGift = 2;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_27"; //саксенфедер
					sItem2 = "cirass7"; //бригант
					sItem3 = "bussol";
					sAdd = DLG_TEXT_BASE[870];
				break;
				
				case 1:
					sItem1 = "blade_20"; //мадонна
					sItem2 = "grape_mushket"; //склопетта
					sItem3 = "bussol";
					sAdd = DLG_TEXT_BASE[871];
				break;
				
				case 2:
					sItem1 = "blade_26"; //асоледа
					sItem2 = "cirass4"; //миланский панцирь
					sItem3 = "bussol";
					sAdd = DLG_TEXT_BASE[872];
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = DLG_TEXT_BASE[873]+sAdd+DLG_TEXT_BASE[874];
			link.l1 = DLG_TEXT_BASE[875];
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = DLG_TEXT_BASE[876];
			link.l1 = DLG_TEXT_BASE[877];
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[dRand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[dRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iShipType;
	if(sti(pchar.rank) >= 14)
	{
		iShipType = SHIP_CORVETTE + rand(makeint(SHIP_POLACRE - SHIP_CORVETTE));
	}
	if(sti(pchar.rank) >= 6 && sti(pchar.rank) < 14)
	{
		iShipType = SHIP_BRIGANTINE + rand(makeint(SHIP_SCHOONER_W - SHIP_BRIGANTINE));
	}
	if(sti(pchar.rank) < 6)
	{
		iShipType = SHIP_CAREERLUGGER + rand(makeint(SHIP_SLOOP - SHIP_CAREERLUGGER));
	}
	return iShipType;
}

int SelectArsenalShipType()
{
	int iShipType;
	if(sti(pchar.rank) >= 18)
	{
		iShipType = SHIP_GALEON_H;
	}
	if(sti(pchar.rank) >= 14 && sti(pchar.rank) < 18)
	{
		iShipType = SHIP_GALEON_L;
	}
	if(sti(pchar.rank) >= 8 && sti(pchar.rank) < 14)
	{
		iShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
	}
	if(sti(pchar.rank) >= 4 && sti(pchar.rank) < 8)
	{
		iShipType = SHIP_SCHOONER + rand(makeint(SHIP_FLEUT - SHIP_SCHOONER));
	}
	if(sti(pchar.rank) < 4)
	{
		iShipType = SHIP_BARQUE;
	}
	return iShipType;
}

string SelectPassText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = DLG_TEXT_BASE[878]; break;
		case 1: sText = DLG_TEXT_BASE[879]; break;
		case 2: sText = DLG_TEXT_BASE[880]; break;
		case 3: sText = DLG_TEXT_BASE[881]; break;
		case 4: sText = DLG_TEXT_BASE[882]; break;
		case 5: sText = DLG_TEXT_BASE[883]; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = DLG_TEXT_BASE[884]; break;
		case 1: sText = DLG_TEXT_BASE[885]; break;
		case 2: sText = DLG_TEXT_BASE[886]; break;
		case 3: sText = DLG_TEXT_BASE[887]; break;
		case 4: sText = DLG_TEXT_BASE[888]; break;
		case 5: sText = DLG_TEXT_BASE[889]; break;
	}
	return sText;
}