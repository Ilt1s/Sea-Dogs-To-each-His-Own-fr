#include "SD\TEXT\DIALOGS\Common_church.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(GetSexPhrase("Malheureusement mon fils","Malheureusement ma fille")+DLG_TEXT_BASE[0], GetSexPhrase("Mon fils","Ma fille")+DLG_TEXT_BASE[1], GetSexPhrase("Mon fils","Ma fille")+DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "Minentown_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = DLG_TEXT_BASE[291];
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[292], DLG_TEXT_BASE[293]);
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[294];
					link.l1 = DLG_TEXT_BASE[295] + NPChar.name + "...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[296];
					link.l1 = "Oui, padre" + DLG_TEXT_BASE[297];
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = DLG_TEXT_BASE[10]+GetSexPhrase("mon fils.","ma fille.");
				link.l1 = DLG_TEXT_BASE[11];
				link.l1.go = "node_3";
				Link.l2 = DLG_TEXT_BASE[12];
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = DLG_TEXT_BASE[13];
				Link.l1 = DLG_TEXT_BASE[14];
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = DLG_TEXT_BASE[15];
			link.l1 = DLG_TEXT_BASE[16];
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = DLG_TEXT_BASE[17];
    			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[21], DLG_TEXT_BASE[22]);
    			link.l1.go = "donation";
    			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[23],DLG_TEXT_BASE[24]+RandPhraseSimple(DLG_TEXT_BASE[25], DLG_TEXT_BASE[26]));
    			link.l2.go = "ispoved";
    			link.l3 = RandPhraseSimple(DLG_TEXT_BASE[27] + RandPhraseSimple(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29]),
                                           DLG_TEXT_BASE[30] + RandPhraseSimple(DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = DLG_TEXT_BASE[298];
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = DLG_TEXT_BASE[299];
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = DLG_TEXT_BASE[300];
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришел в Бриджтаун по направлению
				link.l4 = DLG_TEXT_BASE[301];
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = DLG_TEXT_BASE[302];
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = DLG_TEXT_BASE[303];
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = DLG_TEXT_BASE[304];
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = DLG_TEXT_BASE[305];
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l99 = DLG_TEXT_BASE[33];
			link.l99.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = DLG_TEXT_BASE[306];
			Link.l1 = DLG_TEXT_BASE[307];
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = DLG_TEXT_BASE[308];
			Link.l1 = DLG_TEXT_BASE[309];
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = DLG_TEXT_BASE[310];
			Link.l1 = DLG_TEXT_BASE[311];
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = DLG_TEXT_BASE[312];
			Link.l1 = DLG_TEXT_BASE[313];
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = DLG_TEXT_BASE[314];
			Link.l1 = DLG_TEXT_BASE[315];
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = DLG_TEXT_BASE[316];
			link.l1 = DLG_TEXT_BASE[317];
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = DLG_TEXT_BASE[318];
			link.l1 = DLG_TEXT_BASE[319];
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = DLG_TEXT_BASE[320];
			link.l1 = DLG_TEXT_BASE[321];
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = DLG_TEXT_BASE[322];
			link.l1 = DLG_TEXT_BASE[323];
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = DLG_TEXT_BASE[324];
			link.l1 = DLG_TEXT_BASE[325];
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = DLG_TEXT_BASE[326];
			link.l1 = DLG_TEXT_BASE[327];
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = DLG_TEXT_BASE[328];
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = DLG_TEXT_BASE[329];
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[330];
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = DLG_TEXT_BASE[331];
			link.l1 = DLG_TEXT_BASE[332];
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = DLG_TEXT_BASE[333];
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = DLG_TEXT_BASE[334];
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[335];
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = DLG_TEXT_BASE[336];
			link.l1 = DLG_TEXT_BASE[337];
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = DLG_TEXT_BASE[338];
			link.l1 = DLG_TEXT_BASE[339];
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = DLG_TEXT_BASE[340];
			link.l1 = DLG_TEXT_BASE[341];
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = DLG_TEXT_BASE[342];
			link.l1 = DLG_TEXT_BASE[343];
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = DLG_TEXT_BASE[344];
				link.l1 = DLG_TEXT_BASE[345];
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[346];
				link.l1 = DLG_TEXT_BASE[347];
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = DLG_TEXT_BASE[348];
			link.l1 = DLG_TEXT_BASE[349];
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = DLG_TEXT_BASE[350];
			link.l1 = DLG_TEXT_BASE[351];
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = DLG_TEXT_BASE[352];
			link.l1 = DLG_TEXT_BASE[353];
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = DLG_TEXT_BASE[354];
			link.l1 = DLG_TEXT_BASE[355];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = DLG_TEXT_BASE[356];
			link.l1 = DLG_TEXT_BASE[357];
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = DLG_TEXT_BASE[358];
			link.l1 = DLG_TEXT_BASE[359];
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = DLG_TEXT_BASE[360];
			link.l1 = DLG_TEXT_BASE[361];
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = DLG_TEXT_BASE[362];
			link.l1 = DLG_TEXT_BASE[363];
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = DLG_TEXT_BASE[364];
			link.l1 = DLG_TEXT_BASE[365];
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = DLG_TEXT_BASE[366];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[370];
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[371]);
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[372];
			link.l1 = DLG_TEXT_BASE[373];
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[374], DLG_TEXT_BASE[375], DLG_TEXT_BASE[376]);
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = DLG_TEXT_BASE[377];
			link.l1 = DLG_TEXT_BASE[378];
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = DLG_TEXT_BASE[379];
			link.l1 = DLG_TEXT_BASE[380];
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = DLG_TEXT_BASE[381];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[382], DLG_TEXT_BASE[383]);
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[384];
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = DLG_TEXT_BASE[385];
			link.l1 = DLG_TEXT_BASE[386] + RandPhraseSimple(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]);
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = DLG_TEXT_BASE[387];
				link.l1 = DLG_TEXT_BASE[388];
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = DLG_TEXT_BASE[389];
					link.l1 = DLG_TEXT_BASE[390];
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[391];
					link.l1 = DLG_TEXT_BASE[392];
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase(DLG_TEXT_BASE[393],DLG_TEXT_BASE[394]) +DLG_TEXT_BASE[395];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[396];
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = DLG_TEXT_BASE[397];
			link.l1 = DLG_TEXT_BASE[398];
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[399] + FindRussianMoneyString(iMoneyToCharacter) + DLG_TEXT_BASE[400];
				// ГГ не берет деньги. Плюсанем репу
				link.l1 = DLG_TEXT_BASE[401] + NPChar.name + DLG_TEXT_BASE[402];
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берет деньги
				link.l2 = DLG_TEXT_BASE[403] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[404];
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[405];
				link.l1 = DLG_TEXT_BASE[406] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + ".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = DLG_TEXT_BASE[407];
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("cя","ась"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = DLG_TEXT_BASE[408] + FindRussianMoneyString(iMoneyToCharacter) + DLG_TEXT_BASE[409];
			link.l1 = "Oui, " + LinkRandPhrase(DLG_TEXT_BASE[410], DLG_TEXT_BASE[411]) + DLG_TEXT_BASE[412];
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = DLG_TEXT_BASE[413]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[414];
			link.l1 = DLG_TEXT_BASE[415];
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = DLG_TEXT_BASE[416];
			link.l1 = DLG_TEXT_BASE[417];
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = DLG_TEXT_BASE[418]+ GetSexPhrase(DLG_TEXT_BASE[419],DLG_TEXT_BASE[420]) +DLG_TEXT_BASE[421];
				link.l1 = DLG_TEXT_BASE[422];
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[423];
				link.l1 = DLG_TEXT_BASE[424] + NPChar.name + ".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = DLG_TEXT_BASE[425];
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+ GetSexPhrase(DLG_TEXT_BASE[426],DLG_TEXT_BASE[427]) +" " + PChar.name + DLG_TEXT_BASE[428] + FindRussianMoneyString(iMoneyToCharacter) + DLG_TEXT_BASE[429];
			// При этом варианте репу плюсуем
			link.l1 = DLG_TEXT_BASE[430];
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = DLG_TEXT_BASE[431];
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = DLG_TEXT_BASE[432] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[433];
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = DLG_TEXT_BASE[432] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[434];
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = DLG_TEXT_BASE[435];
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[436];
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[437];
					link.l1 = DLG_TEXT_BASE[438];
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = DLG_TEXT_BASE[439];
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = DLG_TEXT_BASE[440];
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не дает денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[441];
						link.l1 = DLG_TEXT_BASE[442];
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[443];
						link.l1 = DLG_TEXT_BASE[444];
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник дает деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[445] + FindRussianMoneyString(iMoneyToCharacter) + DLG_TEXT_BASE[446];
					link.l1 = DLG_TEXT_BASE[447];
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[448];
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = DLG_TEXT_BASE[449]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[450];
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = DLG_TEXT_BASE[451]+ GetSexPhrase("","") +DLG_TEXT_BASE[452];
				link.l1 = DLG_TEXT_BASE[453];
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[454];
				link.l1 = DLG_TEXT_BASE[455];
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[456]+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[457];
				link.l1 = DLG_TEXT_BASE[458] + NPChar.name + DLG_TEXT_BASE[459];
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = DLG_TEXT_BASE[460];
			link.l1 = DLG_TEXT_BASE[461] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + " !..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[462];
			link.l1 = DLG_TEXT_BASE[463];
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = DLG_TEXT_BASE[464];
			link.l1 = DLG_TEXT_BASE[465];
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[466]+ GetSexPhrase(DLG_TEXT_BASE[467],"") +DLG_TEXT_BASE[468];
			link.l1 = DLG_TEXT_BASE[469];
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = GetSexPhrase("Fort bien, mon fils.","Fort bien, ma fille.") +DLG_TEXT_BASE[34];
			Link.l1 = DLG_TEXT_BASE[35];
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = DLG_TEXT_BASE[36];
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = DLG_TEXT_BASE[37];
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = DLG_TEXT_BASE[38];
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = DLG_TEXT_BASE[39];
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = DLG_TEXT_BASE[40];
			Link.l1 = DLG_TEXT_BASE[41];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[42];
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = DLG_TEXT_BASE[43];
			Link.l1 = DLG_TEXT_BASE[44];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[45];
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = DLG_TEXT_BASE[46];
            Link.l1 = DLG_TEXT_BASE[47];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[48];
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = DLG_TEXT_BASE[49];
            Link.l1 = DLG_TEXT_BASE[50];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[51];
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = DLG_TEXT_BASE[52];
			link.l1 = DLG_TEXT_BASE[53];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[54];
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = DLG_TEXT_BASE[55];
			link.l1 = DLG_TEXT_BASE[56];
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = DLG_TEXT_BASE[57] + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = DLG_TEXT_BASE[58];
			link.l1.go = "ispoved_3";
			link.l2 = DLG_TEXT_BASE[59];
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = DLG_TEXT_BASE[470]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[471];
				link.l1 = DLG_TEXT_BASE[472] + RandPhraseSimple("padre.", DLG_TEXT_BASE[473]) + DLG_TEXT_BASE[474] + PChar.GenQuest.ChurchQuest_1.PriestName + DLG_TEXT_BASE[475] + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + DLG_TEXT_BASE[476];
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			    dialog.text = DLG_TEXT_BASE[64];
			    link.l1 = DLG_TEXT_BASE[65];
			    link.l1.go = "quests"; // ссылка к Ќѕ—
                link.l2 = RandPhraseSimple(DLG_TEXT_BASE[66] + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        DLG_TEXT_BASE[67]);
			    link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple(DLG_TEXT_BASE[68], DLG_TEXT_BASE[69]) + DLG_TEXT_BASE[70]; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = DLG_TEXT_BASE[71];
                link.l4.go = "healthAdd_1";
            }
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
                link.l6 = DLG_TEXT_BASE[72];
                link.l6.go = "GiveLamp";
            }           
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple(DLG_TEXT_BASE[73], DLG_TEXT_BASE[74]) + DLG_TEXT_BASE[75] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = DLG_TEXT_BASE[477]+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = DLG_TEXT_BASE[478]+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+DLG_TEXT_BASE[479];
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = DLG_TEXT_BASE[480];
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			    link.l99 = DLG_TEXT_BASE[87];
			    link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = DLG_TEXT_BASE[481]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[482];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[483]+ GetSexPhrase(DLG_TEXT_BASE[484],"") +"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = DLG_TEXT_BASE[93];
    		link.l2 = DLG_TEXT_BASE[94];
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = DLG_TEXT_BASE[485];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[486];
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = DLG_TEXT_BASE[487] + PChar.GenQuest.ChurchQuest_1.ToName + DLG_TEXT_BASE[488] + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + ", " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Dat") + DLG_TEXT_BASE[489];
			link.l1 = DLG_TEXT_BASE[490] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[491];
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[492];
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = DLG_TEXT_BASE[493]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[494];
				link.l1 = DLG_TEXT_BASE[495] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[496] + PChar.GenQuest.ChurchQuest_1.PriestName + DLG_TEXT_BASE[497];
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = DLG_TEXT_BASE[498]+ GetSexPhrase("Mon fils","Ma fille") +DLG_TEXT_BASE[499];
				link.l1 = DLG_TEXT_BASE[500] + RandPhraseSimple(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[501] + PChar.GenQuest.ChurchQuest_1.PriestName + DLG_TEXT_BASE[502];
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = DLG_TEXT_BASE[503] + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + DLG_TEXT_BASE[504];
			link.l1 = DLG_TEXT_BASE[505] + PChar.GenQuest.ChurchQuest_1.PriestName + DLG_TEXT_BASE[506];
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = DLG_TEXT_BASE[507] + GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[508] + PChar.GenQuest.ChurchQuest_1.PriestName + DLG_TEXT_BASE[509];
			link.l1 = DLG_TEXT_BASE[510] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[511];
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = DLG_TEXT_BASE[512] + GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[513] + sld.Ship.Name + DLG_TEXT_BASE[514] + GetFullName(sld) + DLG_TEXT_BASE[515] + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + DLG_TEXT_BASE[516] + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + DLG_TEXT_BASE[517];
				link.l1 = DLG_TEXT_BASE[518];
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Oh, "+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[519] + PChar.GenQuest.ChurchQuest_1.PriestName + DLG_TEXT_BASE[520] + PChar.GenQuest.ChurchQuest_1.CapFullName + DLG_TEXT_BASE[521] + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + DLG_TEXT_BASE[522] + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + DLG_TEXT_BASE[523];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[524];
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = DLG_TEXT_BASE[525]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[526];
			link.l1 = DLG_TEXT_BASE[527];
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = DLG_TEXT_BASE[528]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[529];
			link.l1 = DLG_TEXT_BASE[530];
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = DLG_TEXT_BASE[531]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[532] + PChar.GenQuest.ChurchQuest_1.CapFullName + DLG_TEXT_BASE[533];
			link.l1 = DLG_TEXT_BASE[534];
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = DLG_TEXT_BASE[535]+ GetSexPhrase(DLG_TEXT_BASE[544],DLG_TEXT_BASE[545]) +DLG_TEXT_BASE[536] + PChar.GenQuest.ChurchQuest_1.CapFullName + DLG_TEXT_BASE[537];
			link.l1 = DLG_TEXT_BASE[538] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[539] + PChar.GenQuest.ChurchQuest_1.CapFullName + DLG_TEXT_BASE[540];
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = DLG_TEXT_BASE[541]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[542];
			link.l1 = "Oh, " + RandPhraseSimple(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[543];
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = DLG_TEXT_BASE[546]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[547];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[548];
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text =DLG_TEXT_BASE[549]+ GetSexPhrase("mon fils","ma fille") +DLG_TEXT_BASE[550];
			link.l1 = DLG_TEXT_BASE[551] + LinkRandPhrase(DLG_TEXT_BASE[367], DLG_TEXT_BASE[368], DLG_TEXT_BASE[369]) + DLG_TEXT_BASE[552];
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+drand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (GetHealthMaxNum(pchar) == 6) // отлично
            {
                dialog.text = DLG_TEXT_BASE[156] + GetHealthNameMaxSmall(pchar) + DLG_TEXT_BASE[157];
    			link.l1 = DLG_TEXT_BASE[158];
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = DLG_TEXT_BASE[159] + GetHealthNameMaxSmall(pchar) + DLG_TEXT_BASE[160];
    			link.l1 = DLG_TEXT_BASE[161];
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = DLG_TEXT_BASE[162];
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = DLG_TEXT_BASE[163];
			link.l1 = DLG_TEXT_BASE[164];
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = DLG_TEXT_BASE[165];
			link.l1 = DLG_TEXT_BASE[166];
			link.l1.go = "healthAdd_3";
			link.l2 = DLG_TEXT_BASE[167];
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = DLG_TEXT_BASE[168];
    			link.l1 = pcharrepphrase(DLG_TEXT_BASE[169], DLG_TEXT_BASE[170]);
    			link.l1.go = "healthAdd_4";
    			link.l2 = DLG_TEXT_BASE[171];
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[172];
    			link.l1    = DLG_TEXT_BASE[173]+RandPhraseSimple(DLG_TEXT_BASE[174], DLG_TEXT_BASE[175]);
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = DLG_TEXT_BASE[176];
			link.l1 = pcharrepphrase(DLG_TEXT_BASE[177], DLG_TEXT_BASE[178]);
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = DLG_TEXT_BASE[179];
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не провер¤ть, тк ¤вно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = DLG_TEXT_BASE[180];
			link.l1 = DLG_TEXT_BASE[181];
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = DLG_TEXT_BASE[202];
			link.l1 = DLG_TEXT_BASE[203];
			link.l1.go = "HostessChurch_call";
			link.l2 = DLG_TEXT_BASE[204];
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return";
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = DLG_TEXT_BASE[205];
					link.l1 = DLG_TEXT_BASE[206];
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[207];
					link.l1 = DLG_TEXT_BASE[208];
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = DLG_TEXT_BASE[209];
					link.l1 = DLG_TEXT_BASE[210];
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[211];
					link.l1 = DLG_TEXT_BASE[212];
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = DLG_TEXT_BASE[213];
				link.l1 = DLG_TEXT_BASE[214];
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[215];
				link.l1 = DLG_TEXT_BASE[216];
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = DLG_TEXT_BASE[217];
			link.l1 = DLG_TEXT_BASE[218];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = DLG_TEXT_BASE[219];
			link.l1 = DLG_TEXT_BASE[220];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = DLG_TEXT_BASE[221];
			link.l1 = DLG_TEXT_BASE[222];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = DLG_TEXT_BASE[223];
			link.l1 = DLG_TEXT_BASE[224];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = DLG_TEXT_BASE[225];
			link.l1 = DLG_TEXT_BASE[226];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = DLG_TEXT_BASE[553];
				link.l1 = DLG_TEXT_BASE[554];
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[555];
				link.l1 = DLG_TEXT_BASE[556];
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = DLG_TEXT_BASE[557];
			link.l1 = DLG_TEXT_BASE[558];
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = DLG_TEXT_BASE[559];
			link.l1 = DLG_TEXT_BASE[560];
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = DLG_TEXT_BASE[561]+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+DLG_TEXT_BASE[562];
			link.l1 = DLG_TEXT_BASE[563];
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = DLG_TEXT_BASE[564];
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = DLG_TEXT_BASE[565];
				link.l1 = DLG_TEXT_BASE[566];
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[567];
				link.l1 = DLG_TEXT_BASE[568];
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = DLG_TEXT_BASE[569];
			link.l1 = DLG_TEXT_BASE[570];
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = DLG_TEXT_BASE[571];
			link.l1 = DLG_TEXT_BASE[572];
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info(DLG_TEXT_BASE[573]+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2А (просто забрать у священника рукописи)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-А (поиск кэпа. О нем есть полная инфа).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-Б (поиск кэпа. Название шипа неизвестно.)"); 
		break;
	}
}