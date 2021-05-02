#include "SD\TEXT\DIALOGS\Quest_Mayor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_MR[323],
                         DLG_TEXT_MR[324], DLG_TEXT_MR[325],
                         DLG_TEXT_MR[326], "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[327],
                                               DLG_TEXT_MR[627],
                                               DLG_TEXT_MR[628],
                                               "Oups...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_MR[510], DLG_TEXT_MR[511]);
				link.l1 = RandPhraseSimple(DLG_TEXT_MR[512], DLG_TEXT_MR[513]);
				link.l1.go = "pirate_town";
				break;
			}
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = DLG_TEXT_MR[629];
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = DLG_TEXT_MR[630];
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = DLG_TEXT_MR[516];
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = DLG_TEXT_MR[517];
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = DLG_TEXT_MR[518];
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = DLG_TEXT_MR[631];
			link.l1 = DLG_TEXT_MR[632];
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = DLG_TEXT_MR[633];
			link.l1 = DLG_TEXT_MR[634];
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = DLG_TEXT_MR[635];
			link.l1 = DLG_TEXT_MR[636];
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = DLG_TEXT_MR[637];
			link.l1 = DLG_TEXT_MR[638];
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = DLG_TEXT_MR[639];
			link.l1 = DLG_TEXT_MR[640];
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = DLG_TEXT_MR[641];
			link.l1 = DLG_TEXT_MR[642];
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = DLG_TEXT_MR[643];
			link.l1 = DLG_TEXT_MR[644];
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = DLG_TEXT_MR[645];
			link.l1 = DLG_TEXT_MR[646];
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = DLG_TEXT_MR[647];
			link.l1 = DLG_TEXT_MR[648];
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = DLG_TEXT_MR[649];
			link.l1 = DLG_TEXT_MR[650];
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = DLG_TEXT_MR[651];
			link.l1 = DLG_TEXT_MR[652];
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = DLG_TEXT_MR[653];
			link.l1 = DLG_TEXT_MR[654];
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = DLG_TEXT_MR[655];
			link.l1 = DLG_TEXT_MR[656];
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + DLG_TEXT_MR[519],
                         DLG_TEXT_MR[520], DLG_TEXT_MR[521],
                         DLG_TEXT_MR[522]+ GetSexPhrase(DLG_TEXT_MR[523],DLG_TEXT_MR[524]) +DLG_TEXT_MR[525], "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[526],
                                               DLG_TEXT_MR[527],
                                               DLG_TEXT_MR[528],
                                               DLG_TEXT_MR[529], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_MR[657], DLG_TEXT_MR[658]);
				link.l1 = RandPhraseSimple(DLG_TEXT_MR[659], DLG_TEXT_MR[660]);
				link.l1.go = "pirate_town";
				break;
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = DLG_TEXT_MR[661];
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
			{
				link.l1 = DLG_TEXT_MR[662];
				link.l1.go = "CapComission3";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				link.l1 = DLG_TEXT_MR[663];
				link.l1.go = "CapComission6";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = DLG_TEXT_MR[555];
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Est-il ici ?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = DLG_TEXT_MR[556];
				link.l1 = DLG_TEXT_MR[557];
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = DLG_TEXT_MR[558];
				link.l1 = DLG_TEXT_MR[559];
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = DLG_TEXT_MR[560];
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = DLG_TEXT_MR[561];
			link.l1 = DLG_TEXT_MR[562];
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = DLG_TEXT_MR[563];
			link.l1 = DLG_TEXT_MR[564]; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = DLG_TEXT_MR[565];
			link.l1 = DLG_TEXT_MR[566];
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = DLG_TEXT_MR[567];
				link.l1 = DLG_TEXT_MR[568];
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = DLG_TEXT_MR[569] + pchar.name + DLG_TEXT_MR[570];
				link.l1 = DLG_TEXT_MR[571];
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = DLG_TEXT_MR[572];
			link.l1 = DLG_TEXT_MR[573];
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = DLG_TEXT_MR[574] + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + DLG_TEXT_MR[575] + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + DLG_TEXT_MR[576] + sLoc + DLG_TEXT_MR[577];
			link.l1 = DLG_TEXT_MR[578];
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = DLG_TEXT_MR[579];
			link.l1 = DLG_TEXT_MR[580];
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = DLG_TEXT_MR[581];
			link.l1 = DLG_TEXT_MR[582];
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = DLG_TEXT_MR[583];
			link.l1 = DLG_TEXT_MR[584];
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = DLG_TEXT_MR[585] + GetFullName(pchar) + DLG_TEXT_MR[586];
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = DLG_TEXT_MR[587];
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = DLG_TEXT_MR[588];
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = DLG_TEXT_MR[589];
			link.l1 = DLG_TEXT_MR[590];
			link.l1.go = "CapComission4_1";
			link.l2 = DLG_TEXT_MR[591];
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = DLG_TEXT_MR[592];
			link.l1 = DLG_TEXT_MR[593];
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = DLG_TEXT_MR[594];
			link.l1 = DLG_TEXT_MR[595];
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = DLG_TEXT_MR[596];
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = DLG_TEXT_MR[597];
			link.l1 = DLG_TEXT_MR[598];
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = DLG_TEXT_MR[599];
			link.l1 = DLG_TEXT_MR[600];
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = DLG_TEXT_MR[601];			
			link.l1 = DLG_TEXT_MR[602]+ NPChar.name +DLG_TEXT_MR[603];
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = DLG_TEXT_MR[604];
				link.l2.go = "CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_MR[605]+ GetSexPhrase(DLG_TEXT_MR[606],DLG_TEXT_MR[607]) +"...", DLG_TEXT_MR[608], DLG_TEXT_MR[609]);
			link.l1 = LinkRandPhrase(DLG_TEXT_MR[610], DLG_TEXT_MR[611], DLG_TEXT_MR[612]);
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[613],DLG_TEXT_MR[614]);
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[615];
        			link.l1 = DLG_TEXT_MR[616];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = DLG_TEXT_MR[617]);
			link.l1 = RandPhraseSimple(DLG_TEXT_MR[618], DLG_TEXT_MR[619]);
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[620];
        			link.l1 = DLG_TEXT_MR[621];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = DLG_TEXT_MR[622];
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = DLG_TEXT_MR[623];
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = DLG_TEXT_MR[624];
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = DLG_TEXT_MR[625];
			link.l1 = DLG_TEXT_MR[626];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}