#include "SD\TEXT\DIALOGS\Pirates_Shipyard.h"
// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = DLG_TEXT_SHY[0] + GetFullName(npchar) + DLG_TEXT_SHY[1];
				Link.l1 = pcharrepphrase(DLG_TEXT_SHY[2] + GetFullName(pchar) + DLG_TEXT_SHY[3],
	            DLG_TEXT_SHY[4] + GetFullName(pchar) + DLG_TEXT_SHY[5]);
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = DLG_TEXT_SHY[6];
				link.l1 = pcharrepphrase(DLG_TEXT_SHY[7],
	            DLG_TEXT_SHY[8]);
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase(DLG_TEXT_SHY[9],
	            DLG_TEXT_SHY[10]);
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = DLG_TEXT_SHY[374]+GetFullName(pchar)+DLG_TEXT_SHY[375];
				Link.l1 = DLG_TEXT_SHY[376];
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = DLG_TEXT_SHY[377];
				Link.l1 = DLG_TEXT_SHY[378];
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = DLG_TEXT_SHY[11];
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[12],
            DLG_TEXT_SHY[13]);
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase(DLG_TEXT_SHY[14],
            DLG_TEXT_SHY[15]);
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = DLG_TEXT_SHY[16];
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[17],
            DLG_TEXT_SHY[18]);
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = DLG_TEXT_SHY[19];
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[20],
            DLG_TEXT_SHY[21]);
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase(DLG_TEXT_SHY[22],
            DLG_TEXT_SHY[23]);
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = DLG_TEXT_SHY[24] + GetAddress_Form(NPChar) + "?";
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[25],DLG_TEXT_SHY[26]);
			link.l1.go = "shipyard_dlg";
            Link.l2 = DLG_TEXT_SHY[27];
			Link.l2.go = "quests"; //(перессылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = DLG_TEXT_SHY[28];
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase(DLG_TEXT_SHY[29], DLG_TEXT_SHY[30]);
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 6))
			{
				dialog.Text = DLG_TEXT_SHY[379];						
				Link.l1 = DLG_TEXT_SHY[380];
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = DLG_TEXT_SHY[381];
			}	
			link.l2 = DLG_TEXT_SHY[33];
			link.l2.go = "shipyard";
			link.l3 = DLG_TEXT_SHY[34];
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = DLG_TEXT_SHY[382];
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_full"))
			{
					link.l50 = DLG_TEXT_SHY[383];
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = DLG_TEXT_SHY[384];
					link.l50.go = "FDM_cabin_pay";
			}
			link.l9 = pcharrepphrase(DLG_TEXT_SHY[385], DLG_TEXT_SHY[35]);
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 6))
			{
				dialog.Text = RandPhraseSimple(DLG_TEXT_SHY[386],
				RandPhraseSimple(DLG_TEXT_SHY[387],
                                           DLG_TEXT_SHY[388]));
				Link.l1 = DLG_TEXT_SHY[32];
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = DLG_TEXT_SHY[389];
			}				
			link.l2 = DLG_TEXT_SHY[40];
			link.l2.go = "shipyard";
			link.l3 = DLG_TEXT_SHY[41];
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = DLG_TEXT_SHY[390];
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_full"))
			{
					link.l50 = DLG_TEXT_SHY[391];
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = DLG_TEXT_SHY[392];
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = DLG_TEXT_SHY[42];
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = DLG_TEXT_SHY[43];
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = DLG_TEXT_SHY[44];
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = DLG_TEXT_SHY[45];
			Link.l1 = RandPhraseSimple(DLG_TEXT_SHY[46], DLG_TEXT_SHY[47]);
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = DLG_TEXT_SHY[48];
			    Link.l1 = DLG_TEXT_SHY[49];
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
                    dialog.Text = DLG_TEXT_SHY[50];
			        Link.l1 = DLG_TEXT_SHY[51];
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = DLG_TEXT_SHY[393];
    			        Link.l1 = DLG_TEXT_SHY[394];
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = DLG_TEXT_SHY[395];
						Link.l1 = DLG_TEXT_SHY[396];
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = DLG_TEXT_SHY[54] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + DLG_TEXT_SHY[55];
    			    }
    			    s1 = s1 + DLG_TEXT_SHY[56];					
                    dialog.Text = s1;
					Link.l1 = DLG_TEXT_SHY[397];
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l10 = DLG_TEXT_SHY[63];
    			    Link.l10.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = DLG_TEXT_SHY[398] + shipCurHP + DLG_TEXT_SHY[399] + shipBaseHP;			
			s1 = s1 + DLG_TEXT_SHY[400]+ Matherial1 + DLG_TEXT_SHY[401] + Matherial2 + DLG_TEXT_SHY[402] + Matherial3 + DLG_TEXT_SHY[403] + Matherial4 + ".";
			s1 = s1 + DLG_TEXT_SHY[404]+ HPPrice +DLG_TEXT_SHY[405];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[406];
			if(CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = DLG_TEXT_SHY[407];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = DLG_TEXT_SHY[408];
			link.l1 = DLG_TEXT_SHY[409];
			link.l1.go = "ship_repair_HP_start";
			link.l2 = DLG_TEXT_SHY[410];
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = DLG_TEXT_SHY[411];
			    link.l1 = DLG_TEXT_SHY[412];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText",  DLG_TEXT_SHY[413] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    DLG_TEXT_SHY[414] + NPChar.Repair.Matherial1 + DLG_TEXT_SHY[415]+ NPChar.Repair.Matherial2 + DLG_TEXT_SHY[416] + NPChar.Repair.Matherial3 + DLG_TEXT_SHY[417] + NPChar.Repair.Matherial4 + 
				DLG_TEXT_SHY[418] + NPChar.Repair.Money + DLG_TEXT_SHY[419]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple(DLG_TEXT_SHY[420],DLG_TEXT_SHY[421]);
				link.l1 = DLG_TEXT_SHY[422];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = DLG_TEXT_SHY[423];
			link.l1 = DLG_TEXT_SHY[424];
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText",  DLG_TEXT_SHY[425] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    DLG_TEXT_SHY[426] + NPChar.Repair.Matherial1 + DLG_TEXT_SHY[427]+ NPChar.Repair.Matherial2 + DLG_TEXT_SHY[428] + NPChar.Repair.Matherial3 + DLG_TEXT_SHY[429] + NPChar.Repair.Matherial4 + 
				DLG_TEXT_SHY[430] + NPChar.Repair.Money + DLG_TEXT_SHY[431]);
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = DLG_TEXT_SHY[432];
			    Link.l1 = DLG_TEXT_SHY[433];
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = DLG_TEXT_SHY[434];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = DLG_TEXT_SHY[435];
			    Link.l1 = DLG_TEXT_SHY[436];
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = DLG_TEXT_SHY[437];
			    link.l1 = DLG_TEXT_SHY[438];
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = DLG_TEXT_SHY[439]+ sti(NPChar.Repair.Matherial1) + DLG_TEXT_SHY[440]+ sti(NPChar.Repair.Matherial2) + DLG_TEXT_SHY[441] + NPChar.Repair.Matherial3 + DLG_TEXT_SHY[442] + NPChar.Repair.Matherial4 + DLG_TEXT_SHY[443];
				link.l1 = DLG_TEXT_SHY[444];
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", DLG_TEXT_SHY[445]+ NPChar.Repair.Matherial1 + DLG_TEXT_SHY[446]+ NPChar.Repair.Matherial2 + DLG_TEXT_SHY[447] + NPChar.Repair.Matherial3 + DLG_TEXT_SHY[448] + NPChar.Repair.Matherial4 + ".");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = DLG_TEXT_SHY[449];
			Link.l1 = DLG_TEXT_SHY[450];
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[295], DLG_TEXT_SHY[296]), DLG_TEXT_SHY[297], DLG_TEXT_SHY[298],
                          DLG_TEXT_SHY[299], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[300], DLG_TEXT_SHY[301]), DLG_TEXT_SHY[302],
                      DLG_TEXT_SHY[303], DLG_TEXT_SHY[304], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = DLG_TEXT_SHY[305];
				link.l2.go = "Step_Door_1";
			}
			if (pchar.questTemp.BlueBird == "toSeekBermudes") //шебека —ин€€ ѕтица
			{
				link.l1 = DLG_TEXT_SHY[306];
				link.l1.go = "BlueBird_1";
			}
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = DLG_TEXT_SHY[451];
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = DLG_TEXT_SHY[452];
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = DLG_TEXT_SHY[453]+npchar.name+DLG_TEXT_SHY[454];
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = DLG_TEXT_SHY[455];
			s1 = DLG_TEXT_SHY[456];
			s1 = s1 + DLG_TEXT_SHY[457];
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = DLG_TEXT_SHY[458];
			s1 = s1 + DLG_TEXT_SHY[459] + sti(pchar.questTemp.different.GiveShipLetters.price5) + DLG_TEXT_SHY[460];
			dialog.text = s1;
			link.l1 = DLG_TEXT_SHY[461];
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = DLG_TEXT_SHY[462];
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = DLG_TEXT_SHY[343];
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = DLG_TEXT_SHY[344];
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = DLG_TEXT_SHY[345];
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = DLG_TEXT_SHY[346];
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = DLG_TEXT_SHY[347];
			link.l1 = DLG_TEXT_SHY[348] + npchar.name + "...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = DLG_TEXT_SHY[349];
			link.l1 = DLG_TEXT_SHY[350];
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Алекса ----------------------------------------------
		case "clock_begin":
			dialog.text = DLG_TEXT_SHY[463];
			link.l1 = DLG_TEXT_SHY[464];
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = DLG_TEXT_SHY[465]+sTotalTemp+DLG_TEXT_SHY[466]+DLG_TEXT_SHY[467];
			link.l1 = DLG_TEXT_SHY[468]+sTotalTemp+DLG_TEXT_SHY[469];
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = DLG_TEXT_SHY[470];
			link.l1 = DLG_TEXT_SHY[471];
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = DLG_TEXT_SHY[472]+sTotalTemp+DLG_TEXT_SHY[473]+sTotalTemp+DLG_TEXT_SHY[474];
			link.l1 = DLG_TEXT_SHY[475]+sTotalTemp+DLG_TEXT_SHY[476];
			link.l1.go = "clock_exit";
			link.l2 = DLG_TEXT_SHY[477]+sTotalTemp+DLG_TEXT_SHY[478];
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = DLG_TEXT_SHY[479];
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = DLG_TEXT_SHY[480];
			link.l1 = DLG_TEXT_SHY[481];
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = DLG_TEXT_SHY[482];
			link.l1 = DLG_TEXT_SHY[483];
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = DLG_TEXT_SHY[484];
			link.l1 = DLG_TEXT_SHY[485];
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = DLG_TEXT_SHY[486];
			link.l1 = DLG_TEXT_SHY[487];
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 200;
			pchar.questTemp.AlexClock.Oil = 250;
			pchar.questTemp.AlexClock.Shipsilk = 220;
			pchar.questTemp.AlexClock.Ropes = 180;
		break;
		
		case "clock":
			dialog.text = DLG_TEXT_SHY[488];
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = DLG_TEXT_SHY[489]+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = DLG_TEXT_SHY[490]+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = DLG_TEXT_SHY[491]+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = DLG_TEXT_SHY[492]+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = DLG_TEXT_SHY[493];
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = DLG_TEXT_SHY[494];
				link.l1 = DLG_TEXT_SHY[495];
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = DLG_TEXT_SHY[496];
				link.l1 = DLG_TEXT_SHY[497];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_SHY[498];
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iTemp = amount-iSan;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 35*iSan;
				dialog.text = DLG_TEXT_SHY[499]+FindRussianQtyString(amount)+DLG_TEXT_SHY[500]+FindRussianQtyString(iSan)+DLG_TEXT_SHY[501]+FindRussianQtyString(iTemp)+DLG_TEXT_SHY[502]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[503];
				link.l1 = DLG_TEXT_SHY[504];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "бакаута");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 35*amount;
				dialog.text = DLG_TEXT_SHY[505]+FindRussianQtyString(amount)+DLG_TEXT_SHY[506]+FindRussianQtyString(iSan)+DLG_TEXT_SHY[507]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[508];
				link.l1 = DLG_TEXT_SHY[509];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "бакаута");
			}
			TakeNItems(pchar, "gold_dublon", iSum);
			Log_Info(DLG_TEXT_SHY[510]+FindRussianDublonString(iSum)+"");
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iTemp = amount-iOil;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 12*iOil;
				dialog.text = DLG_TEXT_SHY[511]+FindRussianQtyString(amount)+DLG_TEXT_SHY[512]+FindRussianQtyString(iOil)+DLG_TEXT_SHY[513]+FindRussianQtyString(iTemp)+DLG_TEXT_SHY[514]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[515];
				link.l1 = DLG_TEXT_SHY[516];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "смол");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 12*amount;
				dialog.text = DLG_TEXT_SHY[517]+FindRussianQtyString(amount)+DLG_TEXT_SHY[518]+FindRussianQtyString(iOil)+DLG_TEXT_SHY[519]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[520];
				link.l1 = DLG_TEXT_SHY[521];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "смол");
			}
			TakeNItems(pchar, "gold_dublon", iSum);
			Log_Info(DLG_TEXT_SHY[522]+FindRussianDublonString(iSum)+"");
		break;
		
		case "shipsilk": // шелк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iTemp = amount-iSil;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 24*iSil;
				dialog.text = DLG_TEXT_SHY[523]+FindRussianQtyString(amount)+DLG_TEXT_SHY[524]+FindRussianQtyString(iSil)+DLG_TEXT_SHY[525]+FindRussianQtyString(iTemp)+DLG_TEXT_SHY[526]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[527];
				link.l1 = DLG_TEXT_SHY[528];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "шелка");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 24*amount;
				dialog.text = DLG_TEXT_SHY[529]+FindRussianQtyString(amount)+DLG_TEXT_SHY[530]+FindRussianQtyString(iSil)+DLG_TEXT_SHY[531]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[532];
				link.l1 = DLG_TEXT_SHY[533];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "шелка");
			}
			TakeNItems(pchar, "gold_dublon", iSum);
			Log_Info(DLG_TEXT_SHY[534]+FindRussianDublonString(iSum)+"");
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iTemp = amount-iRop;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 13*iRop;
				dialog.text = DLG_TEXT_SHY[535]+FindRussianQtyString(amount)+DLG_TEXT_SHY[536]+FindRussianQtyString(iRop)+DLG_TEXT_SHY[537]+FindRussianQtyString(iTemp)+DLG_TEXT_SHY[538]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[539];
				link.l1 = DLG_TEXT_SHY[540];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "канатов");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 13*amount;
				dialog.text = DLG_TEXT_SHY[541]+FindRussianQtyString(amount)+DLG_TEXT_SHY[542]+FindRussianQtyString(iRop)+DLG_TEXT_SHY[543]+FindRussianDublonString(iSum)+DLG_TEXT_SHY[544];
				link.l1 = DLG_TEXT_SHY[545];
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "канатов");
			}
			TakeNItems(pchar, "gold_dublon", iSum);
			Log_Info(DLG_TEXT_SHY[546]+FindRussianDublonString(iSum)+"");
		break;
		
		case "clock_2":
			dialog.text = DLG_TEXT_SHY[547];
			link.l1 = DLG_TEXT_SHY[548];
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = DLG_TEXT_SHY[549];
			link.l1 = DLG_TEXT_SHY[550];
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = DLG_TEXT_SHY[551];
			link.l1 = DLG_TEXT_SHY[552];
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = DLG_TEXT_SHY[553]+DLG_TEXT_SHY[554];
			link.l1 = DLG_TEXT_SHY[555];
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = DLG_TEXT_SHY[556];
			link.l1 = DLG_TEXT_SHY[557];
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = DLG_TEXT_SHY[558];
			link.l1 = DLG_TEXT_SHY[559];
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = DLG_TEXT_SHY[560];
			link.l1 = DLG_TEXT_SHY[561];
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = DLG_TEXT_SHY[562];
			link.l1 = DLG_TEXT_SHY[563];
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = DLG_TEXT_SHY[564]+DLG_TEXT_SHY[565];
			link.l1 = DLG_TEXT_SHY[566];
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info(DLG_TEXT_SHY[567]);
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_SHY[568];
			link.l1 = DLG_TEXT_SHY[569];
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = DLG_TEXT_SHY[570];
			link.l1 = DLG_TEXT_SHY[571];
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = DLG_TEXT_SHY[572];
			link.l1 = DLG_TEXT_SHY[573];
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = DLG_TEXT_SHY[574];
			link.l1 = DLG_TEXT_SHY[575];
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = DLG_TEXT_SHY[576];
			link.l1 = DLG_TEXT_SHY[577];
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			dialog.text = DLG_TEXT_SHY[578];
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = DLG_TEXT_SHY[579];
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = DLG_TEXT_SHY[580];
				link.l2.go = "FDM_sails";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = DLG_TEXT_SHY[581];
			link.l1 = DLG_TEXT_SHY[582];
			link.l1.go = "FDM_cabin_m";
			link.l2 = DLG_TEXT_SHY[583];
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = DLG_TEXT_SHY[584];
			link.l1 = DLG_TEXT_SHY[585];
			link.l1.go = "FDM_cabin_m1";
			link.l2 = DLG_TEXT_SHY[586];
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = DLG_TEXT_SHY[587];
			link.l1 = DLG_TEXT_SHY[588];
			link.l1.go = "FDM_cabin_s1";
			link.l2 = DLG_TEXT_SHY[589];
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = DLG_TEXT_SHY[590];
			if (iTemp > 0)
			{
				link.l1 = DLG_TEXT_SHY[591]+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = DLG_TEXT_SHY[592];
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = DLG_TEXT_SHY[593];
			if (iTemp > 0)
			{
				link.l1 = DLG_TEXT_SHY[594]+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = DLG_TEXT_SHY[595];
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info(DLG_TEXT_SHY[596]);
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = DLG_TEXT_SHY[597]+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+DLG_TEXT_SHY[598]+FindRussianQtyString(iTemp)+DLG_TEXT_SHY[599];
				link.l1 = DLG_TEXT_SHY[600];
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = DLG_TEXT_SHY[601]+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+DLG_TEXT_SHY[602]+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+DLG_TEXT_SHY[603];
				link.l1 = DLG_TEXT_SHY[604];
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam(GetConvertStr("Shipyard_1", "SetLaunchFrameFormParam.txt")+ NewStr() +GetConvertStr("Shipyard_2", "SetLaunchFrameFormParam.txt"), "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = DLG_TEXT_SHY[607];
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = DLG_TEXT_SHY[608];
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = DLG_TEXT_SHY[609];
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = DLG_TEXT_SHY[610];
			link.l1 = DLG_TEXT_SHY[611];
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam(GetConvertStr("Shipyard_3", "SetLaunchFrameFormParam.txt")+ NewStr() +GetConvertStr("Shipyard_4", "SetLaunchFrameFormParam.txt"), "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		
				case "BlueBird_1":
			dialog.text = DLG_TEXT_SHY[335];
			link.l1 = DLG_TEXT_SHY[336];
			link.l1.go = "BlueBird_2";
		break;
		case "BlueBird_2":
			dialog.text = DLG_TEXT_SHY[337];
			link.l1 = DLG_TEXT_SHY[338];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_SHY[339];
			link.l1 = DLG_TEXT_SHY[340];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_SHY[341];
			link.l1 = DLG_TEXT_SHY[342];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "5");
			pchar.questTemp.BlueBird = "toCavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1 = "locator";
			pchar.quest.BlueBird_inCavern.win_condition.l1.location = "Bermudes_Cavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator_group = "quest";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator = "BlueBird";
			pchar.quest.BlueBird_inCavern.function = "BlueBird_inCavern";
			LAi_LocationDisableMonstersGen("Bermudes_Cavern", true); //монстров не генерить
			LAi_LocationDisableOfficersGen("Bermudes_Cavern", true); //офицеров не пускать
		break;	
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}
