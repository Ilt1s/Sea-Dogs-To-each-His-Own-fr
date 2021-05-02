#include "SD\TEXT\DIALOGS\Habitue_dialog.h"
#include "SD\DIALOGS\russian\Common_Duel.c" //navy
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
			link.l1.go = "Beta_test_alc";
            link.l2 = DLG_TEXT_BASE[2];
			link.l2.go = "Beta_test_card";
			link.l3 = DLG_TEXT_BASE[3];
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = DLG_TEXT_BASE[4];
			link.l1 = DLG_TEXT_BASE[5];
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = DLG_TEXT_BASE[6];
			link.l1 = DLG_TEXT_BASE[7];
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = DLG_TEXT_BASE[8];
			link.l1 = DLG_TEXT_BASE[9];
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11] , DLG_TEXT_BASE[12]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[13], DLG_TEXT_BASE[14]); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, "+ GetSexPhrase("monsieur","mademoiselle") +DLG_TEXT_BASE[184];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[185],DLG_TEXT_BASE[186],DLG_TEXT_BASE[187]);
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[188];
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = DLG_TEXT_BASE[15];
            link.l1 = DLG_TEXT_BASE[16];
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = DLG_TEXT_BASE[17];
						link.l1 = DLG_TEXT_BASE[18];
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = DLG_TEXT_BASE[19];
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = DLG_TEXT_BASE[20];
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[21], DLG_TEXT_BASE[22]);
										link.l1 = DLG_TEXT_BASE[23];
										link.l1.go = "Cards_begin";
										link.l2 = DLG_TEXT_BASE[24];
										link.l2.go = "Cards_Rule";
										link.l3 = DLG_TEXT_BASE[25];
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = DLG_TEXT_BASE[26];
						    			link.l1 = DLG_TEXT_BASE[27];
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29]);
										link.l1 = DLG_TEXT_BASE[30];
										link.l1.go = "Dice_begin";
										link.l2 = DLG_TEXT_BASE[31];
										link.l2.go = "Dice_Rule";
										link.l3 = DLG_TEXT_BASE[32];
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = DLG_TEXT_BASE[33];
					    				link.l1 = DLG_TEXT_BASE[34];
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear() + DLG_TEXT_BASE[35];
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple(DLG_TEXT_BASE[36], DLG_TEXT_BASE[37]);
	                        link.l1 = RandPhraseSimple(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]);
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple(DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]);
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = DLG_TEXT_BASE[189]+ GetSexPhrase(DLG_TEXT_BASE[190],DLG_TEXT_BASE[191]) +DLG_TEXT_BASE[192]+ GetSexPhrase(DLG_TEXT_BASE[193],DLG_TEXT_BASE[194]) +". ";
			link.l1 = DLG_TEXT_BASE[195];
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = GetConvertStr("CARDS_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[42];
			link.l1.go = "Cards_begin";
			link.l3 = DLG_TEXT_BASE[43];
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = DLG_TEXT_BASE[44];
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = DLG_TEXT_BASE[47];
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[48];
                link.l1 = DLG_TEXT_BASE[49];
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = DLG_TEXT_BASE[50];
                link.l1 = DLG_TEXT_BASE[51];
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = DLG_TEXT_BASE[52];
                link.l1 = DLG_TEXT_BASE[53];
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = DLG_TEXT_BASE[196] + iLa_Puesta + DLG_TEXT_BASE[197];
				link.l1 = DLG_TEXT_BASE[198];
				link.l1.go = "Cards_begin_2";
				link.l2 = DLG_TEXT_BASE[199];
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = DLG_TEXT_BASE[200];
				link.l1 = DLG_TEXT_BASE[201];
				link.l1.go = "Cards_begin_2";
				link.l2 = DLG_TEXT_BASE[202];
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[54] + iLa_Puesta + " pesos.";
			link.l1 = DLG_TEXT_BASE[55];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = DLG_TEXT_BASE[44];
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = DLG_TEXT_BASE[45];
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = GetConvertStr("DICE_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "Dice_begin";
			link.l3 = DLG_TEXT_BASE[68];
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = DLG_TEXT_BASE[69];
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = DLG_TEXT_BASE[72];
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[73];
                link.l1 = DLG_TEXT_BASE[74];
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = DLG_TEXT_BASE[75];
                link.l1 = DLG_TEXT_BASE[76];
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = DLG_TEXT_BASE[77];
                link.l1 = DLG_TEXT_BASE[78];
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = DLG_TEXT_BASE[203] + iLa_Puesta + DLG_TEXT_BASE[204];
				link.l1 = DLG_TEXT_BASE[205];
				link.l1.go = "Dice_begin_2";
				link.l2 = DLG_TEXT_BASE[206];
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = DLG_TEXT_BASE[207];
				link.l1 = DLG_TEXT_BASE[208];
				link.l1.go = "Dice_begin_2";
				link.l2 = DLG_TEXT_BASE[209];
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Bien, va pour " + iLa_Puesta + DLG_TEXT_BASE[79];
			link.l1 = DLG_TEXT_BASE[80];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			Dialog.text = DLG_TEXT_BASE[69];
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = DLG_TEXT_BASE[72];
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
       case "talk_with_alchogol_song":
			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = DLG_TEXT_BASE[125];
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = DLG_TEXT_BASE[126];
			link.l1 = DLG_TEXT_BASE[127];
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = DLG_TEXT_BASE[128];
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = DLG_TEXT_BASE[129];
			link.l1 = DLG_TEXT_BASE[130];
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[131],
						DLG_TEXT_BASE[210] + GetAddress_Form(npchar) + DLG_TEXT_BASE[211],
						DLG_TEXT_BASE[212]+ GetSexPhrase(DLG_TEXT_BASE[213],DLG_TEXT_BASE[214]) +DLG_TEXT_BASE[215]+ GetSexPhrase(DLG_TEXT_BASE[216],DLG_TEXT_BASE[217]) +".");
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = DLG_TEXT_BASE[218];
				link.l1 = DLG_TEXT_BASE[219];
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = DLG_TEXT_BASE[220];
				link.l1 = DLG_TEXT_BASE[221];
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = DLG_TEXT_BASE[222];
				link.l1 = DLG_TEXT_BASE[223];
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = DLG_TEXT_BASE[224];
				link.l1 = DLG_TEXT_BASE[225];
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = DLG_TEXT_BASE[226];
				link.l1 = DLG_TEXT_BASE[227];
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo(DLG_TEXT_BASE[228] + sGenLocation + DLG_TEXT_BASE[229]);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = DLG_TEXT_BASE[230];
				link.l1 = DLG_TEXT_BASE[231];
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = DLG_TEXT_BASE[232];
				link.l1 = DLG_TEXT_BASE[233];
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = DLG_TEXT_BASE[234]+ GetSexPhrase(DLG_TEXT_BASE[235],DLG_TEXT_BASE[236]) +DLG_TEXT_BASE[237];
				link.l1 = DLG_TEXT_BASE[238];
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = DLG_TEXT_BASE[239];
				link.l1 = DLG_TEXT_BASE[240];
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = DLG_TEXT_BASE[241];
				link.l1 = DLG_TEXT_BASE[242];
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = DLG_TEXT_BASE[243] + pchar.questTemp.Slavetrader.ShipName + ".";
				link.l1 = DLG_TEXT_BASE[244];
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = DLG_TEXT_BASE[245];
				link.l1 = DLG_TEXT_BASE[246];
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			dialog.text = DLG_TEXT_BASE[247];
			link.l1 = DLG_TEXT_BASE[248];
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = DLG_TEXT_BASE[249];
			link.l1 = DLG_TEXT_BASE[250];
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = DLG_TEXT_BASE[251];
			link.l1 = DLG_TEXT_BASE[252];
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = DLG_TEXT_BASE[253];
			link.l1 = DLG_TEXT_BASE[254];
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = DLG_TEXT_BASE[255];
			link.l1 = DLG_TEXT_BASE[256];
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = DLG_TEXT_BASE[257];
			link.l1 = DLG_TEXT_BASE[258];
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = DLG_TEXT_BASE[259];
			link.l1 = DLG_TEXT_BASE[260];
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = DLG_TEXT_BASE[261];
			link.l1 = DLG_TEXT_BASE[262];
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ha ! "+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[263];
				link.l1 = DLG_TEXT_BASE[264];
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[265];
				link.l1 = DLG_TEXT_BASE[266];
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = DLG_TEXT_BASE[267]+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+DLG_TEXT_BASE[268];
			link.l1 = DLG_TEXT_BASE[269];
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = DLG_TEXT_BASE[270];
			link.l1 = DLG_TEXT_BASE[271];
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = DLG_TEXT_BASE[272];
			link.l1 = DLG_TEXT_BASE[273];
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = DLG_TEXT_BASE[274];
			link.l1 = DLG_TEXT_BASE[275];
			link.l1.go = "exit_sit";
			pchar.questTemp.Trial = "spy_drink";
			AddQuestRecord("Trial", "14");
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[133],
			                             DLG_TEXT_BASE[134],
										 DLG_TEXT_BASE[135]);
			link.l1 = DLG_TEXT_BASE[136];
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = DLG_TEXT_BASE[137];
				link.l2.go = "sit_3";
			}

			//if (sti(pchar.reputation) < 41)
            //{
            //    link.l3 = DLG_TEXT_BASE[138];
			//	link.l3.go = "Find_Merchant_1";
            //}
            //homo 15/06/06 слухи
            link.l4 = LinkRandPhrase(DLG_TEXT_BASE[139],
                                    DLG_TEXT_BASE[140],
                                    DLG_TEXT_BASE[141]);
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[142];
					link.l1 = DLG_TEXT_BASE[143];
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[152];
					link.l1 = DLG_TEXT_BASE[153];
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = DLG_TEXT_BASE[159];
					link.l1 = DLG_TEXT_BASE[160];
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[276] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[277],
							DLG_TEXT_BASE[144]);
						link.l1 = DLG_TEXT_BASE[278];
						link.l1.go = "exit_sit";						
						link.l2 = DLG_TEXT_BASE[279];
						link.l2.go = "sit_case_2_enemy";
						link.l3 = DLG_TEXT_BASE[280];
						link.l3.go = "sit_case_2_enemy2";
					}
					else
					{
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[281],
							DLG_TEXT_BASE[282]);
						link.l1 = DLG_TEXT_BASE[283];	
						link.l1.go = "exit_sit";
						link.l2 = DLG_TEXT_BASE[284];
						link.l2.go = "sit_case_2_enemy1";
						link.l3 = DLG_TEXT_BASE[146];
						link.l3.go = "sit_case_2_enemy2";
					}
					link.l4 = DLG_TEXT_BASE[145];
					link.l4.go = "sit_case_2_friend";					
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[147];
					link.l1 = DLG_TEXT_BASE[148];
					link.l1.go = "exit_sit";
					link.l2 = DLG_TEXT_BASE[149];
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) )
					{
					dialog.text = DLG_TEXT_BASE[150];
					link.l1 = DLG_TEXT_BASE[151];
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = DLG_TEXT_BASE[150];
						link.l1 = "Hic* " + DLG_TEXT_BASE[151];
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = DLG_TEXT_BASE[161];
			link.l1 = DLG_TEXT_BASE[162];
			link.l1.go = "exit_sit";
			link.l2 = DLG_TEXT_BASE[163];
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = DLG_TEXT_BASE[164];
			link.l1 = DLG_TEXT_BASE[165];
			link.l1.go = "exit_sit";
			link.l2 = DLG_TEXT_BASE[166];
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = DLG_TEXT_BASE[167];
			link.l1 = DLG_TEXT_BASE[168];
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = DLG_TEXT_BASE[285];
			link.l1 = DLG_TEXT_BASE[286];
			link.l1.go = "exit_sit1";
			link.l2 = DLG_TEXT_BASE[287];
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = DLG_TEXT_BASE[288];
			link.l1 = DLG_TEXT_BASE[289];
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear() + DLG_TEXT_BASE[290];
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[291], RandSwear() + DLG_TEXT_BASE[169],DLG_TEXT_BASE[292]);
				link.l1 = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[293],DLG_TEXT_BASE[294]), RandPhraseSimple(DLG_TEXT_BASE[295],DLG_TEXT_BASE[296]));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[297];
				link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_BASE[298],DLG_TEXT_BASE[299]);
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[300], RandSwear() + DLG_TEXT_BASE[169],DLG_TEXT_BASE[301]);
				link.l1 = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[302],DLG_TEXT_BASE[303]), RandPhraseSimple(DLG_TEXT_BASE[304],DLG_TEXT_BASE[305]));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[306];
				link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_BASE[307],DLG_TEXT_BASE[308]);
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
