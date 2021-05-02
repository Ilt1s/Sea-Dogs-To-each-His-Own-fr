#include "SD\TEXT\DIALOGS\Ransack_captain_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = DLG_TEXT_BASE[59];
			link.l1 = DLG_TEXT_BASE[60]+pchar.questTemp.FalseTrace.CapName+DLG_TEXT_BASE[61];
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "See now, don Juan, treason is bad...";
			link.l1.go = "FMQG";
			break;	
		}
				if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + DLG_TEXT_BASE[0] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[1] + NationNameNominative(sti(NPChar.nation)) + DLG_TEXT_BASE[2];
				link.l1 = DLG_TEXT_BASE[62];
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = DLG_TEXT_BASE[3];
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear() + DLG_TEXT_BASE[4] + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + DLG_TEXT_BASE[5];
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = DLG_TEXT_BASE[63];
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = DLG_TEXT_BASE[6] + GetConvertStr(attrLoc +" Town", "LocLables.txt") + DLG_TEXT_BASE[7];
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = DLG_TEXT_BASE[64];
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = DLG_TEXT_BASE[10];
			link.l4.go = "Slave_1";
			link.l5 = DLG_TEXT_BASE[65];
			link.l5.go = "PunishmentAction";
			link.l99 = DLG_TEXT_BASE[12];
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[66],
							DLG_TEXT_BASE[67]);
						link.l1 = DLG_TEXT_BASE[68];	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = DLG_TEXT_BASE[69];
						link.l1 = DLG_TEXT_BASE[70];
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = DLG_TEXT_BASE[71];
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = DLG_TEXT_BASE[8] + GetFullName(NPChar) + DLG_TEXT_BASE[9];
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase(DLG_TEXT_BASE[72],
							DLG_TEXT_BASE[73],DLG_TEXT_BASE[74]);
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = DLG_TEXT_BASE[75];
						link.l1 = DLG_TEXT_BASE[76];
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple(DLG_TEXT_BASE[77],
							RandPhraseSimple(DLG_TEXT_BASE[78],DLG_TEXT_BASE[79]));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = DLG_TEXT_BASE[80];
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = DLG_TEXT_BASE[81];
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase(DLG_TEXT_BASE[82],
						DLG_TEXT_BASE[83],
						DLG_TEXT_BASE[84]);	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = DLG_TEXT_BASE[85];
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = DLG_TEXT_BASE[86];
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase(DLG_TEXT_BASE[87],DLG_TEXT_BASE[88],DLG_TEXT_BASE[89]);
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[90],
							DLG_TEXT_BASE[91]);
						link.l2 = LinkRandPhrase(DLG_TEXT_BASE[92], 
							RandPhraseSimple(DLG_TEXT_BASE[93],DLG_TEXT_BASE[94]),
							RandPhraseSimple(DLG_TEXT_BASE[95],
							DLG_TEXT_BASE[96]));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = DLG_TEXT_BASE[97];
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = DLG_TEXT_BASE[6] + GetConvertStr(attrLoc +" Town", "LocLables.txt") + DLG_TEXT_BASE[7];
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = DLG_TEXT_BASE[98];
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = DLG_TEXT_BASE[99];
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = DLG_TEXT_BASE[100];
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = DLG_TEXT_BASE[101] + GetAddress_Form(NPChar) + " !";
			link.l1 = DLG_TEXT_BASE[102];
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = DLG_TEXT_BASE[103];
                link.l1 = DLG_TEXT_BASE[48];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[104] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[105];
                link.l1 = DLG_TEXT_BASE[51];
				link.l1.go = "free_to_officer_Hire";
                link.l2 = DLG_TEXT_BASE[52];
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[106],
					DLG_TEXT_BASE[107],
					DLG_TEXT_BASE[108]);
				link.l1 = DLG_TEXT_BASE[109];	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[110];
				link.l1 = DLG_TEXT_BASE[111];	
				link.l1.go = "free_to_officer_Hire";
                link.l2 = DLG_TEXT_BASE[52];
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
        case "Slave_1":
			dialog.text = DLG_TEXT_BASE[13] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[14];
            link.l1 = DLG_TEXT_BASE[15];
			link.l1.go = "Slave_2";
			link.l99 = DLG_TEXT_BASE[16];
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = DLG_TEXT_BASE[17];
                link.l1 = DLG_TEXT_BASE[18];
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = DLG_TEXT_BASE[19];
                        link.l1 = DLG_TEXT_BASE[20];
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = DLG_TEXT_BASE[21];
						link.l1 = DLG_TEXT_BASE[22];
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
                    dialog.text = DLG_TEXT_BASE[23];
                    link.l1 = DLG_TEXT_BASE[24];
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = DLG_TEXT_BASE[40] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[41];
            link.l1 = DLG_TEXT_BASE[42] + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = DLG_TEXT_BASE[43];
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = DLG_TEXT_BASE[44]+GetFullName(PChar) + " !!!";
            link.l1 = DLG_TEXT_BASE[45];
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[112],
						DLG_TEXT_BASE[113]);
					link.l1 = DLG_TEXT_BASE[114];	
				break;
				case "trade":
					dialog.text = DLG_TEXT_BASE[115];
					link.l1 = DLG_TEXT_BASE[116];
				break;
				case "war":
					dialog.text = DLG_TEXT_BASE[117];
					link.l1 = DLG_TEXT_BASE[118];
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = DLG_TEXT_BASE[119] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[120];
			link.l1 = DLG_TEXT_BASE[121];
			link.l1.go = "PunishmentAction1";
			link.l2 = DLG_TEXT_BASE[122];
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                    {
                        dialog.text = DLG_TEXT_BASE[19];
                        link.l1 = DLG_TEXT_BASE[20];
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = DLG_TEXT_BASE[21];
						link.l1 = DLG_TEXT_BASE[22];
						link.l1.go = "free_in_sea_battle_1";
					}		
    		}
			else
    		{
				dialog.text = DLG_TEXT_BASE[123];
                link.l1 = DLG_TEXT_BASE[124];
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "free_tip_off_0";
			link.l2 = DLG_TEXT_BASE[127];
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = DLG_TEXT_BASE[128];  
				break;
				case "war":
					sTmp = DLG_TEXT_BASE[129];
				break;
				case "pirate":
					sTmp = DLG_TEXT_BASE[130];
				break;
			}
			dialog.text = DLG_TEXT_BASE[131] + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + DLG_TEXT_BASE[132] + NPChar.Hold_GenQuest.Name + ". " + 
				DLG_TEXT_BASE[133] + NPChar.Hold_GenQuest.ShipName + DLG_TEXT_BASE[134] + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + DLG_TEXT_BASE[135] + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +". " + 
				DLG_TEXT_BASE[136] + sTmp + DLG_TEXT_BASE[137];
			link.l1 = DLG_TEXT_BASE[138];	
			link.l1.go = "free_tip_off_0";
			link.l2 = DLG_TEXT_BASE[139];
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = DLG_TEXT_BASE[140];
			link.l1 = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[141],DLG_TEXT_BASE[142]),
				RandPhraseSimple(DLG_TEXT_BASE[143],DLG_TEXT_BASE[144]));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = DLG_TEXT_BASE[145] + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + DLG_TEXT_BASE[146] + NPChar.Hold_GenQuest.Name + DLG_TEXT_BASE[147] +
				DLG_TEXT_BASE[148];
			link.l1 = DLG_TEXT_BASE[149];	
			link.l1.go = "free_buyout1";
			link.l2 = DLG_TEXT_BASE[150];
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = DLG_TEXT_BASE[151];
			link.l1 = DLG_TEXT_BASE[152];
			link.l1.go = "free_by_hoard1";
			link.l2 = DLG_TEXT_BASE[153];
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = DLG_TEXT_BASE[154];
			link.l1 = DLG_TEXT_BASE[155];
			link.l1.go = "free_tip_off_0";
			link.l2 = DLG_TEXT_BASE[156];
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = DLG_TEXT_BASE[157]+ GetSexPhrase(DLG_TEXT_BASE[158],DLG_TEXT_BASE[159]) +DLG_TEXT_BASE[160];
			link.l1 = DLG_TEXT_BASE[161];
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = DLG_TEXT_BASE[162] + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + 
				DLG_TEXT_BASE[163] + NPChar.Hold_GenQuest.Name + DLG_TEXT_BASE[164] + 
				DLG_TEXT_BASE[165] + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + DLG_TEXT_BASE[166] +
				DLG_TEXT_BASE[167]+ 
                DLG_TEXT_BASE[168];
			link.l1 = DLG_TEXT_BASE[169];
			link.l1.go = "free_tip_off_0";
			link.l2 = DLG_TEXT_BASE[170];
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = DLG_TEXT_BASE[171]+ GetSexPhrase(DLG_TEXT_BASE[172],DLG_TEXT_BASE[173]);
			link.l1 = DLG_TEXT_BASE[174];
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = DLG_TEXT_BASE[25] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[26];
            link.l1 = DLG_TEXT_BASE[27];
			link.l1.go = "PunishmentAction1";
			link.l99 = DLG_TEXT_BASE[28];
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = DLG_TEXT_BASE[175];
			link.l1 = DLG_TEXT_BASE[176];
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = DLG_TEXT_BASE[177];
			link.l1 = DLG_TEXT_BASE[178];
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = DLG_TEXT_BASE[179];
			link.l1 = DLG_TEXT_BASE[180];
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = DLG_TEXT_BASE[181];
			link.l1 = DLG_TEXT_BASE[182];
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = DLG_TEXT_BASE[183]+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+DLG_TEXT_BASE[184];
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = DLG_TEXT_BASE[185];
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = DLG_TEXT_BASE[186];
			link.l1 = DLG_TEXT_BASE[187];
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = DLG_TEXT_BASE[188]+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+DLG_TEXT_BASE[189] + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen") + DLG_TEXT_BASE[190];
			link.l1 = DLG_TEXT_BASE[191] + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen") + DLG_TEXT_BASE[192];
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = DLG_TEXT_BASE[193];
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			dialog.text = DLG_TEXT_BASE[194];
			link.l1 = DLG_TEXT_BASE[195];
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = DLG_TEXT_BASE[196];
			link.l1 = DLG_TEXT_BASE[197];
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = DLG_TEXT_BASE[198];
			link.l1 = DLG_TEXT_BASE[199];
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = DLG_TEXT_BASE[200];
			link.l1 = DLG_TEXT_BASE[201];
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Woman_Prison":
			dialog.text = DLG_TEXT_BASE[186];
			link.l1 = DLG_TEXT_BASE[187];
			link.l1.go = "Exit";
		break;
	}
}
