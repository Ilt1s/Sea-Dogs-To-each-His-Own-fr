// общий диалог ростовщиков
#include "SD\TEXT\DIALOGS\Common_usurer.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text =DLG_TEXT_BASE[340] + pchar.name + DLG_TEXT_BASE[341];
					link.l1 = DLG_TEXT_BASE[342];
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = DLG_TEXT_BASE[343];
				Link.l1 = DLG_TEXT_BASE[344];
				Link.l1.go = "quests";
				Link.l2 = DLG_TEXT_BASE[345];
				Link.l2.go = "sharlie_credit";
				Link.l3 = DLG_TEXT_BASE[346];
				Link.l3.go = "exit";
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = DLG_TEXT_BASE[347]+DLG_TEXT_BASE[348];
				Link.l1 = DLG_TEXT_BASE[349];
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = DLG_TEXT_BASE[350];
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = DLG_TEXT_BASE[351];
				Link.l1 = DLG_TEXT_BASE[352];
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text =DLG_TEXT_BASE[353];
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = DLG_TEXT_BASE[354];
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = DLG_TEXT_BASE[355];
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = DLG_TEXT_BASE[356];
				link.l1 = DLG_TEXT_BASE[357];
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = DLG_TEXT_BASE[358] + GetFullName(npchar) + DLG_TEXT_BASE[359];
				link.l1 = DLG_TEXT_BASE[360];
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = DLG_TEXT_BASE[989];
				link.l1.go = "FMQG_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[361]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[362],DLG_TEXT_BASE[363]+GetFullName(npchar)+DLG_TEXT_BASE[364],DLG_TEXT_BASE[365]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[366]), LinkRandPhrase(DLG_TEXT_BASE[367]+GetFullName(npchar)+DLG_TEXT_BASE[368],DLG_TEXT_BASE[369]+GetFullName(npchar)+DLG_TEXT_BASE[370],DLG_TEXT_BASE[371]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[372]+GetFullName(npchar)+DLG_TEXT_BASE[373]), LinkRandPhrase(DLG_TEXT_BASE[374]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[375]+GetFullName(npchar)+DLG_TEXT_BASE[376],DLG_TEXT_BASE[377],DLG_TEXT_BASE[378]));
				link.l1 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[379],DLG_TEXT_BASE[380]+GetFullName(pchar)+DLG_TEXT_BASE[381],""+GetFullName(pchar)+DLG_TEXT_BASE[382]+pchar.ship.name+DLG_TEXT_BASE[383]), RandPhraseSimple(DLG_TEXT_BASE[384]+GetFullName(pchar)+DLG_TEXT_BASE[385]+pchar.ship.name+DLG_TEXT_BASE[386],DLG_TEXT_BASE[387]+GetFullName(pchar)+DLG_TEXT_BASE[388]));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[389]+GetAddress_Form(NPChar)+" ?",DLG_TEXT_BASE[390],DLG_TEXT_BASE[391]),LinkRandPhrase(DLG_TEXT_BASE[392],DLG_TEXT_BASE[393],DLG_TEXT_BASE[394]+GetFullName(pchar)+DLG_TEXT_BASE[395]),LinkRandPhrase(DLG_TEXT_BASE[396]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[397],DLG_TEXT_BASE[398]+GetFullName(pchar)+DLG_TEXT_BASE[399],DLG_TEXT_BASE[400]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[401])),LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[402]+GetFullName(pchar)+DLG_TEXT_BASE[403],DLG_TEXT_BASE[404]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[405],DLG_TEXT_BASE[406]+GetFullName(pchar)+DLG_TEXT_BASE[407]),LinkRandPhrase(DLG_TEXT_BASE[408]+GetFullName(pchar)+DLG_TEXT_BASE[409],DLG_TEXT_BASE[410],DLG_TEXT_BASE[411]+GetFullName(pchar)+DLG_TEXT_BASE[412]),LinkRandPhrase(DLG_TEXT_BASE[413],DLG_TEXT_BASE[414]+GetFullName(pchar)+DLG_TEXT_BASE[415],DLG_TEXT_BASE[416])));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[417],DLG_TEXT_BASE[418],DLG_TEXT_BASE[419]), LinkRandPhrase(DLG_TEXT_BASE[420],DLG_TEXT_BASE[421],DLG_TEXT_BASE[422])),
				RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[423],DLG_TEXT_BASE[424],DLG_TEXT_BASE[425]),LinkRandPhrase(DLG_TEXT_BASE[426],DLG_TEXT_BASE[427],DLG_TEXT_BASE[428])));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[27] + GetAddress_Form(npchar) + DLG_TEXT_BASE[28], 
				DLG_TEXT_BASE[29] + GetAddress_Form(npchar) + DLG_TEXT_BASE[30], 
				DLG_TEXT_BASE[31] + GetAddress_Form(npchar) + DLG_TEXT_BASE[32],
                DLG_TEXT_BASE[33] + GetAddress_Form(npchar) + DLG_TEXT_BASE[34] , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[35], 
				DLG_TEXT_BASE[36],
                DLG_TEXT_BASE[37], 
				DLG_TEXT_BASE[38], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[39];
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = DLG_TEXT_BASE[429];
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = DLG_TEXT_BASE[40];
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = DLG_TEXT_BASE[430]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple(DLG_TEXT_BASE[43] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[44]);
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = DLG_TEXT_BASE[431]; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = DLG_TEXT_BASE[432];
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(npchar, "quest.noblelombard"))
			{
				link.l11 = DLG_TEXT_BASE[433]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[434];
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = DLG_TEXT_BASE[435]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[436]+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = DLG_TEXT_BASE[437];
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[438] + NPChar.name + DLG_TEXT_BASE[439];
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[440] + NPChar.name + DLG_TEXT_BASE[441];
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[442] + NPChar.name + DLG_TEXT_BASE[443];
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[444];
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[445];
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[446] + npchar.name + DLG_TEXT_BASE[447];
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[448];
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[449] + npchar.name + DLG_TEXT_BASE[450];
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[451] + npchar.name + DLG_TEXT_BASE[452];
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[453] + npchar.name + DLG_TEXT_BASE[454];
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[455] + npchar.name + DLG_TEXT_BASE[456];
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[457] + npchar.name + DLG_TEXT_BASE[458];
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + DLG_TEXT_BASE[459];
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + DLG_TEXT_BASE[460];
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[461] + npchar.name + DLG_TEXT_BASE[462];
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + DLG_TEXT_BASE[463];
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + DLG_TEXT_BASE[464];
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = DLG_TEXT_BASE[465] + npchar.name + DLG_TEXT_BASE[466];
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = DLG_TEXT_BASE[467];
			link.l1 = DLG_TEXT_BASE[468];
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = DLG_TEXT_BASE[469];
			link.l1 = DLG_TEXT_BASE[470];
			link.l1.go = "items";
			link.l2 = DLG_TEXT_BASE[471];
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = DLG_TEXT_BASE[472];
			link.l1 = DLG_TEXT_BASE[473] + sti(pchar.questTemp.different.GiveShipLetters.price1) + DLG_TEXT_BASE[474];
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = DLG_TEXT_BASE[475];
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = DLG_TEXT_BASE[476];
				link.l1 = DLG_TEXT_BASE[477];
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = DLG_TEXT_BASE[478];
				dialog.text = s1 +" "+ DLG_TEXT_BASE[479];
				link.l1 = DLG_TEXT_BASE[480];
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = DLG_TEXT_BASE[481];
				dialog.text = s1 +" "+ DLG_TEXT_BASE[482];
				link.l1 = DLG_TEXT_BASE[483];
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = DLG_TEXT_BASE[484];
			link.l1 = DLG_TEXT_BASE[485];
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = DLG_TEXT_BASE[486];
			link.l1 = DLG_TEXT_BASE[487];
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = DLG_TEXT_BASE[488];
			dialog.text = s1 +" "+ DLG_TEXT_BASE[489];
			link.l1 = DLG_TEXT_BASE[490];
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = DLG_TEXT_BASE[491];
				link.l1 = DLG_TEXT_BASE[492];
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[493];
				link.l1 = DLG_TEXT_BASE[494];
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = DLG_TEXT_BASE[495];
			link.l1 = DLG_TEXT_BASE[496];
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = DLG_TEXT_BASE[497];
			link.l1 = DLG_TEXT_BASE[498];
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
			dialog.text = DLG_TEXT_BASE[499];
			link.l1 = DLG_TEXT_BASE[500];
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer": 
			dialog.text = DLG_TEXT_BASE[100];
		//	link.l1 = DLG_TEXT_BASE[101];
		//	link.l1.go = "Loan_GiveWork"; //patch
			//найти должника
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
            {
                link.l2 = DLG_TEXT_BASE[102];;
                link.l2.go = "FindCitizen_1";
            }
			//доставить сундук
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
            {
                link.l3 = DLG_TEXT_BASE[103];;
                link.l3.go = "TakeChest_1";
            }
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l4 = DLG_TEXT_BASE[104];;
                link.l4.go = "TakeChest_2";
            }
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = DLG_TEXT_BASE[105]+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(DLG_TEXT_BASE[106], DLG_TEXT_BASE[107], DLG_TEXT_BASE[108]);
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase(DLG_TEXT_BASE[109], DLG_TEXT_BASE[110], DLG_TEXT_BASE[111]);
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase(DLG_TEXT_BASE[112],DLG_TEXT_BASE[113], DLG_TEXT_BASE[501]); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = DLG_TEXT_BASE[114];
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase(DLG_TEXT_BASE[115], DLG_TEXT_BASE[116], DLG_TEXT_BASE[502]);
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase(DLG_TEXT_BASE[503], DLG_TEXT_BASE[504], DLG_TEXT_BASE[117]);
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = LinkRandPhrase(DLG_TEXT_BASE[118], DLG_TEXT_BASE[119], DLG_TEXT_BASE[120]);
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = DLG_TEXT_BASE[121];
				link.l11.go = "exit";
			}
		break;
		//даем или не даем работу - сундуки и должники
		case "Loan_GiveWork": 
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + DLG_TEXT_BASE[122] + GetFullName(pchar)+ DLG_TEXT_BASE[123] +
                              RandPhraseSimple(DLG_TEXT_BASE[124],DLG_TEXT_BASE[125]) + DLG_TEXT_BASE[126];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[127], RandSwear() + DLG_TEXT_BASE[128]);
				link.l1.go = "exit";
                break;
            }
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//при низком авторитете не даем
			{
				dialog.text = DLG_TEXT_BASE[129];
				link.l9 = DLG_TEXT_BASE[145];
				link.l9.go = "exit";
				break;
			}
            dialog.text = DLG_TEXT_BASE[129];

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
                npchar.quest.trade_date = lastspeak_date;
                iNum = rand(1);
                if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
                {
                    iNum = 0; // всегда первый
                }
                switch (iNum)
                {
                    case 0 : // найти должника
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;
                        
                        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
                        {
                            iNum = findCitizenMan(Npchar, true);
                            npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // значит на суше без корабля
                        }
                        else
                        {
                            iNum = findCitizenMan(Npchar, false);
                        }
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.Loan.FindCitizenMoney   = (7 + cRand(sti(PChar.rank)))*1000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*200 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
                            pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3+rand(2)));
                            pchar.GenQuest.Loan.FindCitizenIdx  =  iNum;
							pchar.GenQuest.Loan.FindCitizenChance1 = rand(2);
							pchar.GenQuest.Loan.FindCitizenChance2 = rand(1);
							pchar.GenQuest.Loan.FindCitizenChance3 = rand(1);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = DLG_TEXT_BASE[130] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = DLG_TEXT_BASE[131]+
                                     GetFullName(chr) + DLG_TEXT_BASE[132] + XI_ConvertString("Colony"+chr.city+"Dat") + sTemp + DLG_TEXT_BASE[133] + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)) +
                                     DLG_TEXT_BASE[134] + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)) + ".";
                            link.l1 = DLG_TEXT_BASE[135];
                			link.l1.go = "LoanUsurer_GiveWork_1";
            			}
                    break;

                    case 1: // доставить сундуки
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;
                        
                        iNum = findChestMan(Npchar);
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.LoanChest.Chest      = 2 + drand(2);
                            pchar.GenQuest.LoanChest.Money      = (3 + cRand(sti(pchar.GenQuest.LoanChest.Chest)))*400 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*250;
                            pchar.GenQuest.LoanChest.TargetIdx  =  iNum;
                            pchar.GenQuest.LoanChest.Time       = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = DLG_TEXT_BASE[136] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = DLG_TEXT_BASE[137] + pchar.GenQuest.LoanChest.Chest + 
									DLG_TEXT_BASE[138]+ XI_ConvertString("Colony"+chr.city+"Acc") + sTemp + DLG_TEXT_BASE[139] +
									GetFullName(chr) + DLG_TEXT_BASE[140] + GetWorkTypeOfMan(chr, "") +
									DLG_TEXT_BASE[141] + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)) + DLG_TEXT_BASE[142] + FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)) + ".";
                            link.l1 = DLG_TEXT_BASE[143];
                			link.l1.go = "LoanUsurer_ChestWork_1";
            			}
                     break;
    			}
    		}
            else
            {
                dialog.text = DLG_TEXT_BASE[144];
            }
            link.l9 = DLG_TEXT_BASE[145];
		    link.l9.go = "exit";
		break;
		//============== boal нахождение должника ===============
		case "LoanUsurer_GiveWork_1":
            pchar.GenQuest.Loan.FindCitizen = true;
            pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
            dialog.text = DLG_TEXT_BASE[146];
			link.l9 = DLG_TEXT_BASE[147];
			link.l9.go = "exit";		
            chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];     
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = DLG_TEXT_BASE[148] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
            AddQuestRecord("Gen_LoanFindCitizen", "1");
            AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
            AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony"+chr.city+"Dat") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //проверка выполнения квеста
            dialog.text = DLG_TEXT_BASE[149];
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
            {
                link.l1 = DLG_TEXT_BASE[150];
                link.l1.go = "finish_work";
                link.l2 = DLG_TEXT_BASE[151];
                if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
                {
                    link.l2.go = "finish_work_bad";
                }
                else
                {
                    link.l2.go = "finish_work_lie";
                }
            }

            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                link.l1 = DLG_TEXT_BASE[152];
                link.l1.go = "finish_work_bad";
            }
            link.l3 = DLG_TEXT_BASE[153];
            link.l3.go = "finish_work_cancel";
            link.l9 = DLG_TEXT_BASE[154];
			link.l9.go = "exit";
            
		break; 

		case "finish_work":
            if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
            {
                dialog.text = DLG_TEXT_BASE[155];
    			link.l9 = DLG_TEXT_BASE[156];
    			link.l9.go = "exit";
    			AddMoneyToCharacter(Pchar, -1*sti(pchar.GenQuest.Loan.FindCitizenMoney));
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
    			ChangeCharacterComplexReputation(pchar,"nobility", 1);
    			OfficersReaction("good");    			
    			AddQuestRecord("Gen_LoanFindCitizen", "4");
                CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
			    dialog.text = DLG_TEXT_BASE[157];
    			link.l9 = DLG_TEXT_BASE[158];
    			link.l9.go = "exit";
    		}
		break;
		
		case "finish_work_bad":
            dialog.text = DLG_TEXT_BASE[159];
			link.l9 = DLG_TEXT_BASE[160];
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
			AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase(" tried"," tried"));
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;
		
		case "finish_work_cancel":
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                dialog.text = DLG_TEXT_BASE[161];
                link.l1 = DLG_TEXT_BASE[162];
    			link.l1.go = "finish_work";
    			link.l2 = DLG_TEXT_BASE[163];
    			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
    			   link.l2.go = "finish_work_bad";
    			}
    			else
    			{
    			   link.l2.go = "finish_work_bad_2";
    			}
    			
			}
            else
            {
                ChangeCharacterComplexReputation(pchar,"nobility", -1);
                dialog.text = DLG_TEXT_BASE[165];
                link.l1 = DLG_TEXT_BASE[166];
    			link.l1.go = "exit";
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddQuestRecord("Gen_LoanFindCitizen", "6");
				AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("tried","tried"));
                CloseQuestHeader("Gen_LoanFindCitizen");
            }
		break;
		
		case "finish_work_bad_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
            dialog.text = DLG_TEXT_BASE[167];
			link.l1 = DLG_TEXT_BASE[505];
    		link.l1.go = "finish_work_hanter";
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
				link.l2 = DLG_TEXT_BASE[168];
				link.l2.go = "finish_work";
			}
		break;
		
		case "finish_work_lie":
            dialog.text = DLG_TEXT_BASE[169];
            link.l1 = DLG_TEXT_BASE[170];
    		link.l1.go = "finish_work_cancel";
		break;

		case "finish_work_hanter":
            dialog.text = DLG_TEXT_BASE[506];
            link.l1 = DLG_TEXT_BASE[507];
    		link.l1.go = "exit";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 40);
			DeleteAttribute(pchar, "GenQuest.Loan");
    		DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    		AddQuestRecord("Gen_LoanFindCitizen", "7");
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		//============== boal доставка сундуков ===============
		case "LoanUsurer_ChestWork_1": 
            pchar.GenQuest.LoanChest.TakeChest = true;
            pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
            dialog.text = DLG_TEXT_BASE[171];
			link.l9 = DLG_TEXT_BASE[172];
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// немного веселой жизни
            TraderHunterOnMap();
            chr  = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = DLG_TEXT_BASE[173] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
            AddQuestRecord("Gen_LoanTakeChest", "1");
            AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", pchar.GenQuest.LoanChest.Chest);
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony"+chr.city+"Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
            dialog.text = DLG_TEXT_BASE[174];
            link.l1 = DLG_TEXT_BASE[175];
            link.l1.go = "TakeChestFinish_work_cancel";
            link.l9 = DLG_TEXT_BASE[176];
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                ChangeCharacterComplexReputation(pchar,"nobility", -1);
                dialog.text = DLG_TEXT_BASE[177];
                link.l1 = DLG_TEXT_BASE[178];
    			link.l1.go = "exit";
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
                AddQuestRecord("Gen_LoanTakeChest", "5");
				AddQuestUserData("Gen_LoanTakeChest", "sSex", GetSexPhrase("tried","tried"));
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[179];
                link.l1 = DLG_TEXT_BASE[180];
    			link.l1.go = "Exit";
			}
		break;
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = DLG_TEXT_BASE[181];			
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = DLG_TEXT_BASE[182];
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = DLG_TEXT_BASE[508];
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = DLG_TEXT_BASE[183];
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + DLG_TEXT_BASE[184] + GetFullName(pchar)+ DLG_TEXT_BASE[185] +
                              RandPhraseSimple(DLG_TEXT_BASE[186],DLG_TEXT_BASE[187]) + DLG_TEXT_BASE[188];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[189], RandSwear() + DLG_TEXT_BASE[190]);
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = DLG_TEXT_BASE[191];
			Link.l1 = DLG_TEXT_BASE[192];
			Link.l1.go = "Small";
			Link.l2 = DLG_TEXT_BASE[193];
			Link.l2.go = "Medium";
			Link.l3 = DLG_TEXT_BASE[194];
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = DLG_TEXT_BASE[195] + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = DLG_TEXT_BASE[196];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT_BASE[197];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT_BASE[198];
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = DLG_TEXT_BASE[199] + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + DLG_TEXT_BASE[200];
			Link.l1 = DLG_TEXT_BASE[201];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT_BASE[202];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT_BASE[203];
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = DLG_TEXT_BASE[204] + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + DLG_TEXT_BASE[205];
			Link.l1 = DLG_TEXT_BASE[206];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT_BASE[207];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT_BASE[208];
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + DLG_TEXT_BASE[209]; 
			Link.l1 = DLG_TEXT_BASE[210];
			Link.l1.go = "Period";
			Link.l3 = DLG_TEXT_BASE[211];
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  DLG_TEXT_BASE[212] + Pchar.name + DLG_TEXT_BASE[213] + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + DLG_TEXT_BASE[214]; 
			Link.l1 = DLG_TEXT_BASE[215];
			Link.l1.go = "LoanGranted";
			Link.l3 = DLG_TEXT_BASE[216];
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = DLG_TEXT_BASE[217];
			Link.l1 = DLG_TEXT_BASE[218];
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = DLG_TEXT_BASE[219];
			Link.l1 = DLG_TEXT_BASE[220];
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[221], DLG_TEXT_BASE[222],  DLG_TEXT_BASE[223] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[224]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[225], DLG_TEXT_BASE[226], DLG_TEXT_BASE[227]);
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[228],DLG_TEXT_BASE[229], DLG_TEXT_BASE[230]);
				Link.l2.go = "deposit";						
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = DLG_TEXT_BASE[509];
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = DLG_TEXT_BASE[231] + NPchar.name + ".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[232], DLG_TEXT_BASE[233], DLG_TEXT_BASE[234]);
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = DLG_TEXT_BASE[235];
				link.l1 = DLG_TEXT_BASE[236];
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = DLG_TEXT_BASE[237];
				link.l1 = DLG_TEXT_BASE[238];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[239] + Pchar.QuestTemp.Deposits.(NPC_Area).Interest + DLG_TEXT_BASE[240];
			Link.l1 = DLG_TEXT_BASE[241];
			Link.l1.go = "Deposit_placed";
			Link.l2 = DLG_TEXT_BASE[242];
			Link.l2.go = "Deposit";
			Link.l3 = DLG_TEXT_BASE[243];
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = DLG_TEXT_BASE[510] +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = DLG_TEXT_BASE[246];
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[247];
				Link.l1 = DLG_TEXT_BASE[248];
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = DLG_TEXT_BASE[249] + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)) + DLG_TEXT_BASE[250];
			Link.l1 = DLG_TEXT_BASE[251];		
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = DLG_TEXT_BASE[511];			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = DLG_TEXT_BASE[252];			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = DLG_TEXT_BASE[512];
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = DLG_TEXT_BASE[513];			
				link.l1 = DLG_TEXT_BASE[514];	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = DLG_TEXT_BASE[515];			
				link.l1 = DLG_TEXT_BASE[516];	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = DLG_TEXT_BASE[517];			
				link.l1 = DLG_TEXT_BASE[518];	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = DLG_TEXT_BASE[519];			
			link.l1 = DLG_TEXT_BASE[520];	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с нее, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[253];			
			Link.l1 = DLG_TEXT_BASE[254];			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[521], DLG_TEXT_BASE[522], DLG_TEXT_BASE[523]);
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = DLG_TEXT_BASE[524];
				link.l1 = DLG_TEXT_BASE[525];
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = DLG_TEXT_BASE[526];
				link.l1 = DLG_TEXT_BASE[527];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[528] + Pchar.QuestTemp.Deposits.(sDepositType2).Interest + DLG_TEXT_BASE[529];
			Link.l1 = DLG_TEXT_BASE[530];
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = DLG_TEXT_BASE[531];
			Link.l2.go = "Deposit_dub";
			Link.l3 = DLG_TEXT_BASE[532];
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = DLG_TEXT_BASE[533] +
						FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = DLG_TEXT_BASE[534];
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[535];
				Link.l1 = DLG_TEXT_BASE[536];
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = DLG_TEXT_BASE[537] + FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result)) + DLG_TEXT_BASE[538];
			Link.l1 = DLG_TEXT_BASE[539];			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = DLG_TEXT_BASE[540];			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = DLG_TEXT_BASE[541];			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = DLG_TEXT_BASE[542];
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = DLG_TEXT_BASE[543];			
				link.l1 = DLG_TEXT_BASE[544];	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = DLG_TEXT_BASE[545];			
				link.l1 = DLG_TEXT_BASE[546];	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = DLG_TEXT_BASE[547];			
				link.l1 = DLG_TEXT_BASE[548];	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = DLG_TEXT_BASE[549];			
			link.l1 = DLG_TEXT_BASE[550];	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с нее, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[551];			
			Link.l1 = DLG_TEXT_BASE[552];			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[255];
            Link.l1 = DLG_TEXT_BASE[256];
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[257], DLG_TEXT_BASE[258], DLG_TEXT_BASE[259]);
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[260];				
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = DLG_TEXT_BASE[261];
			Link.l1 = DLG_TEXT_BASE[262] + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + DLG_TEXT_BASE[263];
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = DLG_TEXT_BASE[264] + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = DLG_TEXT_BASE[265];
			Link.l1 = DLG_TEXT_BASE[266];
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = DLG_TEXT_BASE[553];
			Link.l1 = DLG_TEXT_BASE[554];
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			dialog.Text = DLG_TEXT_BASE[555]+DLG_TEXT_BASE[556] + pchar.questTemp.Slavetrader.iSlaveQuantity + DLG_TEXT_BASE[557] + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + " pesos.";
			Link.l1 = DLG_TEXT_BASE[558];
			Link.l1.go = "exit_slaves";
			Link.l2 = DLG_TEXT_BASE[559];
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = DLG_TEXT_BASE[560];
			Link.l1 = DLG_TEXT_BASE[561];
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = DLG_TEXT_BASE[562];
			Link.l1 = DLG_TEXT_BASE[563];
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = DLG_TEXT_BASE[564];
            if (amount < 0)
			{
				Link.l1 = DLG_TEXT_BASE[565];
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[566];
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = DLG_TEXT_BASE[567];
			Link.l1 = DLG_TEXT_BASE[568];
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = DLG_TEXT_BASE[569];
			Link.l1 = DLG_TEXT_BASE[570];
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = DLG_TEXT_BASE[571];
			Link.l1 = DLG_TEXT_BASE[572];
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = DLG_TEXT_BASE[573];
				Link.l1 = DLG_TEXT_BASE[574];
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = DLG_TEXT_BASE[575];
				Link.l1 = DLG_TEXT_BASE[576];
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = DLG_TEXT_BASE[577] + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + DLG_TEXT_BASE[578] + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + DLG_TEXT_BASE[579] + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + DLG_TEXT_BASE[580] + pchar.questTemp.Slavetrader.ShipName + DLG_TEXT_BASE[581];
			link.l1 = DLG_TEXT_BASE[582];
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = DLG_TEXT_BASE[583] + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + DLG_TEXT_BASE[584];
			Link.l1 = DLG_TEXT_BASE[585];
            Link.l1.go = "Takeslaves_6";
			Link.l2 = DLG_TEXT_BASE[586];
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = DLG_TEXT_BASE[587] + pchar.questTemp.Slavetrader.ShipName + DLG_TEXT_BASE[588];
			Link.l1 = DLG_TEXT_BASE[589];
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = DLG_TEXT_BASE[590];
			Link.l1 = DLG_TEXT_BASE[591];
            Link.l1.go = "Takeslaves_7";
			Link.l2 = DLG_TEXT_BASE[592];
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = DLG_TEXT_BASE[593];
			link.l1 = DLG_TEXT_BASE[594];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Abl"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Dat"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = DLG_TEXT_BASE[595] + GetFullName(pchar) + DLG_TEXT_BASE[5966];
			link.l1 = DLG_TEXT_BASE[597];
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = DLG_TEXT_BASE[598] + GetFullName(pchar) + DLG_TEXT_BASE[599] + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + DLG_TEXT_BASE[600];
			link.l1 = DLG_TEXT_BASE[601] + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + DLG_TEXT_BASE[602];
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = DLG_TEXT_BASE[603];
			link.l1 = DLG_TEXT_BASE[604];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = DLG_TEXT_BASE[605]+ GetSexPhrase(DLG_TEXT_BASE[606],DLG_TEXT_BASE[607]) +DLG_TEXT_BASE[608];
				link.l1 = DLG_TEXT_BASE[609] + npchar.name + " !";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = DLG_TEXT_BASE[610]+ GetSexPhrase(DLG_TEXT_BASE[611],DLG_TEXT_BASE[612]) +DLG_TEXT_BASE[613]+ sTemp +DLG_TEXT_BASE[614] + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = DLG_TEXT_BASE[615] + npchar.name + " !";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = DLG_TEXT_BASE[616]+ sTemp +DLG_TEXT_BASE[617] + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = DLG_TEXT_BASE[618] + npchar.name + " !";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = DLG_TEXT_BASE[619]+ sTemp +DLG_TEXT_BASE[620] + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = DLG_TEXT_BASE[621] + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = DLG_TEXT_BASE[622]+ sTemp +DLG_TEXT_BASE[623];
				link.l1 = DLG_TEXT_BASE[624];
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = DLG_TEXT_BASE[625];
			link.l1 = DLG_TEXT_BASE[626];
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = DLG_TEXT_BASE[627];
			link.l1 = DLG_TEXT_BASE[628];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = DLG_TEXT_BASE[629] + pchar.name + DLG_TEXT_BASE[630];
			link.l1 = DLG_TEXT_BASE[631];
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = DLG_TEXT_BASE[632] + pchar.name + DLG_TEXT_BASE[633];
			link.l1 = DLG_TEXT_BASE[634];
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = DLG_TEXT_BASE[635];
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = DLG_TEXT_BASE[636];
			link.l1 = DLG_TEXT_BASE[637] + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = DLG_TEXT_BASE[638];
			link.l1 = DLG_TEXT_BASE[639];
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info(DLG_TEXT_BASE[640]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[641] + pchar.name + DLG_TEXT_BASE[642];
			link.l1 = DLG_TEXT_BASE[643];
			link.l1.go = "Buystatue";
			link.l2 = DLG_TEXT_BASE[644];
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = DLG_TEXT_BASE[645];
			link.l1 = DLG_TEXT_BASE[646] + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = DLG_TEXT_BASE[647]+DLG_TEXT_BASE[648]+DLG_TEXT_BASE[649];
			link.l1 = DLG_TEXT_BASE[650];
			link.l1.go = "Nobuystatue_yes";
			link.l2 = DLG_TEXT_BASE[651];
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = DLG_TEXT_BASE[652];
			link.l1 = DLG_TEXT_BASE[653] + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info(DLG_TEXT_BASE[654]);
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = DLG_TEXT_BASE[655];
			link.l1 = DLG_TEXT_BASE[656];
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info(DLG_TEXT_BASE[657]);
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = DLG_TEXT_BASE[658] + pchar.name + DLG_TEXT_BASE[659];
			link.l1 = DLG_TEXT_BASE[660];
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = DLG_TEXT_BASE[661];
			link.l1 = DLG_TEXT_BASE[662];
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = DLG_TEXT_BASE[663];
			link.l1 = DLG_TEXT_BASE[664];
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = DLG_TEXT_BASE[665]+DLG_TEXT_BASE[666];
			link.l1 = DLG_TEXT_BASE[667];
			link.l1.go = "EscapeSlave_yes";
			link.l2 = DLG_TEXT_BASE[668];
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = DLG_TEXT_BASE[669];
			link.l1 = DLG_TEXT_BASE[670];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = DLG_TEXT_BASE[671]+ sTemp +DLG_TEXT_BASE[672]+ sNum +DLG_TEXT_BASE[673] + FindRussianMoneyString(iSlaveMoneyH) + DLG_TEXT_BASE[674];
				link.l1 = DLG_TEXT_BASE[675] + npchar.name + " !";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = DLG_TEXT_BASE[676]+ sTemp +DLG_TEXT_BASE[677] + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = DLG_TEXT_BASE[678] + npchar.name + " !";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = DLG_TEXT_BASE[679]+ sTemp +DLG_TEXT_BASE[680] + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = DLG_TEXT_BASE[681] + npchar.name + " !";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = DLG_TEXT_BASE[682]+ sTemp +DLG_TEXT_BASE[683];
				link.l1 = DLG_TEXT_BASE[684];
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = DLG_TEXT_BASE[685];
			link.l1 = DLG_TEXT_BASE[686];
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = DLG_TEXT_BASE[687] + pchar.name + DLG_TEXT_BASE[688];
			link.l1 = DLG_TEXT_BASE[689] + npchar.name + DLG_TEXT_BASE[690];
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = DLG_TEXT_BASE[691] + pchar.name + DLG_TEXT_BASE[692];
			link.l1 = DLG_TEXT_BASE[693];
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = DLG_TEXT_BASE[694] + pchar.questTemp.Slavetrader.ShipName + DLG_TEXT_BASE[695] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[696] + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + DLG_TEXT_BASE[697]+DLG_TEXT_BASE[698];
			link.l1 = DLG_TEXT_BASE[699];
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = DLG_TEXT_BASE[700] + pchar.name + DLG_TEXT_BASE[701];
			link.l1 = DLG_TEXT_BASE[702];
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = DLG_TEXT_BASE[703] + NationNameAblative(sti(npchar.nation)) + DLG_TEXT_BASE[704];
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = DLG_TEXT_BASE[705];
			link.l1 = DLG_TEXT_BASE[706] + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = DLG_TEXT_BASE[707]+DLG_TEXT_BASE[708];
			link.l1 = DLG_TEXT_BASE[709] + npchar.name + DLG_TEXT_BASE[710];
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = DLG_TEXT_BASE[711] + pchar.name + ".";
			link.l1 = DLG_TEXT_BASE[712];
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = DLG_TEXT_BASE[713] + GetFullName(pchar) + DLG_TEXT_BASE[714];
			link.l1 = DLG_TEXT_BASE[715];
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = "" + pchar.name + DLG_TEXT_BASE[716];
			link.l1 = DLG_TEXT_BASE[717];
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = DLG_TEXT_BASE[718] + pchar.name + DLG_TEXT_BASE[719]+DLG_TEXT_BASE[720];
			link.l1 = DLG_TEXT_BASE[721];
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдет
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Charles";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = DLG_TEXT_BASE[722] + pchar.questTemp.Slavetraderbrig.ShipName + DLG_TEXT_BASE[723] + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + DLG_TEXT_BASE[724];
			link.l1 = DLG_TEXT_BASE[725];
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = DLG_TEXT_BASE[726] + pchar.name + DLG_TEXT_BASE[727];
			link.l1 = DLG_TEXT_BASE[728];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = DLG_TEXT_BASE[729] + pchar.name + DLG_TEXT_BASE[730];
			link.l1 = DLG_TEXT_BASE[731] + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = DLG_TEXT_BASE[732];
			link.l1 = DLG_TEXT_BASE[733] + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = DLG_TEXT_BASE[734] + pchar.name + DLG_TEXT_BASE[735];
			link.l1 = DLG_TEXT_BASE[736];
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = DLG_TEXT_BASE[737];
			link.l1 = DLG_TEXT_BASE[738];
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = DLG_TEXT_BASE[739] + pchar.name + DLG_TEXT_BASE[740];
			link.l1 = DLG_TEXT_BASE[741];
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = DLG_TEXT_BASE[742] + pchar.name + DLG_TEXT_BASE[743];
			link.l1 = DLG_TEXT_BASE[744];
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = DLG_TEXT_BASE[745]+DLG_TEXT_BASE[746]+DLG_TEXT_BASE[747]+DLG_TEXT_BASE[748];
			link.l1 = DLG_TEXT_BASE[749];
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = DLG_TEXT_BASE[750] + pchar.name + DLG_TEXT_BASE[751];
			link.l1 = DLG_TEXT_BASE[752] + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = DLG_TEXT_BASE[753] + pchar.name + DLG_TEXT_BASE[754];
			link.l1 = DLG_TEXT_BASE[755] + npchar.name + DLG_TEXT_BASE[756];
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = DLG_TEXT_BASE[757];
			link.l1 = DLG_TEXT_BASE[758];
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = DLG_TEXT_BASE[759] + pchar.name + DLG_TEXT_BASE[760];
			link.l1 = DLG_TEXT_BASE[761];
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = DLG_TEXT_BASE[762]+DLG_TEXT_BASE[763]+DLG_TEXT_BASE[764];
			link.l1 = DLG_TEXT_BASE[765];
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = DLG_TEXT_BASE[766]+DLG_TEXT_BASE[767];
			link.l1 = DLG_TEXT_BASE[768] + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = DLG_TEXT_BASE[769] + sTemp + DLG_TEXT_BASE[770] + pchar.questTemp.Slavetrader.ShipName + DLG_TEXT_BASE[771]+DLG_TEXT_BASE[772];
			link.l1 = DLG_TEXT_BASE[773];
			link.l1.go = "SlaveGalleon_5";
			link.l2 = DLG_TEXT_BASE[774];
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = DLG_TEXT_BASE[775] + sTemp + DLG_TEXT_BASE[776];
			link.l1 = DLG_TEXT_BASE[777];
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = DLG_TEXT_BASE[778] + pchar.name + DLG_TEXT_BASE[779] + pchar.name + ".";
			link.l1 = DLG_TEXT_BASE[780] + npchar.name + DLG_TEXT_BASE[781];
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = DLG_TEXT_BASE[782];
				link.l1 = DLG_TEXT_BASE[783]+ sTemp +DLG_TEXT_BASE[784] + FindRussianMoneyString(iSlaveMoney) + DLG_TEXT_BASE[785];
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = DLG_TEXT_BASE[786]+DLG_TEXT_BASE[787] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[788];
				link.l1 = DLG_TEXT_BASE[789];
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = DLG_TEXT_BASE[790]+DLG_TEXT_BASE[791] + pchar.name +DLG_TEXT_BASE[792]+DLG_TEXT_BASE[793];
			link.l1 = DLG_TEXT_BASE[794];
			link.l1.go = "Wingalleon_yes";
			link.l2 = DLG_TEXT_BASE[795] + npchar.name + DLG_TEXT_BASE[796];
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = DLG_TEXT_BASE[797] + npchar.name + DLG_TEXT_BASE[798]+DLG_TEXT_BASE[799] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[800];
			link.l1 = DLG_TEXT_BASE[801];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = DLG_TEXT_BASE[802] + pchar.name + DLG_TEXT_BASE[803]+DLG_TEXT_BASE[804]+DLG_TEXT_BASE[805];
			link.l1 = DLG_TEXT_BASE[806] + npchar.name + DLG_TEXT_BASE[807];
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info(DLG_TEXT_BASE[808]);
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = DLG_TEXT_BASE[809] + pchar.name + DLG_TEXT_BASE[810] + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + DLG_TEXT_BASE[811];
			link.l1 = DLG_TEXT_BASE[812] + npchar.name + DLG_TEXT_BASE[813];
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = DLG_TEXT_BASE[814] + pchar.name + DLG_TEXT_BASE[815]+DLG_TEXT_BASE[816];
			link.l1 = DLG_TEXT_BASE[817];
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "jewelry30"))
			{
				dialog.text = DLG_TEXT_BASE[818];
				link.l1 = DLG_TEXT_BASE[819];
				link.l1.go = "BG_money";
				link.l2 = DLG_TEXT_BASE[820];
				link.l2.go = "BG_change";
				link.l3 = DLG_TEXT_BASE[821];
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[822];
				link.l1 = DLG_TEXT_BASE[823];
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = DLG_TEXT_BASE[824];
			link.l1 = DLG_TEXT_BASE[825];
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info(DLG_TEXT_BASE[826]);
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "jewelry30", 1);
		break;
			
		case "BG_change":
			dialog.text = DLG_TEXT_BASE[827];
			link.l1 = DLG_TEXT_BASE[828];
			link.l1.go = "BG_PF";
			Log_Info(DLG_TEXT_BASE[829]);
			Log_Info(DLG_TEXT_BASE[830]);
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "jewelry30", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = DLG_TEXT_BASE[831];
			link.l1 = DLG_TEXT_BASE[832];
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = DLG_TEXT_BASE[833];
			link.l1 = DLG_TEXT_BASE[834];
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = DLG_TEXT_BASE[835];
				link.l1 = DLG_TEXT_BASE[836];
				link.l1.go = "PF_money";
				link.l2 = DLG_TEXT_BASE[837];
				link.l2.go = "PF_change";
				link.l3 = DLG_TEXT_BASE[838];
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[839];
				link.l1 = DLG_TEXT_BASE[840];
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = DLG_TEXT_BASE[841];
			link.l1 = DLG_TEXT_BASE[842];
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info(DLG_TEXT_BASE[843]);
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = DLG_TEXT_BASE[844];
			link.l1 = DLG_TEXT_BASE[845];
			link.l1.go = "FindRat_3";
			Log_Info(DLG_TEXT_BASE[846]);
			Log_Info(DLG_TEXT_BASE[847]);
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = DLG_TEXT_BASE[848];
			link.l1 = DLG_TEXT_BASE[849];
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = DLG_TEXT_BASE[850] + pchar.name + DLG_TEXT_BASE[851];
			link.l1 = DLG_TEXT_BASE[852];
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = DLG_TEXT_BASE[853];
			link.l1 = DLG_TEXT_BASE[854];
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = DLG_TEXT_BASE[855];
			link.l1 = DLG_TEXT_BASE[856];
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = DLG_TEXT_BASE[857]+DLG_TEXT_BASE[858]+DLG_TEXT_BASE[859]+DLG_TEXT_BASE[860];
			link.l1 = DLG_TEXT_BASE[861];
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = DLG_TEXT_BASE[862]+DLG_TEXT_BASE[863];
			link.l1 = DLG_TEXT_BASE[864];
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = DLG_TEXT_BASE[865];
			link.l1 = DLG_TEXT_BASE[866];
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = DLG_TEXT_BASE[867] + pchar.name + DLG_TEXT_BASE[868];
			link.l1 = DLG_TEXT_BASE[869] + npchar.name + DLG_TEXT_BASE[870];
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = DLG_TEXT_BASE[871];
			link.l1 = DLG_TEXT_BASE[872];
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = DLG_TEXT_BASE[873];
			link.l1 = DLG_TEXT_BASE[874] + npchar.name + DLG_TEXT_BASE[875];
			link.l1.go = "Wincorvette_3";
			Log_Info(DLG_TEXT_BASE[876]);
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = DLG_TEXT_BASE[877];
			link.l1 = DLG_TEXT_BASE[878] + npchar.name + DLG_TEXT_BASE[879];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = DLG_TEXT_BASE[880]+DLG_TEXT_BASE[881];
			link.l1 = DLG_TEXT_BASE[882] + npchar.name + DLG_TEXT_BASE[883];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = DLG_TEXT_BASE[884] + pchar.name + DLG_TEXT_BASE[885]+DLG_TEXT_BASE[886];
			link.l1 = DLG_TEXT_BASE[887] + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = DLG_TEXT_BASE[888];
			link.l1 = DLG_TEXT_BASE[889];
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = DLG_TEXT_BASE[890] + pchar.name + DLG_TEXT_BASE[891]+DLG_TEXT_BASE[892];
			link.l1 = DLG_TEXT_BASE[893] + npchar.name + DLG_TEXT_BASE[894] + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = DLG_TEXT_BASE[895] + npchar.name + DLG_TEXT_BASE[896];
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = DLG_TEXT_BASE[897] + pchar.name + DLG_TEXT_BASE[898];
			link.l1 = DLG_TEXT_BASE[899] + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = DLG_TEXT_BASE[900]+DLG_TEXT_BASE[901];
			link.l1 = DLG_TEXT_BASE[902];
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = DLG_TEXT_BASE[903];
			link.l1 = DLG_TEXT_BASE[904];
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = DLG_TEXT_BASE[905] + pchar.name + DLG_TEXT_BASE[906]+DLG_TEXT_BASE[907]+DLG_TEXT_BASE[908];
			link.l1 = DLG_TEXT_BASE[909] + npchar.name + DLG_TEXT_BASE[910];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = DLG_TEXT_BASE[911];
				link.l1 = DLG_TEXT_BASE[912] + sTemp + DLG_TEXT_BASE[913];
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = DLG_TEXT_BASE[914] + sTemp + DLG_TEXT_BASE[915];
				link.l1 = DLG_TEXT_BASE[916];
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = DLG_TEXT_BASE[917];
			link.l1 = DLG_TEXT_BASE[918];
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = DLG_TEXT_BASE[919];
			link.l1 = DLG_TEXT_BASE[920];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = DLG_TEXT_BASE[921];
			link.l1 = DLG_TEXT_BASE[922];
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = DLG_TEXT_BASE[923];
			link.l1 = DLG_TEXT_BASE[924];
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = DLG_TEXT_BASE[925] + sTemp + DLG_TEXT_BASE[926] + FindRussianMoneyString(iSlaveMoney) + DLG_TEXT_BASE[927];
			link.l1 = DLG_TEXT_BASE[928] + npchar.name + DLG_TEXT_BASE[929];
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + DLG_TEXT_BASE[930];
			link.l1 = DLG_TEXT_BASE[931];
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = DLG_TEXT_BASE[932] + pchar.name + DLG_TEXT_BASE[933];
			link.l1 = DLG_TEXT_BASE[934] + npchar.name + DLG_TEXT_BASE[935];
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = DLG_TEXT_BASE[936];
			link.l1 = DLG_TEXT_BASE[937];
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = DLG_TEXT_BASE[938];
			link.l1 = DLG_TEXT_BASE[939] + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = DLG_TEXT_BASE[940];
			link.l1 = DLG_TEXT_BASE[941] + pchar.questTemp.Slavetrader.Name + " ?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = DLG_TEXT_BASE[942];
			link.l1 = DLG_TEXT_BASE[943];
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = DLG_TEXT_BASE[944];
			link.l1 = DLG_TEXT_BASE[945];
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = DLG_TEXT_BASE[946];
			link.l1 = DLG_TEXT_BASE[947];
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = DLG_TEXT_BASE[948];
			link.l1 = DLG_TEXT_BASE[949] + npchar.name + DLG_TEXT_BASE[950];
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = DLG_TEXT_BASE[951];
			link.l1 = DLG_TEXT_BASE[952];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = DLG_TEXT_BASE[953]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[954]+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+" : "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+DLG_TEXT_BASE[955]+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+DLG_TEXT_BASE[956];
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = DLG_TEXT_BASE[957]+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+DLG_TEXT_BASE[958];
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = DLG_TEXT_BASE[959]+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+DLG_TEXT_BASE[960];
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = DLG_TEXT_BASE[961];
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = DLG_TEXT_BASE[962];
			link.l4.go = "Noblelombard_4";
			npchar.quest.noblelombard = "true";
		break;
		
		case "Noblelombard_1":
			dialog.text = DLG_TEXT_BASE[963]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[964];
			link.l1 = DLG_TEXT_BASE[965]+npchar.name+DLG_TEXT_BASE[966];
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = DLG_TEXT_BASE[967]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[968];
				link.l1 = DLG_TEXT_BASE[969];
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[970];
				link.l1 = DLG_TEXT_BASE[971];
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = DLG_TEXT_BASE[972]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[973];
				link.l1 = DLG_TEXT_BASE[974];
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[975];
				link.l1 = DLG_TEXT_BASE[976];
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = DLG_TEXT_BASE[977]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[978];
				link.l1 = DLG_TEXT_BASE[979];
				link.l1.go = "Noblelombard_6";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[980]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[981];
				link.l1 = DLG_TEXT_BASE[982]+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = DLG_TEXT_BASE[983]+pchar.GenQuest.Noblelombard.Name+DLG_TEXT_BASE[984];
			link.l1 = DLG_TEXT_BASE[985]+npchar.name+DLG_TEXT_BASE[986];
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(NPchar, "quest.noblelombard");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = makeint(sti(pchar.GenQuest.Noblelombard.Regard)/100);
			TakeNItems(pchar, "gold_dublon", iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(NPchar, "quest.noblelombard");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = DLG_TEXT_BASE[987];
			link.l1 = DLG_TEXT_BASE[988];
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			dialog.text = DLG_TEXT_BASE[990];
			link.l1 = DLG_TEXT_BASE[991];
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = DLG_TEXT_BASE[992];
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
	}	
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(9)+11), "man", "man", 10, sti(npchar.nation), -1, false, "citizen"));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{		
		for(n=0; n<MAX_COLONIES; n++)
		{			
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));	
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1; 
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(9)+11), "man", "man", 10, sti(colonies[nation].nation), -1, false, "citizen"));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
            if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}		
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}

// ugeen -> проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS36, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}		