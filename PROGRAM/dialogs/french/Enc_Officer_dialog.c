#include "SD\TEXT\DIALOGS\Enc_Officer_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
  	if (findsubstr(sAttr, "MyGrow_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	npchar.MyGrow = strcut(sAttr, i+1, strlen(sAttr)-1); // индех в конце
 	    Dialog.CurrentNode = "New_Grow";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_TEXT_BASE[4];
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = DLG_TEXT_BASE[5];
    			Link.l1.go = "Node_2";
			}
			Link.l2 = DLG_TEXT_BASE[6];
			Link.l2.go = "Exit";		
		break;
		
		case "CitizenNotBlade":
			dialog.text = DLG_TEXT_BASE[137];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[138], DLG_TEXT_BASE[139], DLG_TEXT_BASE[140]);
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = DLG_TEXT_BASE[7];
				link.l2 = DLG_TEXT_BASE[8];
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = DLG_TEXT_BASE[9];
				Link.l1 = DLG_TEXT_BASE[10];
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[11],DLG_TEXT_BASE[12]);
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = DLG_TEXT_BASE[141];
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = ""+npchar.name+DLG_TEXT_BASE[142];
				Link.l4.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
	            Link.l2 = DLG_TEXT_BASE[13];
				Link.l2.go = "stay_follow";
			}

           		// boal отчет о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = DLG_TEXT_BASE[17] + GetStrSmallRegister(XI_ConvertString("treasurer")) + ".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = DLG_TEXT_BASE[143];
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = DLG_TEXT_BASE[144];
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = DLG_TEXT_BASE[14] + NPCharSexPhrase(NPChar, "", DLG_TEXT_BASE[15]) + DLG_TEXT_BASE[16];
			Link.l4.go = "AsYouWish";
			}
			if (Npchar.location == "Myown_Tavern")
			{	
				sld = CharacterFromID("MonBarmen");
				if (sld.officer != 7)
				{				
				Link.l7 = "Assis-toi";
				Link.l7.go = "Tavern";
				}
			}
			if (Npchar.location == "My_Plantation")
			{	
				sld = CharacterFromID("Islamona_carpenter");
				if (!CheckAttribute(sld, "Planta_officer"))
				{				
				Link.l7 = DLG_TEXT_BASE[31];
				Link.l7.go = "Planta_Hire";
				}
			}			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = DLG_TEXT_BASE[18];
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = DLG_TEXT_BASE[19];
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[145],DLG_TEXT_BASE[146],DLG_TEXT_BASE[147]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[148],DLG_TEXT_BASE[149],DLG_TEXT_BASE[150]);
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = DLG_TEXT_BASE[151];
				Link.l1 = DLG_TEXT_BASE[152];
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = DLG_TEXT_BASE[153]+ GetSexPhrase(DLG_TEXT_BASE[154],DLG_TEXT_BASE[155]) +DLG_TEXT_BASE[156];
			Link.l1 = DLG_TEXT_BASE[157];
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = DLG_TEXT_BASE[158]+ GetSexPhrase(DLG_TEXT_BASE[159],DLG_TEXT_BASE[160]) +DLG_TEXT_BASE[161];
			Link.l1 = DLG_TEXT_BASE[162];
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			int x = rand(10);
			if (x!=0)
			{
			dialog.text = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[163],DLG_TEXT_BASE[164],DLG_TEXT_BASE[165]), LinkRandPhrase(DLG_TEXT_BASE[166],DLG_TEXT_BASE[167],DLG_TEXT_BASE[168]), LinkRandPhrase(DLG_TEXT_BASE[169],DLG_TEXT_BASE[170],DLG_TEXT_BASE[171]));
			Link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[172],DLG_TEXT_BASE[173],DLG_TEXT_BASE[174]), LinkRandPhrase(DLG_TEXT_BASE[175],DLG_TEXT_BASE[176],DLG_TEXT_BASE[177]));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[178]+sti(NPChar.rank)*250+DLG_TEXT_BASE[179], DLG_TEXT_BASE[180]+sti(NPChar.rank)*250+DLG_TEXT_BASE[181], DLG_TEXT_BASE[182]+sti(NPChar.rank)*250+DLG_TEXT_BASE[183]); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase(DLG_TEXT_BASE[184],DLG_TEXT_BASE[185],DLG_TEXT_BASE[186]);	
			Link.l3.go = "WantToGo_Stay";
			}
			else
			{
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[20],DLG_TEXT_BASE[21],DLG_TEXT_BASE[22]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[23],DLG_TEXT_BASE[24],DLG_TEXT_BASE[25]);
			Link.l1.go = "WantToGo_free";	
			Link.l3 = LinkRandPhrase(DLG_TEXT_BASE[26],DLG_TEXT_BASE[27],DLG_TEXT_BASE[28]);	
			Link.l3.go = "WantToGo_Stay_Aop";
			}
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = DLG_TEXT_BASE[187];
			Link.l1 = DLG_TEXT_BASE[188];
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = DLG_TEXT_BASE[189];
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay_Aop":
			dialog.text = DLG_TEXT_BASE[29];
			Link.l1 = DLG_TEXT_BASE[30];
			Link.l1.go = "WantToGo_Stay_2";	
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple(DLG_TEXT_BASE[195],DLG_TEXT_BASE[196]),
				LinkRandPhrase(DLG_TEXT_BASE[197],DLG_TEXT_BASE[198],DLG_TEXT_BASE[199]));	
			Link.l2.go = "WantToGo_Stay_force";			
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[190],DLG_TEXT_BASE[191]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[192],DLG_TEXT_BASE[193],DLG_TEXT_BASE[194]);
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple(DLG_TEXT_BASE[195],DLG_TEXT_BASE[196]),
				LinkRandPhrase(DLG_TEXT_BASE[197],DLG_TEXT_BASE[198],DLG_TEXT_BASE[199]));	
			Link.l2.go = "WantToGo_Stay_force";
		break;		
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase(DLG_TEXT_BASE[200]+sti(NPChar.rank)*500+DLG_TEXT_BASE[201], DLG_TEXT_BASE[202]+sti(NPChar.rank)*500+DLG_TEXT_BASE[203], DLG_TEXT_BASE[204]+sti(NPChar.rank)*500+DLG_TEXT_BASE[205]);
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[206],DLG_TEXT_BASE[207],DLG_TEXT_BASE[208]);	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[209],DLG_TEXT_BASE[210],DLG_TEXT_BASE[211]);				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = DLG_TEXT_BASE[212];
		Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[213],DLG_TEXT_BASE[214],DLG_TEXT_BASE[215]);
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase (DLG_TEXT_BASE[216],DLG_TEXT_BASE[217],DLG_TEXT_BASE[218]);	
		Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[219],DLG_TEXT_BASE[220]);
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[221],DLG_TEXT_BASE[222],DLG_TEXT_BASE[223]), LinkRandPhrase(DLG_TEXT_BASE[224],DLG_TEXT_BASE[225],DLG_TEXT_BASE[226])) + DLG_TEXT_BASE[227];
			Link.l1 = DLG_TEXT_BASE[228];
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = DLG_TEXT_BASE[229]+sti(NPChar.rank)*500+DLG_TEXT_BASE[230];
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase(DLG_TEXT_BASE[231],DLG_TEXT_BASE[232],DLG_TEXT_BASE[233]);
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[234],DLG_TEXT_BASE[235],DLG_TEXT_BASE[236]), LinkRandPhrase(DLG_TEXT_BASE[237],DLG_TEXT_BASE[238],DLG_TEXT_BASE[239]));
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[240],DLG_TEXT_BASE[241]) + DLG_TEXT_BASE[242];
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = DLG_TEXT_BASE[243]+sti(NPChar.rank)*500+DLG_TEXT_BASE[244];
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple(DLG_TEXT_BASE[245],DLG_TEXT_BASE[246]);
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[247],DLG_TEXT_BASE[248],DLG_TEXT_BASE[249]);
				Link.l1 = DLG_TEXT_BASE[250];
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = DLG_TEXT_BASE[251];
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[252],DLG_TEXT_BASE[253],DLG_TEXT_BASE[254]);
				Link.l1 = DLG_TEXT_BASE[255];
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = DLG_TEXT_BASE[256];
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[257],DLG_TEXT_BASE[258]);
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[259],DLG_TEXT_BASE[260]);
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, DLG_TEXT_BASE[261], DLG_TEXT_BASE[262]);
			Link.l1 = NPCharRepPhrase(NPChar, DLG_TEXT_BASE[263], DLG_TEXT_BASE[264]);
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, DLG_TEXT_BASE[265], DLG_TEXT_BASE[266]);
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar, DLG_TEXT_BASE[267],DLG_TEXT_BASE[268]);
			Link.l1 = NPCharRepPhrase(NPChar, DLG_TEXT_BASE[269],DLG_TEXT_BASE[270]);
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			if (sti(Pchar.questTemp.MunityOfficerIDX) != GetCharacterIndex(Npchar.id))
			{
				Pchar.questTemp.MunityOfficerIDX = GetCharacterIndex(Npchar.id);
				Pchar.questTemp.MunityOfficerIDX.begin = "1";
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + DLG_TEXT_BASE[43]+ XI_ConvertString(Npchar.quest.officertype) + DLG_TEXT_BASE[44] + Npchar.quest.officertype_2 + DLG_TEXT_BASE[45],
                                    DLG_TEXT_BASE[46] + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + DLG_TEXT_BASE[47]);
			Link.l1 = DLG_TEXT_BASE[48];
			Link.l1.go = "price";
			Link.l2 = DLG_TEXT_BASE[49];
			Link.l2.go = "ShowParam_exit";
			Link.l3 = DLG_TEXT_BASE[50] + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[51], DLG_TEXT_BASE[52]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[53], DLG_TEXT_BASE[54]); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_TEXT_BASE[55] + XI_ConvertString(Npchar.quest.officertype) + DLG_TEXT_BASE[56];
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = DLG_TEXT_BASE[57];
                Link.l1.go = "price";
			}
			Link.l2 = DLG_TEXT_BASE[58];
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = DLG_TEXT_BASE[59];
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = DLG_TEXT_BASE[60] + Npchar.quest.OfficerPrice + DLG_TEXT_BASE[61];
			Link.l1 = DLG_TEXT_BASE[62];
			Link.l1.go = "trade";
			Link.l2 = DLG_TEXT_BASE[63];
			Link.l2.go = "hire";
			Link.l3 = DLG_TEXT_BASE[64];
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = DLG_TEXT_BASE[65] + Npchar.quest.OfficerPrice + DLG_TEXT_BASE[66];
				Link.l1 = DLG_TEXT_BASE[67];
				Link.l1.go = "hire";				
				Link.l2 = DLG_TEXT_BASE[68];
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[69];
				Link.l1 = DLG_TEXT_BASE[70];
				Link.l1.go = "hire";				
				Link.l2 = DLG_TEXT_BASE[71];
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = DLG_TEXT_BASE[72];
				Link.l1 = DLG_TEXT_BASE[73];
				Link.l1.go = "Exit_hire";								
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[74];
				Link.l1 = DLG_TEXT_BASE[75];
				Link.l1.go = "Exit";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = DLG_TEXT_BASE[76];
			Link.l1 = DLG_TEXT_BASE[77];
			Link.l1.go = "Exit";										
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = DLG_TEXT_BASE[271];
				Link.l1 = DLG_TEXT_BASE[272];
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			
			dialog.text = DLG_TEXT_BASE[78] +
			FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
			DLG_TEXT_BASE[78]+GetCrewQuantity(PChar) + DLG_TEXT_BASE[79] + makeint((GetCrewQuantity(PChar)+6) / 10) + DLG_TEXT_BASE[80];
			Link.l1 = DLG_TEXT_BASE[81];
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = DLG_TEXT_BASE[83];
            Link.l1 = DLG_TEXT_BASE[84];
            Link.l1.go = "Boal_Stay";
            Link.l2 = DLG_TEXT_BASE[85];
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = DLG_TEXT_BASE[86];
				Link.l3.go = "TargetDistance";
			}
			
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l4 = DLG_TEXT_BASE[273];
					Link.l4.go = "SetGunBullets";
				}	
			}						
		break;

		case "SetGunBullets":
			Dialog.Text = DLG_TEXT_BASE[274];
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
		case "TargetDistance":
			dialog.text = DLG_TEXT_BASE[87];
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = DLG_TEXT_BASE[88];
				link.l1 = DLG_TEXT_BASE[89];
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = DLG_TEXT_BASE[90];
				link.l1 = DLG_TEXT_BASE[91];
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = DLG_TEXT_BASE[92];
				link.l1 = DLG_TEXT_BASE[93];
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = DLG_TEXT_BASE[96];
					Link.l1 = DLG_TEXT_BASE[97];
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[275],DLG_TEXT_BASE[276],DLG_TEXT_BASE[277]), RandPhraseSimple(DLG_TEXT_BASE[278],DLG_TEXT_BASE[279]));
				Link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[280],DLG_TEXT_BASE[281],DLG_TEXT_BASE[282]), LinkRandPhrase(DLG_TEXT_BASE[283],DLG_TEXT_BASE[284],DLG_TEXT_BASE[285])) + DLG_TEXT_BASE[286];
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[287],DLG_TEXT_BASE[288]), RandPhraseSimple(DLG_TEXT_BASE[289],DLG_TEXT_BASE[290]));
				Link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[291],DLG_TEXT_BASE[292],DLG_TEXT_BASE[293]), LinkRandPhrase(DLG_TEXT_BASE[294],DLG_TEXT_BASE[295],DLG_TEXT_BASE[296]));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[297],DLG_TEXT_BASE[298]), RandPhraseSimple(DLG_TEXT_BASE[299],DLG_TEXT_BASE[300]));
				Link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[301],DLG_TEXT_BASE[302],DLG_TEXT_BASE[303]), LinkRandPhrase(DLG_TEXT_BASE[304],DLG_TEXT_BASE[305],DLG_TEXT_BASE[306])) + DLG_TEXT_BASE[307];
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[308],DLG_TEXT_BASE[309],DLG_TEXT_BASE[310]), RandPhraseSimple(DLG_TEXT_BASE[311],DLG_TEXT_BASE[312]));
				Link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[313],DLG_TEXT_BASE[314],DLG_TEXT_BASE[315]), LinkRandPhrase(DLG_TEXT_BASE[316],DLG_TEXT_BASE[317],DLG_TEXT_BASE[318])) + DLG_TEXT_BASE[319];
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[320],DLG_TEXT_BASE[321],DLG_TEXT_BASE[322]), LinkRandPhrase(DLG_TEXT_BASE[323],DLG_TEXT_BASE[324],DLG_TEXT_BASE[325]));
			Link.l1 = DLG_TEXT_BASE[326];
			Link.l1.go = "exit_bad";
			Link.l2 = DLG_TEXT_BASE[327];
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = DLG_TEXT_BASE[328]+sti(NPChar.rank)*500+DLG_TEXT_BASE[329];
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[330], DLG_TEXT_BASE[331],DLG_TEXT_BASE[332]);
			Link.l1 = DLG_TEXT_BASE[333] ;
			Link.l1.go = "exit_bad";
			Link.l2 = DLG_TEXT_BASE[334];
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = DLG_TEXT_BASE[335]+sti(NPChar.rank)*500+DLG_TEXT_BASE[336];
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[337],DLG_TEXT_BASE[338]) + " "+sti(NPChar.rank)*1000+DLG_TEXT_BASE[339];
			Link.l1 = DLG_TEXT_BASE[340];
			Link.l1.go = "exit_bad1";
			Link.l2 = DLG_TEXT_BASE[341];
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = DLG_TEXT_BASE[342];
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = DLG_TEXT_BASE[343];
			Link.l1 = DLG_TEXT_BASE[344];
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[345],DLG_TEXT_BASE[346],DLG_TEXT_BASE[347]);
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = DLG_TEXT_BASE[348];
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = DLG_TEXT_BASE[349];
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = DLG_TEXT_BASE[350];
			Link.l1 = DLG_TEXT_BASE[351];
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = DLG_TEXT_BASE[352];
			Link.l1 = DLG_TEXT_BASE[353];
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[354],DLG_TEXT_BASE[355],DLG_TEXT_BASE[356]), LinkRandPhrase(DLG_TEXT_BASE[357],DLG_TEXT_BASE[358],DLG_TEXT_BASE[359]));
			Link.l1 = DLG_TEXT_BASE[360];
			Link.l1.go = "exit_good";
			Link.l2 = DLG_TEXT_BASE[361];
			Link.l2.go = "exit_fire_2";
			Link.l3 = DLG_TEXT_BASE[362];
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = DLG_TEXT_BASE[363]+sti(NPChar.rank)*500+DLG_TEXT_BASE[364];
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = DLG_TEXT_BASE[365];
			Link.l1 = DLG_TEXT_BASE[366];
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = DLG_TEXT_BASE[367];
			Link.l1 = DLG_TEXT_BASE[368];
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = DLG_TEXT_BASE[369];
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[370],DLG_TEXT_BASE[371],DLG_TEXT_BASE[372]), LinkRandPhrase(DLG_TEXT_BASE[373],DLG_TEXT_BASE[374],DLG_TEXT_BASE[375]));
			Link.l1 = DLG_TEXT_BASE[376];
			Link.l1.go = "exit_bad";
			Link.l2 = DLG_TEXT_BASE[377];
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = DLG_TEXT_BASE[378]+sti(NPChar.rank)*500+DLG_TEXT_BASE[379];
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[380],DLG_TEXT_BASE[381],DLG_TEXT_BASE[382]);
			Link.l1 = DLG_TEXT_BASE[383];
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[384],DLG_TEXT_BASE[385],DLG_TEXT_BASE[386]);
			Link.l1 = DLG_TEXT_BASE[387];
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = DLG_TEXT_BASE[388]+sti(NPChar.rank)*500+DLG_TEXT_BASE[389];
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = DLG_TEXT_BASE[390];
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = DLG_TEXT_BASE[391];
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = DLG_TEXT_BASE[392]+sti(NPChar.rank)*1000+DLG_TEXT_BASE[393];
			Link.l1 = DLG_TEXT_BASE[394];
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = DLG_TEXT_BASE[395];
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = DLG_TEXT_BASE[396];
			Link.l1 = DLG_TEXT_BASE[397];
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = DLG_TEXT_BASE[398];
			Link.l1 = DLG_TEXT_BASE[399];
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[400],DLG_TEXT_BASE[401],DLG_TEXT_BASE[402]), LinkRandPhrase(DLG_TEXT_BASE[403],DLG_TEXT_BASE[404],DLG_TEXT_BASE[405]));
			Link.l1 = DLG_TEXT_BASE[406];
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple(DLG_TEXT_BASE[407],DLG_TEXT_BASE[408]);
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = DLG_TEXT_BASE[409]+sti(NPChar.rank)*500+DLG_TEXT_BASE[410];
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = DLG_TEXT_BASE[411];
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[412],DLG_TEXT_BASE[413],DLG_TEXT_BASE[414]);
			Link.l1 = DLG_TEXT_BASE[415];
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[416],DLG_TEXT_BASE[417],DLG_TEXT_BASE[418]);
				Link.l1 = DLG_TEXT_BASE[419];
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[420]+sti(NPChar.rank)*1000+DLG_TEXT_BASE[421], DLG_TEXT_BASE[422]+sti(NPChar.rank)*1000+DLG_TEXT_BASE[423]);
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = DLG_TEXT_BASE[424];
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = DLG_TEXT_BASE[425];
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = DLG_TEXT_BASE[426];
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = DLG_TEXT_BASE[427];
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[428],DLG_TEXT_BASE[429]);
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = DLG_TEXT_BASE[430];
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[431],DLG_TEXT_BASE[432]);	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = DLG_TEXT_BASE[433];
			Link.l1 = DLG_TEXT_BASE[434];	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = DLG_TEXT_BASE[435];
			Link.l1 = DLG_TEXT_BASE[436];	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = DLG_TEXT_BASE[437];
			Link.l1 = DLG_TEXT_BASE[438];	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		      dialog.text = DLG_TEXT_BASE[109];
		      Link.l1 = DLG_TEXT_BASE[110];
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		      dialog.text = DLG_TEXT_BASE[111];
		      Link.l1 = DLG_TEXT_BASE[112];
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = DLG_TEXT_BASE[113];
            Link.l1 = DLG_TEXT_BASE[114];
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = DLG_TEXT_BASE[115];
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = DLG_TEXT_BASE[116] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[117];
			}
			else
			{
			    dialog.Text = DLG_TEXT_BASE[118];
			}

            Link.l1 = DLG_TEXT_BASE[119] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[120], DLG_TEXT_BASE[121]) + DLG_TEXT_BASE[122];
        	Link.l1.go = "Gover_Tax";
            Link.l8 = DLG_TEXT_BASE[123] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[124], DLG_TEXT_BASE[125]) + DLG_TEXT_BASE[126];
            Link.l8.go = "Gover_Fire";
			Link.l9 = DLG_TEXT_BASE[127];
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = DLG_TEXT_BASE[128] + FindRussianMoneyString(iFortValue*iTax) + DLG_TEXT_BASE[129] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[130] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[131], DLG_TEXT_BASE[132]) + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = DLG_TEXT_BASE[133];
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = DLG_TEXT_BASE[134];
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = DLG_TEXT_BASE[135];
            Link.l8 = DLG_TEXT_BASE[136];
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = DLG_TEXT_BASE[439];
			Link.l1 = DLG_TEXT_BASE[440];
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = DLG_TEXT_BASE[441];
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = DLG_TEXT_BASE[442];
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = DLG_TEXT_BASE[443];
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = DLG_TEXT_BASE[444];
			Link.l1 = DLG_TEXT_BASE[445];
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = DLG_TEXT_BASE[446];
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = DLG_TEXT_BASE[447];
			Link.l1 = DLG_TEXT_BASE[448];
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = DLG_TEXT_BASE[449];
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = DLG_TEXT_BASE[450];
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = DLG_TEXT_BASE[451];
			Link.l1 = DLG_TEXT_BASE[452];
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = DLG_TEXT_BASE[453];
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = DLG_TEXT_BASE[454];
			Link.l1 = DLG_TEXT_BASE[455];
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = DLG_TEXT_BASE[446];
					Link.l1 = DLG_TEXT_BASE[457];
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = DLG_TEXT_BASE[458];
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = DLG_TEXT_BASE[459] + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = DLG_TEXT_BASE[460];
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = DLG_TEXT_BASE[461];
				Link.l1 = DLG_TEXT_BASE[462];
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = DLG_TEXT_BASE[463];
				Link.l1 = DLG_TEXT_BASE[464];
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = DLG_TEXT_BASE[465];
				Link.l1 = DLG_TEXT_BASE[466];
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = DLG_TEXT_BASE[467];
				Link.l1 = DLG_TEXT_BASE[468];
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = DLG_TEXT_BASE[469] + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + DLG_TEXT_BASE[470] + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + DLG_TEXT_BASE[471];
				Link.l1 = DLG_TEXT_BASE[472];
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = DLG_TEXT_BASE[473];
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = DLG_TEXT_BASE[474];
				Link.l1 = DLG_TEXT_BASE[475];
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[476],
			DLG_TEXT_BASE[477] + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = DLG_TEXT_BASE[478];
					Link.l1 = DLG_TEXT_BASE[479];
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[480];
					Link.l1 = DLG_TEXT_BASE[481];
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = DLG_TEXT_BASE[482];
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = DLG_TEXT_BASE[483] + NPChar.name + DLG_TEXT_BASE[484];
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[485];
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		case "Tavern":
			DialogExit();
			CheckForReleaseOfficer(sti(npchar.index));
			RemovePassenger(pchar, npchar);
			RemoveCharacterCompanion(pchar, npchar);			
			sld = CharacterFromID("MonBarmen");
            npchar.location = "MyOwn_Tavern";
            npchar.location.group = "sit";
			LAi_SetSitType(npchar);
			npchar.dialog.currentnode = "Tavern2";					
			i=1;
			while(i!=0)
			{
				if(CheckAttribute(sld, "place"+i)) i++;
				else
				{
				sld.officer = sti(sld.officer+1);
				attrLoc = "place"+i;
				sld.(attrLoc) = true;
				if(attrLoc == "place1") npchar.location.locator = "sit2";
				if(attrLoc == "place2") npchar.location.locator = "sit_front4";
				if(attrLoc == "place3") npchar.location.locator = "sit_base4";
				if(attrLoc == "place4") npchar.location.locator = "sit1";
				if(attrLoc == "place5") npchar.location.locator = "sit_base2";
				if(attrLoc == "place6") npchar.location.locator = "sit_base1";
				if(attrLoc == "place7")	npchar.location.locator = "sit_front1";		
				i=0;
				}
			}
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");			
		break;	

		case "Tavern2":
			Diag.TempNode = "Tavern2";
			dialog.text = DLG_TEXT_BASE[206];
			link.l1 = DLG_TEXT_BASE[207];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[208];
			link.l2.go = "exit_hire2";
		break;
		
		case "exit_hire2":
			sld = CharacterFromID("MonBarmen");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
			if(NPChar.location.locator == "sit2") DeleteAttribute(sld, "place1");
			if(NPChar.location.locator == "sit_front4") DeleteAttribute(sld, "place2");
			if(NPChar.location.locator == "sit_base4") DeleteAttribute(sld, "place3");
			if(NPChar.location.locator == "sit1") DeleteAttribute(sld, "place4");
			if(NPChar.location.locator == "sit_base2") DeleteAttribute(sld, "place5");
			if(NPChar.location.locator == "sit_base1") DeleteAttribute(sld, "place6");
			if(NPChar.location.locator == "sit_front1")	DeleteAttribute(sld, "place7");	
			sld.officer = sti(sld.officer-1);			
		break;		

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "exit_planta":
			npchar.dialog.currentnode = "Planta_Main";
			DialogExit();			
		break;

		case "exit_Inter":
			npchar.dialog.currentnode = "Planta_Main";
			DialogExit();
			LaunchStorage(29);		
		break;
		
	    case "Planta_Hire":	
			sld = CharacterFromID("Islamona_carpenter");
			sld.Planta_officer = true;
			NPChar.quest.meeting = true;
			DialogExit();		
			CheckForReleaseOfficer(sti(npchar.index));
			RemovePassenger(Pchar, npchar);
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetHuberType(npchar);
			npchar.location = "My_Planta_Office";
			npchar.location.group = "sit";
			npchar.location.locator = "sit1";	
			npchar.dialog.currentnode = "Planta_Main";				
			DoQuestReloadToLocation("My_Planta_Office", "reload", "Reload1", "");
		break;	

        case "Planta_Main":
			dialog.text = DLG_TEXT_BASE[32];
			if(CheckAttribute(npchar, "MyGrow"))
			{			
			Link.l1 = DLG_TEXT_BASE[33];
            Link.l1.go = "Planta_collect";	
			Link.l2 = "Je voudrais changer de culture";
            Link.l2.go = "Planta_change";				
			}
			else
			{
			Link.l1 = DLG_TEXT_BASE[34];
            Link.l1.go = "Grow_Something";				
			}		
            Link.l3 = DLG_TEXT_BASE[36];
            Link.l3.go = "TakeBack";
			Link.l4 = DLG_TEXT_BASE[35];
			Link.l4.go = "exit_planta";					
		break;

        case "TakeBack":
            dialog.Text = DLG_TEXT_BASE[135];
            Link.l8 = DLG_TEXT_BASE[136];
            Link.l8.go = "TakeBack_B";
            Diag.TempNode = "Hired";
        break;	

        case "TakeBack_B":	   
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			sld = CharacterFromID("Islamona_carpenter");
			DeleteAttribute(sld,"Planta_officer");
			DeleteAttribute(npchar,"quantity");
			DeleteAttribute(npchar,"MyGrow");			
			DialogExit();
        break;			

        case "Grow_Something":			
            dialog.Text = "Que voulez-vous cultiver ?";
            Link.l1 = DLG_TEXT_BASE[136];		
            Link.l1.go = "exit_planta";
            Link.l2 = "Tabac";						
            Link.l2.go = "MyGrow_" + GOOD_TOBACCO;			
            Link.l3 = "Cafe";	
            Link.l3.go = "MyGrow_" + GOOD_COFFEE;			
            Link.l4 = "Sucre";			
            Link.l4.go = "MyGrow_" + GOOD_SUGAR;			
            Link.l5 = "Vanille";			
            Link.l5.go = "MyGrow_" + GOOD_CINNAMON;			
        break;		
		
        case "New_Grow":
            dialog.Text = "Tres bien nous allons lancer la culture de " + GetConvertStr(Goods[sti(npchar.MyGrow)].name, "GoodsDescribe.txt") + ".";
            Link.l1 = "Je reviendrai recuperer les recoltes.";
            Link.l1.go = "exit_planta";
			SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
        break;			
			
        case "Planta_collect":
			sld = CharacterFromID("PrisonRoomMan");
			i = 1 + sti(sld.prisoner);
			NPchar.quantity = sti(GetNpcQuestPastDayParam(NPChar, "StartTaxDate")) * sti(npchar.MyGrow) * i;
			attr = Goods[sti(npchar.MyGrow)].name;
			rItm = &Stores[29];
			iTax = sti(GetStorageUsedWeight(&Stores[29]))+sti(GetGoodWeightByType(sti(npchar.MyGrow), sti(NPchar.quantity)))
			if (iTax <= 50000)
			{
			rItm.Storage.Goods.(attr).Quantity = sti(rItm.Storage.Goods.(attr).Quantity) + sti(NPchar.quantity);
			}
			else
			{
			iTemp = (iTax - 50000)/sti(GetGoodWeightByType(sti(npchar.MyGrow), 1))
			rItm.Storage.Goods.(attr).Quantity = sti(rItm.Storage.Goods.(attr).Quantity) + sti(NPchar.quantity) - iTemp;	
			attrL = " Attention, l'entrepot est plein, nous n'avons pas pu conserver toute la recolte.";
			}
            dialog.Text = "Votre derniere visite remonte a " + GetNpcQuestPastDayParam(NPChar, "StartTaxDate") + " jours. Nous avons pu recolter " + NPchar.quantity + " unites de " + GetConvertStr(Goods[sti(npchar.MyGrow)].name, "GoodsDescribe.txt") + ". Les stocks ont ete deplace vers l'entrepot." + attrL;
            Link.l1 = "Parfait, montrez moi.";		
            Link.l1.go = "exit_Inter";
			SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
        break;	

        case "Planta_change":
            dialog.Text = "Attention si nous changeons de culture, nous allons devoir detruire la recolte actuelle. Par quoi voulez-vous remplacer la culture ?";
            Link.l1 = "Oubliez ca, j'ai change d'avis.";		
            Link.l1.go = "exit_planta";
            Link.l2 = "Tabac";						
            Link.l2.go = "MyGrow_" + GOOD_TOBACCO;			
            Link.l3 = "Cafe";	
            Link.l3.go = "MyGrow_" + GOOD_COFFEE;			
            Link.l4 = "Sucre";			
            Link.l4.go = "MyGrow_" + GOOD_SUGAR;			
            Link.l5 = "Vanille";			
            Link.l5.go = "MyGrow_" + GOOD_CINNAMON;		
        break;				
	}
}