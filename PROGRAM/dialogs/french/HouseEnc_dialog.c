#include "SD\TEXT\DIALOGS\HouseEnc_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //��������� ���� � ���
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //��������� ���� � ���
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- ����� ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
				LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7] + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
				RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = DLG_TEXT_BASE[190];
					link.l1 = "Heh !";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[191];
					link.l1 = LinkRandPhrase(DLG_TEXT_BASE[192],DLG_TEXT_BASE[193],DLG_TEXT_BASE[194]);
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[16], 
				DLG_TEXT_BASE[17], 
				DLG_TEXT_BASE[18],
				DLG_TEXT_BASE[19], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[20], 
				DLG_TEXT_BASE[21],
				DLG_TEXT_BASE[22], 
				DLG_TEXT_BASE[23], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[24], 
				DLG_TEXT_BASE[25], 
				DLG_TEXT_BASE[26],
				DLG_TEXT_BASE[27], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[28], 
				DLG_TEXT_BASE[29],
				DLG_TEXT_BASE[30], 
				DLG_TEXT_BASE[31], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = DLG_TEXT_BASE[32] + GetFullName(npchar) + DLG_TEXT_BASE[33];
			link.l1 = GetFullName(pchar) + DLG_TEXT_BASE[34];
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			    dialog.text = LinkRandPhrase(DLG_TEXT_BASE[35], DLG_TEXT_BASE[36], DLG_TEXT_BASE[37]);
			    link.l1 = DLG_TEXT_BASE[38];
			link.l1.go = "fight";
		break;
		// --------------------------------- ���� ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[39], DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]), 
				LinkRandPhrase(DLG_TEXT_BASE[42], DLG_TEXT_BASE[43], DLG_TEXT_BASE[44]));
				link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[45], DLG_TEXT_BASE[46]), 
				RandPhraseSimple(DLG_TEXT_BASE[47], DLG_TEXT_BASE[48]));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = DLG_TEXT_BASE[195];
					link.l1 = DLG_TEXT_BASE[196];
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = DLG_TEXT_BASE[197]+ GetSexPhrase(DLG_TEXT_BASE[198],DLG_TEXT_BASE[199]) +DLG_TEXT_BASE[200];
					link.l1 = DLG_TEXT_BASE[201];
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[53] + GetFullName(npchar) + DLG_TEXT_BASE[54], DLG_TEXT_BASE[55], DLG_TEXT_BASE[56], DLG_TEXT_BASE[57], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + DLG_TEXT_BASE[58], DLG_TEXT_BASE[59],	DLG_TEXT_BASE[60], 	DLG_TEXT_BASE[61], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[62], DLG_TEXT_BASE[63], DLG_TEXT_BASE[64],DLG_TEXT_BASE[65], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[66], DLG_TEXT_BASE[67],DLG_TEXT_BASE[68], DLG_TEXT_BASE[69], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- �������� ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[76], DLG_TEXT_BASE[77], DLG_TEXT_BASE[78]), 
					LinkRandPhrase(DLG_TEXT_BASE[79], DLG_TEXT_BASE[80], DLG_TEXT_BASE[81]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[82], DLG_TEXT_BASE[83] + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple(DLG_TEXT_BASE[84], DLG_TEXT_BASE[85]));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[88] + GetFullName(npchar) + DLG_TEXT_BASE[89], 
					DLG_TEXT_BASE[90], 
					DLG_TEXT_BASE[91],
					RandPhraseSimple(DLG_TEXT_BASE[92], DLG_TEXT_BASE[93]), "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[94], 
					DLG_TEXT_BASE[95],
					DLG_TEXT_BASE[96], 
					DLG_TEXT_BASE[97], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);			
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[202],DLG_TEXT_BASE[203],DLG_TEXT_BASE[204]), 
					LinkRandPhrase(DLG_TEXT_BASE[205]+ GetSexPhrase(DLG_TEXT_BASE[206],DLG_TEXT_BASE[207]) +DLG_TEXT_BASE[208]+ GetSexPhrase(DLG_TEXT_BASE[209],DLG_TEXT_BASE[210]) +" !", ""+ GetSexPhrase(DLG_TEXT_BASE[211],DLG_TEXT_BASE[212]) +DLG_TEXT_BASE[213], DLG_TEXT_BASE[214]+ GetSexPhrase(DLG_TEXT_BASE[215],DLG_TEXT_BASE[216]) +DLG_TEXT_BASE[217]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[218], DLG_TEXT_BASE[219] + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple(DLG_TEXT_BASE[220],DLG_TEXT_BASE[221]));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[222], 
				DLG_TEXT_BASE[223], 
				DLG_TEXT_BASE[224],
				RandPhraseSimple(DLG_TEXT_BASE[225], DLG_TEXT_BASE[226]), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[227], 
				DLG_TEXT_BASE[228],
				DLG_TEXT_BASE[229], 
				DLG_TEXT_BASE[230], npchar, Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//���������� ����� ����� �� ������ ������������� ��������
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = DLG_TEXT_BASE[231];
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> ����� ������� ��� ��				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = DLG_TEXT_BASE[232];
					link.l7 = DLG_TEXT_BASE[233];
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = DLG_TEXT_BASE[234];
						link.l7.go = "storage_0";
						link.l8 = DLG_TEXT_BASE[235];
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = DLG_TEXT_BASE[236];
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- ������ ������ ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = DLG_TEXT_BASE[237];
			link.l1 = DLG_TEXT_BASE[238];
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = DLG_TEXT_BASE[239] + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + DLG_TEXT_BASE[240]+
				DLG_TEXT_BASE[241];
			link.l1 = DLG_TEXT_BASE[242];	
			link.l1.go = "storage_rent2";
			link.l2 = DLG_TEXT_BASE[243];
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = DLG_TEXT_BASE[244];
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = DLG_TEXT_BASE[245];
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 =DLG_TEXT_BASE[246];
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = DLG_TEXT_BASE[247];
			link.l1 = DLG_TEXT_BASE[248];
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = DLG_TEXT_BASE[249] + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = DLG_TEXT_BASE[250];
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[251];
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = DLG_TEXT_BASE[252];
				link.l1 = DLG_TEXT_BASE[253];
				link.l1.go = "storage_2";
			}
			link.l2 = DLG_TEXT_BASE[254];
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Non, "+ GetSexPhrase(DLG_TEXT_BASE[255],DLG_TEXT_BASE[256]) +DLG_TEXT_BASE[257];
			link.l1 = DLG_TEXT_BASE[258];
			link.l1.go = "storage_1";
			link.l2 = DLG_TEXT_BASE[259];
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = DLG_TEXT_BASE[260];
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = DLG_TEXT_BASE[261];
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[262];
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = DLG_TEXT_BASE[263];
			link.l1 = DLG_TEXT_BASE[264];
			link.l1.go = "storage_4";
			link.l2 = DLG_TEXT_BASE[265];
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = DLG_TEXT_BASE[266] + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = DLG_TEXT_BASE[267];
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[268];
				link.l1 = DLG_TEXT_BASE[269];
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- ������ ������ ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = DLG_TEXT_BASE[270];
			link.l1 = DLG_TEXT_BASE[271];
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = DLG_TEXT_BASE[272];
				link.l1 = DLG_TEXT_BASE[273];
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[274]+ GetSexPhrase(DLG_TEXT_BASE[275],DLG_TEXT_BASE[276]) +DLG_TEXT_BASE[277];
				link.l1 = DLG_TEXT_BASE[278];
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = DLG_TEXT_BASE[279];
			link.l1 = DLG_TEXT_BASE[280];
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = DLG_TEXT_BASE[281] + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + DLG_TEXT_BASE[282];
			link.l1 = DLG_TEXT_BASE[283];
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = DLG_TEXT_BASE[284];
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = DLG_TEXT_BASE[285];
			link.l1 = DLG_TEXT_BASE[286];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//������� close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//������ ������ �� ������� close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
