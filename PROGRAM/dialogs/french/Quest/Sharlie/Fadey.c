#include "SD\TEXT\DIALOGS\Quest\Sharlie\Fadey.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = DLG_TEXT_Q[269];
					link.l1 = DLG_TEXT_Q[270];
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = DLG_TEXT_Q[271];
					link.l1 = DLG_TEXT_Q[272];
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = DLG_TEXT_Q[273];
					link.l1 = DLG_TEXT_Q[274];
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = DLG_TEXT_Q[275];
					if (GetCharacterItem(pchar, "gold_dublon") >= 100)
					{
						link.l1 = DLG_TEXT_Q[276];
						link.l1.go = "Tichingitu_7";
					}
					else
					{
						link.l1 = DLG_TEXT_Q[277];
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = DLG_TEXT_Q[278];
					link.l1 = TimeGreeting()+DLG_TEXT_Q[279];
					link.l1.go = "trial";
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = DLG_TEXT_Q[280];
					link.l1 = TimeGreeting()+DLG_TEXT_Q[281];
					link.l1.go = "vodka";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = DLG_TEXT_Q[282]+pchar.name+DLG_TEXT_Q[283];
					link.l1 = TimeGreeting()+DLG_TEXT_Q[284];
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+DLG_TEXT_Q[285];
					link.l1 = DLG_TEXT_Q[286];
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					dialog.text = DLG_TEXT_Q[287];
					link.l1 = DLG_TEXT_Q[288];
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = DLG_TEXT_Q[289]+pchar.name+DLG_TEXT_Q[290];
					link.l1 = DLG_TEXT_Q[291];
					link.l1.go = "guardoftruth_14";
					break;
				}
				if(pchar.questTemp.Ascold == "HaveRecomendation")
				{
					sld = characterFromId(pchar.questTemp.Ascold.TraderId);
					dialog.text = DLG_TEXT_Q[18];
					link.l1 = DLG_TEXT_Q[19] + GetFullName(sld) + DLG_TEXT_Q[20] + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
					link.l1.go = "Step_5";
					break;
				}	
				if(pchar.questTemp.Ascold == "TakenThreeObject" && GetQuestPastDayParam("questTemp.Ascold") > 62) // торговля канатами
				{		
					dialog.text = DLG_TEXT_Q[59] + GetFullName(pchar) + ".";
					link.l1 = DLG_TEXT_Q[60];
					link.l1.go = "Step_14";
					break;
				}
				if (pchar.questTemp.Ascold == "Mummie_begin" && GetQuestPastDayParam("questTemp.Ascold") > 40)
				{
					dialog.text = DLG_TEXT_Q[134]+ GetFullName(pchar) + "...";
					link.l1 = DLG_TEXT_Q[135];
					link.l1.go = "Step_31A";
					break;
				}		
				if (pchar.questTemp.Ascold == "Ascold_FoundMummy")
				{
					dialog.text = DLG_TEXT_Q[189] + GetFullName(pchar) + DLG_TEXT_Q[190];
					link.l1 = DLG_TEXT_Q[191];
					link.l1.go = "Step_46";
					break;
				}	
				if (pchar.questTemp.Ascold == "Ascold_ReturnToAscold")
				{
					dialog.text = DLG_TEXT_Q[205];
					link.l1 = DLG_TEXT_Q[206];
					link.l1.go = "Step_52";	
					break;
				}						
				dialog.text = DLG_TEXT_Q[292]+pchar.name+" ?";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = DLG_TEXT_Q[293];
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = DLG_TEXT_Q[294];
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = DLG_TEXT_Q[295];
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = DLG_TEXT_Q[296];
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = DLG_TEXT_Q[297];
					link.l3.go = "ropes";
				}
				if(pchar.questTemp.Ascold == "SeekThreeObject") // торговля канатами
				{
					link.l4 = DLG_TEXT_Q[298];
					link.l4.go = "ResultOfSeek";
				}						
				if (pchar.questTemp.Ascold.work == 1)
				{
					link.l4 = DLG_TEXT_Q[299];
					link.l4.go = "AfterManowarsBattle";
				}
				if(pchar.questTemp.Ascold == "Mummie_begin") // торговля канатами
				{
					link.l4 = DLG_TEXT_Q[300];
					link.l4.go = "Mummie_begin";
				}	
				if (pchar.questTemp.Ascold == "Ascold_SeekGrave")
				{	
					link.l4 = DLG_TEXT_Q[152];
					link.l4.go = "Step_36";
				}					
				if (pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
				{	
					link.l4 = DLG_TEXT_Q[154];
					link.l4.go = "Step_37";
				}					
				if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
				{
					link.l4 = DLG_TEXT_Q[156];
					link.l4.go = "Step_38";
				}	
				if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"))
				{
					link.l4 = DLG_TEXT_Q[160];
					link.l4.go = "Step_45";
				}
				if (pchar.questTemp.Azzy == "HowToKnowAzzy")
				{
					link.l4 = DLG_TEXT_Q[243];
					link.l4.go = "Step_64";
				}				
				link.l1 = DLG_TEXT_Q[301];
				link.l1.go = "help";
 				link.l9 = DLG_TEXT_Q[302];
				link.l9.go = "exit";
				NextDiag.TempNode = "First time";
			}
			else
			{
				if (npchar.quest.meeting == "0")
				{
					dialog.text = DLG_TEXT_Q[0];
					link.l1 = DLG_TEXT_Q[1] + GetFullName(pchar) + ".";
					link.l1.go = "Step_1";
					npchar.quest.meeting = "1";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[2];
					link.l1 = DLG_TEXT_Q[3];
					link.l1.go = "exit";
					link.l2 = DLG_TEXT_Q[4];
					link.l2.go = "Step_3";
					NextDiag.TempNode = "First time";
				}
			}
		break;

 		case "Step_1":
        	dialog.text = DLG_TEXT_Q[5];
    		link.l1 = DLG_TEXT_Q[6];
    		link.l1.go = "Step_2";
		break;

 		case "Step_2":
        	dialog.text = DLG_TEXT_Q[7];
    		link.l1 = DLG_TEXT_Q[8];
    		link.l1.go = "First time";
		break;

 		case "Step_3":
            if (npchar.quest.meeting == "1")
            {
            	dialog.text = DLG_TEXT_Q[9];
        		link.l1 = "...";
        		npchar.quest.meeting = "2";
            }
            else
            {
            	dialog.text = RandPhraseSimple(DLG_TEXT_Q[10], DLG_TEXT_Q[11]);
        		link.l1 = RandPhraseSimple(DLG_TEXT_Q[12], DLG_TEXT_Q[13]);
            }
            link.l1.go = "Step_4";
		break;

 		case "Step_4":
            DoReloadCharacterToLocation("BasTer_town", "reload", "houseSp1");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
 		case "Step_5":
        	dialog.text = DLG_TEXT_Q[21];
			link.l1 = "...";
    		link.l1.go = "Step_5bis";
		break;

		case "Step_5bis":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey_3");
			NextDiag.CurrentNode = "Step_5ter";
		break;		

 		case "Step_5ter":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
        	dialog.text = DLG_TEXT_Q[22]+DLG_TEXT_Q[23];
    		link.l1 = sld.lastname + DLG_TEXT_Q[24];
        	link.l1.go = "Step_6";
		break;
		
 		case "Step_6":
        	dialog.text = DLG_TEXT_Q[25];
    		link.l1 = DLG_TEXT_Q[26];
        	link.l1.go = "Step_7";
        	AddMoneyToCharacter(pchar, 30000);
			TakeItemFromCharacter(pchar, "Powder_mummie");
		break;

 		case "Step_7":
        	dialog.text = DLG_TEXT_Q[30];
    		link.l1 = DLG_TEXT_Q[31];
    		link.l1.go = "Step_8";
		break;

 		case "Step_8":
        	dialog.text = DLG_TEXT_Q[32]+
                          DLG_TEXT_Q[33]+
                          DLG_TEXT_Q[34];
    		link.l1 = DLG_TEXT_Q[35];
    		link.l1.go = "Step_9";
		break;		

 		case "Step_9":
        	dialog.text = DLG_TEXT_Q[36]+
                          DLG_TEXT_Q[37];
    		link.l1 = DLG_TEXT_Q[38];
    		link.l1.go = "Step_10";
    		link.l2 = DLG_TEXT_Q[39];
    		link.l2.go = "No_Work_Table";			
		break;
		
 		case "No_Work_Table":
        	dialog.text = DLG_TEXT_Q[40];
    		link.l1 = DLG_TEXT_Q[41];
    		link.l1.go = "vodka_14";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;		

 		case "No_Work":
        	dialog.text = DLG_TEXT_Q[40];
    		link.l1 = DLG_TEXT_Q[41];
    		link.l1.go = "exit";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;	
		
 		case "Step_10":
        	dialog.text = DLG_TEXT_Q[42]+
                          DLG_TEXT_Q[43];
    		link.l1 = DLG_TEXT_Q[44];
    		link.l1.go = "vodka_14";
    	    pchar.questTemp.Ascold = "SeekThreeObject";
            AddQuestRecord("Ascold", "3");
		break;

 		case "ResultOfSeek":
        	dialog.text = DLG_TEXT_Q[45];
    		link.l1 = DLG_TEXT_Q[46];
    		link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "indian_8") && CheckCharacterItem(pchar, "indian_9") && CheckCharacterItem(pchar, "amulet_5"))
            {
                link.l2 = DLG_TEXT_Q[47];
                link.l2.go = "Step_11";
            }
		break;

 		case "Step_11":
        	dialog.text = DLG_TEXT_Q[48];
            link.l1 = DLG_TEXT_Q[49];
            if (pchar.questTemp.Ascold == "SoughtThreeObject")
            {
               link.l1 = DLG_TEXT_Q[50];
            }
    		link.l1.go = "Step_12";
            link.l2 = DLG_TEXT_Q[51];
    		link.l2.go = "WantMoreMoney";
		break;

 		case "WantMoreMoney":
        	dialog.text = DLG_TEXT_Q[52]+
                          DLG_TEXT_Q[53];
        	link.l1 = DLG_TEXT_Q[54];
    		link.l1.go = "Step_12";
		break;

 		case "Step_12":
        	dialog.text = DLG_TEXT_Q[55];
        	link.l1 = DLG_TEXT_Q[56];
    		link.l1.go = "Step_13";
		break;	

 		case "Step_13":
        	dialog.text = DLG_TEXT_Q[57];
    		link.l1 = DLG_TEXT_Q[58];
    		link.l1.go = "exit";
    		TakeItemFromCharacter(pchar, "indian_8");
    		TakeItemFromCharacter(pchar, "indian_9");
    		TakeItemFromCharacter(pchar, "amulet_5");
    		AddMoneyToCharacter(pchar, 90000);
			pchar.questTemp.Ascold = "TakenThreeObject";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		AddQuestRecord("Ascold", "4");
		break;	
		
 		case "Step_14":
        	dialog.text = DLG_TEXT_Q[64];
        	link.l1 = DLG_TEXT_Q[65];
    		link.l1.go = "Step_15";
		break;

 		case "Step_15":
        	dialog.text = DLG_TEXT_Q[66]+
                          DLG_TEXT_Q[67]+
                          DLG_TEXT_Q[68]+
                          DLG_TEXT_Q[69];
        	link.l1 = DLG_TEXT_Q[70];
    		link.l1.go = "Step_16";
        	link.l2 = DLG_TEXT_Q[71];
    		link.l2.go = "No_Work";
		break;

 		case "Step_16":
        	dialog.text = DLG_TEXT_Q[72];
        	link.l1 = DLG_TEXT_Q[73];
    		link.l1.go = "exit";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		pchar.questTemp.Ascold = "ToHavanna";
			pchar.questTemp.Ascold.work = 1;
    		AddQuestRecord("Ascold", "5");
		break;		

 		case "AfterManowarsBattle":
        	dialog.text = DLG_TEXT_Q[74];
        	link.l1 = DLG_TEXT_Q[75];
    		link.l1.go = "exit";
        	link.l2 = DLG_TEXT_Q[76];
    		link.l2.go = "No_Work";
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna")
            {
             	link.l1 = DLG_TEXT_Q[77];
        		link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
             	link.l1 = DLG_TEXT_Q[78];
        		link.l1.go = "Step_20";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[79];
        		link.l1.go = "Step_24";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[80];
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "2ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[81];
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[82];
        		link.l1.go = "NoFoundList";
            }
    		if (CheckCharacterItem(pchar, "Powder_mummie") && pchar.questTemp.Ascold == "ILookedThisAss")
    		{
            	link.l1 = DLG_TEXT_Q[83];
        		link.l1.go = "Step_26";
    		}
    		if (CheckCharacterItem(pchar, "Powder_mummie") && pchar.questTemp.Ascold == "2ILookedThisAss")
    		{
            	link.l1 = DLG_TEXT_Q[84];
        		link.l1.go = "Step_26";
    		}
            if (CheckCharacterItem(pchar, "Powder_mummie") && pchar.questTemp.Ascold == "Ascold_ManowarsDead")
            {
             	link.l1 = DLG_TEXT_Q[85];
        		link.l1.go = "ManowarGoodWork";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[86];
        		link.l1.go = "ManowarGoodWork";
            }
		break;

 		case "Step_17":
        	dialog.text = DLG_TEXT_Q[87];
        	link.l1 = DLG_TEXT_Q[88];
    		link.l1.go = "Step_18";
		break;

 		case "Step_18":
        	dialog.text = DLG_TEXT_Q[89];
        	link.l1 = DLG_TEXT_Q[90];
    		link.l1.go = "Step_19";
		break;

 		case "Step_19":
        	dialog.text = DLG_TEXT_Q[91];
        	link.l1 = DLG_TEXT_Q[92];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2SeekInformatorHavanna";
		break;

 		case "Step_20":
        	dialog.text = DLG_TEXT_Q[93];
        	link.l1 = DLG_TEXT_Q[94];
    		link.l1.go = "Step_21";
		break;

 		case "Step_21":
        	dialog.text = DLG_TEXT_Q[95];
        	link.l1 = DLG_TEXT_Q[96];
    		link.l1.go = "Step_22";
		break;

 		case "Step_22":
        	dialog.text = DLG_TEXT_Q[97]+
                          DLG_TEXT_Q[98];
        	link.l1 = DLG_TEXT_Q[99];
    		link.l1.go = "Step_23";
        	link.l2 = DLG_TEXT_Q[100];
    		link.l2.go = "No_Work";
		break;

 		case "Step_23":
        	dialog.text = DLG_TEXT_Q[101];
        	link.l1 = DLG_TEXT_Q[102];
    		link.l1.go = "exit";
    		AddQuestRecord("Ascold", "8");
    		pchar.questTemp.Ascold = "IMustKillAll";
		break;

 		case "Step_24":
        	dialog.text = DLG_TEXT_Q[103];
        	link.l1 = DLG_TEXT_Q[104];
    		link.l1.go = "Step_25";
            link.l2 = DLG_TEXT_Q[105];
    		link.l2.go = "No_Work";
		break;

 		case "Step_25":
        	dialog.text = DLG_TEXT_Q[106];
        	link.l1 = DLG_TEXT_Q[107];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2ILookedThisAss";
		break;

 		case "NoFoundList":
        	dialog.text = DLG_TEXT_Q[108];
    		link.l1 = "...";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_26":
        	dialog.text = DLG_TEXT_Q[111];
        	link.l1 = DLG_TEXT_Q[112];
    		link.l1.go = "Step_27";
            link.l2 = DLG_TEXT_Q[113];
    		link.l2.go = "No_Work";
            link.l3 = DLG_TEXT_Q[114];
    		link.l3.go = "Step_27";
            pchar.questTemp.Ascold.list = 1;
		break;

 		case "Step_27":
        	dialog.text = DLG_TEXT_Q[115];
        	link.l1 = DLG_TEXT_Q[116];
    		link.l1.go = "exit";
            AddQuestRecord("Ascold", "10");
		break;

 		case "ManowarGoodWork":
        	dialog.text = DLG_TEXT_Q[117];
        	link.l1 = DLG_TEXT_Q[118];
    		link.l1.go = "exit";
            link.l2 = DLG_TEXT_Q[119];
    		link.l2.go = "Step_28";
    		NextDiag.TempNode = "ManowarGoodWork";
		break;

 		case "Step_28":
        	dialog.text = DLG_TEXT_Q[120];
        	link.l1 = DLG_TEXT_Q[121];
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		pchar.quest.Ascold_FightNearTemple.over = "yes";
		break;	
		
		case "vodka_14":
			DialogExit();
			LAi_SetPlayerType(pchar);
			DoQuestReloadToLocation("BasTer_houseSp1", "goto", "goto1", "");			
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;	

 		case "Ascold_KilledTemple":
        	dialog.text = DLG_TEXT_Q[122];
        	link.l1 = DLG_TEXT_Q[123];
    		link.l1.go = "NoFoundList";
            if (CheckCharacterItem(pchar, "Powder_mummie") || CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
            	link.l1 = DLG_TEXT_Q[124];
        		link.l1.go = "Step_29";
                DeleteAttribute(PChar, "questTemp.Ascold.List");
            }
		break;

 		case "Step_29":
        	dialog.text = DLG_TEXT_Q[125];
        	link.l1 = DLG_TEXT_Q[126];
    		link.l1.go = "Step_30";
		break;

 		case "Step_30":
        	dialog.text = DLG_TEXT_Q[127];
        	link.l1 = DLG_TEXT_Q[128];
    		link.l1.go = "Step_31";
		break;

 		case "Step_31":
        	dialog.text = DLG_TEXT_Q[129];
        	link.l1 = DLG_TEXT_Q[130];
    		link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "Powder_mummie");
    		SaveCurrentQuestDateParam("questTemp.Ascold");
			pchar.questTemp.Ascold = "Mummie_begin";
    		AddQuestRecord("Ascold", "12");
		break;	

 		case "Mummie_begin":
        	dialog.text = DLG_TEXT_Q[131]+ GetFullName(pchar) + DLG_TEXT_Q[132];
        	link.l1 = DLG_TEXT_Q[133];
    		link.l1.go = "exit";
		break;		
		
 		case "Step_31A":
        	dialog.text = DLG_TEXT_Q[136];
        	link.l1 = DLG_TEXT_Q[137];
    		link.l1.go = "Step_32";
		break;

 		case "Step_32":
        	dialog.text = DLG_TEXT_Q[138];
        	link.l1 = DLG_TEXT_Q[139];
    		link.l1.go = "Step_33";
        break;

        case "Step_33":
        	dialog.text = DLG_TEXT_Q[140];
        	link.l1 = DLG_TEXT_Q[141];
    		link.l1.go = "Step_34";
            link.l2 = DLG_TEXT_Q[142];
    		link.l2.go = "No_Work";
		break;

 		case "Step_34":
        	dialog.text = DLG_TEXT_Q[143]+
                          DLG_TEXT_Q[144];
        	link.l1 = DLG_TEXT_Q[145];
    		link.l1.go = "Step_35";
        	link.l2 = DLG_TEXT_Q[146];
    		link.l2.go = "No_Work";
		break;
		
 		case "Step_35":
        	dialog.text = DLG_TEXT_Q[147];
        	link.l1 = DLG_TEXT_Q[148];
    		link.l1.go = "exit";
    		AddQuestRecord("Ascold", "13");
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "Ascold_SeekGrave";
		break;	

 		case "Step_36":
        	dialog.text = DLG_TEXT_Q[163]+
                          DLG_TEXT_Q[164];
        	link.l1 = DLG_TEXT_Q[165];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_CantSeekGrave";
		break;
		
 		case "Step_37":
        	dialog.text = DLG_TEXT_Q[166];
        	link.l1 = DLG_TEXT_Q[167];
    		link.l1.go = "exit";
		break;

 		case "Step_38":
        	dialog.text = DLG_TEXT_Q[168]+
                          DLG_TEXT_Q[169];
        	link.l1 = DLG_TEXT_Q[170];
    		link.l1.go = "Step_40";
		break;
		
 		case "Step_40":
        	dialog.text = DLG_TEXT_Q[171]+
                          DLG_TEXT_Q[172]+
                          DLG_TEXT_Q[173];
        	link.l1 = DLG_TEXT_Q[174];
    		link.l1.go = "Step_41";
		break;

 		case "Step_41":
        	dialog.text = DLG_TEXT_Q[175]+
                          DLG_TEXT_Q[176]+
                          DLG_TEXT_Q[177];
        	link.l1 = DLG_TEXT_Q[178];
    		link.l1.go = "Step_42";
		break;

 		case "Step_42":
        	dialog.text = DLG_TEXT_Q[179];
        	link.l1 = DLG_TEXT_Q[180];
    		link.l1.go = "Step_43";
		break;
		
 		case "Step_43":
        	dialog.text = DLG_TEXT_Q[181]+
                          DLG_TEXT_Q[182];
        	link.l1 = DLG_TEXT_Q[183];
    		link.l1.go = "Step_44";
        	link.l2 = DLG_TEXT_Q[184];
    		link.l2.go = "No_Work";
		break;

 		case "Step_44":
        	dialog.text = DLG_TEXT_Q[185];
        	link.l1 = DLG_TEXT_Q[186];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_SeekRockLetter";
            // ==> ?елаем скрижали видимыми, теперь их можно найти.
            sld = ItemsFromID("Rock_letter");
            sld.shown = 1;
		break;			
		
 		case "Step_45":
        	dialog.text = DLG_TEXT_Q[187];
        	link.l1 = DLG_TEXT_Q[188];
    		link.l1.go = "exit";
			bDisableLandEncounters = true; //закроем энкаунтеров, лучше раньше, чем баги.
    		pchar.questTemp.Ascold = "Ascold_EnterGrave";
			sld = ItemsFromID("Rock_letter");
			sld.model = "StoneMap2";
		break;	

 		case "Step_46":
        	dialog.text = DLG_TEXT_Q[192];
        	link.l1 = DLG_TEXT_Q[193];
    		link.l1.go = "Step_47";
		break;
		
 		case "Step_47":
        	dialog.text = DLG_TEXT_Q[194];
        	link.l1 = DLG_TEXT_Q[195];
    		link.l1.go = "Step_48";
		break;
		
 		case "Step_48":
        	dialog.text = DLG_TEXT_Q[196]+
                          DLG_TEXT_Q[197];
        	link.l1 = DLG_TEXT_Q[198];
    		link.l1.go = "Step_49";
		break;
		
 		case "Step_49":
        	dialog.text = DLG_TEXT_Q[199];
        	link.l1 = DLG_TEXT_Q[200];
    		link.l1.go = "Step_50";
		break;

 		case "Step_50":
        	dialog.text = DLG_TEXT_Q[201];
        	link.l1 = DLG_TEXT_Q[202];
    		link.l1.go = "Step_51";
		break;

 		case "Step_51":
        	dialog.text = DLG_TEXT_Q[203];
           	link.l1 = DLG_TEXT_Q[204];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_WateringMummy";
    		GiveItem2Character(Pchar,"Ascold_rabble");
		break;		

 		case "Step_52":
        	dialog.text = DLG_TEXT_Q[211]+
                          DLG_TEXT_Q[212];
        	link.l1 = DLG_TEXT_Q[213];
    		link.l1.go = "Step_53";
		break;

 		case "Step_53":
        	dialog.text = DLG_TEXT_Q[214];
        	link.l1 = DLG_TEXT_Q[215];
    		link.l1.go = "Step_54";
		break;

 		case "Step_54":
        	dialog.text = DLG_TEXT_Q[216]+
                          DLG_TEXT_Q[217];
        	link.l1 = DLG_TEXT_Q[218];
    		link.l1.go = "Step_55";
		break;

 		case "Step_55":
        	dialog.text = DLG_TEXT_Q[219];
        	link.l1 = DLG_TEXT_Q[220];
    		link.l1.go = "Step_56";
		break;

 		case "Step_56":
        	dialog.text = DLG_TEXT_Q[221]+
                          DLG_TEXT_Q[222];
        	link.l1 = DLG_TEXT_Q[223];
    		link.l1.go = "Step_57";
		break;

 		case "Step_57":
        	dialog.text = DLG_TEXT_Q[224];
        	link.l1 = DLG_TEXT_Q[225];
    		link.l1.go = "Step_58";
		break;

 		case "Step_58":
        	dialog.text = DLG_TEXT_Q[226]+
                          DLG_TEXT_Q[227];
        	link.l1 = DLG_TEXT_Q[228];
    		link.l1.go = "Step_59";
		break;

 		case "Step_59":
        	dialog.text = DLG_TEXT_Q[229];
        	link.l1 = DLG_TEXT_Q[230];
    		link.l1.go = "exit";
			LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			pchar.quest.Ascold_LeifIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Ascold_LeifIsDead.win_condition.l1.character = "LeifEricson";
			pchar.quest.Ascold_LeifIsDead.function = "Ascold_LeifIsDead";
			NextDiag.TempNode = "AfterAttackMummy";
    		pchar.questTemp.Ascold = "Ascold_SaveWorld";
			sld = characterFromId("LeifEricson");
            LAi_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_FightGroups(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, true);
		break;

 		case "AfterAttackMummy":
            if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
            {
            	dialog.text = DLG_TEXT_Q[207];
            	link.l1 = DLG_TEXT_Q[208];
        		link.l1.go = "exit";
                NextDiag.TempNode = "AfterAttackMummy";
            }
            if (GetCharacterIndex("LeifEricson") == -1)
            {
            	dialog.text = DLG_TEXT_Q[209];
            	link.l1 = DLG_TEXT_Q[210];
        		link.l1.go = "Step_60";
				NextDiag.TempNode = "First time";
				SelectAscoldRendom();
            }
		break;

 		case "Step_60":
			pchar.questTemp.Ascold.work = 0;
        	dialog.text = DLG_TEXT_Q[231]+
                          DLG_TEXT_Q[232];
        	link.l1 = DLG_TEXT_Q[233];
    		link.l1.go = "Step_61";
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
            	link.l2 = DLG_TEXT_Q[234];
        		link.l2.go = "Step_63";				
            }
		break;

 		case "Step_61":
        	dialog.text = DLG_TEXT_Q[235]+
                          DLG_TEXT_Q[236];
        	link.l1 = DLG_TEXT_Q[237];
    		link.l1.go = "Step_62";
		break;

 		case "Step_62":
        	dialog.text = DLG_TEXT_Q[238];
        	link.l1 = DLG_TEXT_Q[239];
    		link.l1.go = "exit";
            pchar.questTemp.Ascold = "Ascold_OverBusiness";
		break;

 		case "Step_63":
        	dialog.text = DLG_TEXT_Q[244];
        	link.l1 = DLG_TEXT_Q[245];
    		link.l1.go = "BuyAzzy";
        	link.l2 = DLG_TEXT_Q[246];
    		link.l2.go = "Step_62";
		break;

 		case "BuyAzzy":
        	dialog.text = DLG_TEXT_Q[247];
        	link.l1 = DLG_TEXT_Q[248];
    		link.l1.go = "Step_62";
            TakeItemFromCharacter(pchar, "Azzy_bottle");
            AddMoneyToCharacter(pchar, 50000);
		break;
		
 		case "Step_64":
        	dialog.text = DLG_TEXT_Q[249];
        	link.l1 = DLG_TEXT_Q[250];
    		link.l1.go = "Step_65";
		break;
		
 		case "Step_65":
        	dialog.text = DLG_TEXT_Q[251];
        	link.l1 = DLG_TEXT_Q[252];
    		link.l1.go = "Step_66";
		break;

 		case "Step_66":
        	dialog.text = DLG_TEXT_Q[253];
        	link.l1 = DLG_TEXT_Q[254];
    		link.l1.go = "Step_67";
		break;

 		case "Step_67":
        	dialog.text = DLG_TEXT_Q[255];
        	link.l1 = DLG_TEXT_Q[256];
    		link.l1.go = "Step_68";
		break;

 		case "Step_68":
        	dialog.text = DLG_TEXT_Q[257];
        	link.l1 = DLG_TEXT_Q[258];
    		link.l1.go = "Step_69";
		break;

 		case "Step_69":
        	dialog.text = DLG_TEXT_Q[259];
        	link.l1 = DLG_TEXT_Q[260];
    		link.l1.go = "Step_70";
		break;

 		case "Step_70":
            dialog.text = DLG_TEXT_Q[263];
            link.l1 = DLG_TEXT_Q[264];
            link.l1.go = "Step_71";
            pchar.questTemp.Azzy = "DestrContract";
		break;
		
 		case "Step_71":
        	dialog.text = DLG_TEXT_Q[265];
        	link.l1 = DLG_TEXT_Q[266];
    		link.l1.go = "Step_72";
            GiveItem2Character(pchar, "sculMa1");
            GiveItem2Character(pchar, "sculMa2");
            GiveItem2Character(pchar, "sculMa3");
            GiveItem2Character(pchar, "talisman6");
		break;

 		case "Step_72":
        	dialog.text = DLG_TEXT_Q[267];
        	link.l1 = DLG_TEXT_Q[268];
    		link.l1.go = "exit";
		break;
		
		case "Sharlie":
			dialog.text = DLG_TEXT_Q[303];
			link.l1 = DLG_TEXT_Q[304];
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = DLG_TEXT_Q[305];
			link.l1 = DLG_TEXT_Q[306];
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = DLG_TEXT_Q[307];
			link.l1 = DLG_TEXT_Q[308];
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = DLG_TEXT_Q[309];
			link.l1 = DLG_TEXT_Q[310];
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = DLG_TEXT_Q[311];
			link.l1 = DLG_TEXT_Q[312];
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = DLG_TEXT_Q[313];
			link.l1 = DLG_TEXT_Q[314];
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = DLG_TEXT_Q[315];
			link.l1 = DLG_TEXT_Q[316];
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			Log_Info(DLG_TEXT_Q[317]);
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			dialog.text = DLG_TEXT_Q[318];
			link.l1 = DLG_TEXT_Q[319];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_Q[320];
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2"; 
		break;
		
		case "Sharlie_8":
			dialog.text = DLG_TEXT_Q[321];
			link.l1 = DLG_TEXT_Q[322];
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = DLG_TEXT_Q[323];
			link.l1 = DLG_TEXT_Q[324];
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = DLG_TEXT_Q[327];
			link.l1 = DLG_TEXT_Q[328];
			link.l1.go = "Sharlie_12";
			link.l2 = DLG_TEXT_Q[329];
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = DLG_TEXT_Q[330];
			link.l1 = DLG_TEXT_Q[331];
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = DLG_TEXT_Q[332];
			link.l1 = DLG_TEXT_Q[333];
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = DLG_TEXT_Q[334];
			link.l1 = DLG_TEXT_Q[335];
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = DLG_TEXT_Q[336];
			link.l1 = DLG_TEXT_Q[337];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			dialog.text = DLG_TEXT_Q[338];
			link.l1 = DLG_TEXT_Q[339];
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = DLG_TEXT_Q[340];
			link.l1 = DLG_TEXT_Q[341];
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = DLG_TEXT_Q[342];
			link.l1 = DLG_TEXT_Q[343];
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = DLG_TEXT_Q[344];
			link.l1 = DLG_TEXT_Q[345];
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = DLG_TEXT_Q[346];
			link.l1 = DLG_TEXT_Q[347];
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = DLG_TEXT_Q[348];
			if (GetCharacterItem(pchar, "gold_dublon") >= 100)
			{
				link.l1 = DLG_TEXT_Q[349];
				link.l1.go = "Tichingitu_7";
			}
			link.l2 = DLG_TEXT_Q[350];
			link.l2.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = DLG_TEXT_Q[351];
			link.l1 = DLG_TEXT_Q[352];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			RemoveItems(PChar, "gold_dublon", 100);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[353];
			link.l1 = DLG_TEXT_Q[354];
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[355];
			link.l1 = DLG_TEXT_Q[356];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
		break;
		
		case "vodka":
			dialog.text = DLG_TEXT_Q[357];
			link.l1 = DLG_TEXT_Q[358];
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = DLG_TEXT_Q[359];
			link.l1 = DLG_TEXT_Q[360];
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = DLG_TEXT_Q[361];
			link.l1 = DLG_TEXT_Q[362];
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = DLG_TEXT_Q[363];
			link.l1 = DLG_TEXT_Q[364];
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\Russian\sharlie\Fadey Moskovit-04.wav");
			dialog.text = DLG_TEXT_Q[365];
			link.l1 = DLG_TEXT_Q[366];
			link.l1.go = "vodka_no";
			link.l2 = DLG_TEXT_Q[367];
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = DLG_TEXT_Q[368];
			link.l1 = DLG_TEXT_Q[369];
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = DLG_TEXT_Q[370];
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[371];
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = DLG_TEXT_Q[372];
			link.l1 = DLG_TEXT_Q[373];
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = DLG_TEXT_Q[374];
			link.l1 = DLG_TEXT_Q[375];
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = DLG_TEXT_Q[376];
			link.l1 = DLG_TEXT_Q[377];
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = DLG_TEXT_Q[378];
			link.l1 = DLG_TEXT_Q[379];
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = DLG_TEXT_Q[380];
			link.l1 = DLG_TEXT_Q[381];
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = DLG_TEXT_Q[382];
			link.l1 = DLG_TEXT_Q[383];
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = DLG_TEXT_Q[384];
			link.l1 = DLG_TEXT_Q[385];
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = DLG_TEXT_Q[386];
			link.l1 = DLG_TEXT_Q[387];
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_Q[388];
			link.l1 = DLG_TEXT_Q[389];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_Q[390];
			link.l1 = DLG_TEXT_Q[391];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_Q[392];
			link.l1 = DLG_TEXT_Q[393];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_Q[394];
			link.l1 = DLG_TEXT_Q[395];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[396];
			link.l1 = DLG_TEXT_Q[397];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = DLG_TEXT_Q[398];
			link.l1 = DLG_TEXT_Q[399];
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = DLG_TEXT_Q[400];
			link.l1 = DLG_TEXT_Q[401];
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = DLG_TEXT_Q[402]+pchar.name+DLG_TEXT_Q[403];
			link.l1 = DLG_TEXT_Q[404];
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = DLG_TEXT_Q[405]+pchar.name+DLG_TEXT_Q[406];
			link.l1 = DLG_TEXT_Q[407];
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = DLG_TEXT_Q[408];
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = DLG_TEXT_Q[409];
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[410];
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = DLG_TEXT_Q[411];
			link.l1 = DLG_TEXT_Q[412];
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveItems(pchar, "gold_dublon", 250);
			Log_Info(DLG_TEXT_Q[413]);
			GiveItem2Character(pchar, "jewelry34");
			Log_Info(DLG_TEXT_Q[414]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[415];
			link.l1 = DLG_TEXT_Q[416];
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = DLG_TEXT_Q[417];
			link.l1 = DLG_TEXT_Q[418];
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = DLG_TEXT_Q[419]+pchar.name+DLG_TEXT_Q[420];
			link.l1 = DLG_TEXT_Q[421];
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = DLG_TEXT_Q[422];
			link.l1 = DLG_TEXT_Q[423];
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = DLG_TEXT_Q[424]+pchar.name+DLG_TEXT_Q[425];
			link.l1 = DLG_TEXT_Q[426];
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = DLG_TEXT_Q[427];
			link.l1 = DLG_TEXT_Q[428];
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = DLG_TEXT_Q[429];
			link.l1 = DLG_TEXT_Q[430];
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = DLG_TEXT_Q[431];
			link.l1 = DLG_TEXT_Q[432];
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = DLG_TEXT_Q[433]+pchar.name+DLG_TEXT_Q[434];
			link.l1 = DLG_TEXT_Q[435];
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = DLG_TEXT_Q[436];
			link.l1 = DLG_TEXT_Q[437];
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = DLG_TEXT_Q[438]+pchar.name+DLG_TEXT_Q[439];
			link.l1 = DLG_TEXT_Q[440];
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info(DLG_TEXT_Q[441]);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = DLG_TEXT_Q[442]+pchar.name+DLG_TEXT_Q[443];
			link.l1 = DLG_TEXT_Q[444];
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = DLG_TEXT_Q[445]+pchar.name+DLG_TEXT_Q[446]+pchar.name+DLG_TEXT_Q[447];
			link.l1 = DLG_TEXT_Q[448];
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecord("Unique_Goods", "2");
			dialog.text = DLG_TEXT_Q[449];
			link.l1 = DLG_TEXT_Q[450];
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = DLG_TEXT_Q[451];
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = DLG_TEXT_Q[452];
			link.l1 = DLG_TEXT_Q[453];
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info(DLG_TEXT_Q[454]);
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = DLG_TEXT_Q[455];
			link.l1 = DLG_TEXT_Q[456];
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			Log_Info(DLG_TEXT_Q[457]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[458]+pchar.name+DLG_TEXT_Q[459];
			link.l1 = DLG_TEXT_Q[460];
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = DLG_TEXT_Q[461];
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = DLG_TEXT_Q[462]+pchar.name+DLG_TEXT_Q[463];
			link.l1 = DLG_TEXT_Q[464];
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info(DLG_TEXT_Q[465]);
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			dialog.text = DLG_TEXT_Q[466];
			link.l1 = DLG_TEXT_Q[467];
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = DLG_TEXT_Q[468];
			link.l1 = DLG_TEXT_Q[469];
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = DLG_TEXT_Q[470];
			if (GetCharacterItem(pchar, "gold_dublon") >= 700)
			{
				link.l1 = DLG_TEXT_Q[471];
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[472];
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveItems(pchar, "gold_dublon", 700);
			Log_Info(DLG_TEXT_Q[473]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			Log_Info(DLG_TEXT_Q[474]);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = DLG_TEXT_Q[475];
			link.l1 = DLG_TEXT_Q[476];
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = DLG_TEXT_Q[477];
			link.l1 = DLG_TEXT_Q[478];
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			dialog.text = DLG_TEXT_Q[479];
			if (GetCharacterItem(pchar, "gold_dublon") >= 500)
			{
				link.l1 = DLG_TEXT_Q[480];
				link.l1.go = "ropes_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[481];
				link.l1.go = "exit";
			}
		break;
		
		case "ropes_1":
			RemoveItems(pchar, "gold_dublon", 500);
			Log_Info(DLG_TEXT_Q[482]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[483]+pchar.name+DLG_TEXT_Q[484];
			link.l1 = DLG_TEXT_Q[485];
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = DLG_TEXT_Q[486];
			link.l1 = DLG_TEXT_Q[487];
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = DLG_TEXT_Q[488];
				link.l1 = DLG_TEXT_Q[489];
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = DLG_TEXT_Q[490];
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = DLG_TEXT_Q[491];
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = DLG_TEXT_Q[492];
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = DLG_TEXT_Q[493];
				Link.l5.go = "contraband";
            }
			link.l9 = DLG_TEXT_Q[494];
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = DLG_TEXT_Q[495];
			link.l1 = DLG_TEXT_Q[496];
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = DLG_TEXT_Q[497];
				if (GetCharacterItem(pchar, "gold_dublon") >= 300)
				{
					link.l1 = DLG_TEXT_Q[498];
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = DLG_TEXT_Q[499];
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = DLG_TEXT_Q[500];
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = DLG_TEXT_Q[501];
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = DLG_TEXT_Q[502];
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[503];
					if (GetCharacterItem(pchar, "gold_dublon") >= 700)
					{
						link.l1 = DLG_TEXT_Q[504];
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = DLG_TEXT_Q[505];
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info(DLG_TEXT_Q[506]+iTotalTemp+DLG_TEXT_Q[507]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[508];
			link.l1 = DLG_TEXT_Q[509];
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = DLG_TEXT_Q[510];
			if (GetCharacterItem(pchar, "gold_dublon") >= 700)
			{
				Link.l1 = DLG_TEXT_Q[511];
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = DLG_TEXT_Q[512];
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = DLG_TEXT_Q[513];
			Link.l1 = DLG_TEXT_Q[514];
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			RemoveItems(pchar, "gold_dublon", 700);
			Log_Info(DLG_TEXT_Q[515]);
			PlaySound("interface\important_item.wav");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}