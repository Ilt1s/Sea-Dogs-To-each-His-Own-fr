#include "SD\TEXT\DIALOGS\Common_Brothel.h"
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - drand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = "exit";
				break;
			}
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = DLG_TEXT_BASE[354];
				link.l5 = DLG_TEXT_BASE[355];
				link.l5.go = "Badboy";
				link.l8 = DLG_TEXT_BASE[356];
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = DLG_TEXT_BASE[357]+pchar.GenQuest.Badboy.Brothel.Name+DLG_TEXT_BASE[358];
					link.l5 = DLG_TEXT_BASE[359];
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
				{
					dialog.text = DLG_TEXT_BASE[360];
					link.l5 = DLG_TEXT_BASE[361];
					link.l5.go = "Portugal";
					link.l8 = DLG_TEXT_BASE[362];
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				dialog.text = DLG_TEXT_BASE[363];
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = DLG_TEXT_BASE[364];
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[365];
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = DLG_TEXT_BASE[425];
				link.l1 = RandSwear()+DLG_TEXT_BASE[426];
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = DLG_TEXT_BASE[427];
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = DLG_TEXT_BASE[428];
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[429];
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + DLG_TEXT_BASE[34] + npchar.name + DLG_TEXT_BASE[35] + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + DLG_TEXT_BASE[36]+ NPChar.Name + DLG_TEXT_BASE[37]);
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + DLG_TEXT_BASE[38] + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + DLG_TEXT_BASE[39] + GetAddress_Form(NPChar) + "?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идет квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name + DLG_TEXT_BASE[40];
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идет старт Шарля
			{
				link.l3 = DLG_TEXT_BASE[41];
				link.l3.go = "ForCrew";
			}
			link.l4 = DLG_TEXT_BASE[42];
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = DLG_TEXT_BASE[43] + npchar.name + DLG_TEXT_BASE[44];
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			link.l9 = DLG_TEXT_BASE[45];
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[366],DLG_TEXT_BASE[367]);
				link.l1 = DLG_TEXT_BASE[368] + npchar.name + DLG_TEXT_BASE[369];
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = DLG_TEXT_BASE[370];
				link.l1 = DLG_TEXT_BASE[371];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[372];
				link.l1	= DLG_TEXT_BASE[373];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[374];
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = DLG_TEXT_BASE[46];
					Link.l1 = DLG_TEXT_BASE[47];
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = DLG_TEXT_BASE[48];
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[49];
					Link.l1 = DLG_TEXT_BASE[50];
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[51];
				Link.l1 = DLG_TEXT_BASE[52];
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = DLG_TEXT_BASE[53];
				Link.l1 = DLG_TEXT_BASE[54];
				Link.l1.go = "exit";	
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[55] + GetFullName(sld) + DLG_TEXT_BASE[56]  + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + DLG_TEXT_BASE[57];
					Link.l1 = DLG_TEXT_BASE[58];
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = DLG_TEXT_BASE[59];
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = DLG_TEXT_BASE[60];
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = DLG_TEXT_BASE[61] + sld.name + DLG_TEXT_BASE[62];
				Link.l1 = DLG_TEXT_BASE[63];
				Link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("Les papiers sont  " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[64] + sld.name + DLG_TEXT_BASE[65] + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + DLG_TEXT_BASE[66];
				Link.l1 = DLG_TEXT_BASE[67];
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = DLG_TEXT_BASE[68];
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_BASE[69];
				Link.l1 = DLG_TEXT_BASE[70];
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = DLG_TEXT_BASE[71];
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + DLG_TEXT_BASE[72];
				Link.l1 = DLG_TEXT_BASE[73];
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = DLG_TEXT_BASE[74];
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = DLG_TEXT_BASE[75];
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = DLG_TEXT_BASE[76];
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = DLG_TEXT_BASE[77] + FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost) + ".";			
			link.l1 = DLG_TEXT_BASE[78];
			link.l1.go = "ForCrew_1";
			link.l2 = DLG_TEXT_BASE[79];
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = DLG_TEXT_BASE[80];
			    link.l1 = DLG_TEXT_BASE[81];
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = DLG_TEXT_BASE[101];
			link.l1 = DLG_TEXT_BASE[102];
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = DLG_TEXT_BASE[103];
			link.l1 = DLG_TEXT_BASE[104];
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = DLG_TEXT_BASE[106] + npchar.name + ".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = DLG_TEXT_BASE[145];
			link.l1 = DLG_TEXT_BASE[146];
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришел
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[185], DLG_TEXT_BASE[186], DLG_TEXT_BASE[187]), 
					LinkRandPhrase(DLG_TEXT_BASE[188], DLG_TEXT_BASE[189], DLG_TEXT_BASE[190]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[191], DLG_TEXT_BASE[192]), 
					RandPhraseSimple(DLG_TEXT_BASE[193], DLG_TEXT_BASE[194]));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[195] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[196], 
				DLG_TEXT_BASE[197], 
				DLG_TEXT_BASE[198] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[199], 
				DLG_TEXT_BASE[200] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[201], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[202], DLG_TEXT_BASE[203],
                      DLG_TEXT_BASE[204], DLG_TEXT_BASE[205], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = DLG_TEXT_BASE[206];
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(DLG_TEXT_BASE[207], DLG_TEXT_BASE[208], DLG_TEXT_BASE[209]);
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase(DLG_TEXT_BASE[210], 
					DLG_TEXT_BASE[211], 
					DLG_TEXT_BASE[212]);
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = DLG_TEXT_BASE[430];
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = DLG_TEXT_BASE[217] + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = DLG_TEXT_BASE[218];
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[219], DLG_TEXT_BASE[220], DLG_TEXT_BASE[221]);
				link.l1 = DLG_TEXT_BASE[222];
				Link.l1.go = "Horse_3";		
				Link.l2 = DLG_TEXT_BASE[223];
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[224], DLG_TEXT_BASE[225], DLG_TEXT_BASE[226]);
				link.l1 = DLG_TEXT_BASE[227];
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + DLG_TEXT_BASE[228] + npchar.name + DLG_TEXT_BASE[229];
			Link.l1 = DLG_TEXT_BASE[230];
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[231], 
				DLG_TEXT_BASE[232], 
				DLG_TEXT_BASE[233], 
				DLG_TEXT_BASE[234], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[235], DLG_TEXT_BASE[236],
                      DLG_TEXT_BASE[237], DLG_TEXT_BASE[238], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[239], 
					DLG_TEXT_BASE[240], 
					DLG_TEXT_BASE[241], 
					DLG_TEXT_BASE[242], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[243], DLG_TEXT_BASE[244],
						DLG_TEXT_BASE[245], DLG_TEXT_BASE[246], npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[247];
				Link.l1 = DLG_TEXT_BASE[248];
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[249], 
						DLG_TEXT_BASE[250], 
						DLG_TEXT_BASE[251], 
						DLG_TEXT_BASE[252], "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[253], DLG_TEXT_BASE[254],
							DLG_TEXT_BASE[255], DLG_TEXT_BASE[256], npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[257];
					Link.l1 = DLG_TEXT_BASE[258];
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[259];
				Link.l1 = DLG_TEXT_BASE[260];
				Link.l1.go = "exit";
				Link.l2 = DLG_TEXT_BASE[261];
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[262], 
					DLG_TEXT_BASE[263], 
					DLG_TEXT_BASE[264], 
					DLG_TEXT_BASE[265], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[266], DLG_TEXT_BASE[267],
						DLG_TEXT_BASE[268], DLG_TEXT_BASE[269], npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[270];
				Link.l1 = DLG_TEXT_BASE[271];
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = DLG_TEXT_BASE[272];
			Link.l1 = DLG_TEXT_BASE[273];
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = DLG_TEXT_BASE[431];
				Link.l1 = DLG_TEXT_BASE[432];
				Link.l1.go = "mtraxx_2";
				break;
			}		
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[274], DLG_TEXT_BASE[275]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[276], DLG_TEXT_BASE[277]);
				break;
				case "1":
					dialog.text = DLG_TEXT_BASE[278];
					Link.l1 = DLG_TEXT_BASE[279];	
				break;
				case "2":
					dialog.text = DLG_TEXT_BASE[280];
					Link.l1 = DLG_TEXT_BASE[281];
				break;
			}
			Link.l1.go = "exit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(pchar, 23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
				else 												AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = DLG_TEXT_BASE[375];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[376], DLG_TEXT_BASE[377], RandPhraseSimple(DLG_TEXT_BASE[378], DLG_TEXT_BASE[379]+ GetSexPhrase(DLG_TEXT_BASE[380],DLG_TEXT_BASE[381]) +DLG_TEXT_BASE[382]));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase(DLG_TEXT_BASE[383],DLG_TEXT_BASE[384]) +".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase(DLG_TEXT_BASE[282], DLG_TEXT_BASE[283], DLG_TEXT_BASE[284]);
						Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[285], DLG_TEXT_BASE[286]);
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase(DLG_TEXT_BASE[289], DLG_TEXT_BASE[290], DLG_TEXT_BASE[291]);
						Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[292], DLG_TEXT_BASE[293]);	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[294], DLG_TEXT_BASE[295]);
						Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[296], DLG_TEXT_BASE[297]);
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = DLG_TEXT_BASE[385];
				link.l1 = DLG_TEXT_BASE[386];
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[298], DLG_TEXT_BASE[299], DLG_TEXT_BASE[300]);
				Link.l1 = DLG_TEXT_BASE[301];
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = DLG_TEXT_BASE[387];
			link.l1 = DLG_TEXT_BASE[388];
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = DLG_TEXT_BASE[389];
			link.l1 = DLG_TEXT_BASE[390];
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = DLG_TEXT_BASE[391]+ GetSexPhrase(DLG_TEXT_BASE[392],DLG_TEXT_BASE[393]) +DLG_TEXT_BASE[394];
			link.l1 = DLG_TEXT_BASE[395];
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = DLG_TEXT_BASE[396];
			link.l1 = DLG_TEXT_BASE[397]+ GetSexPhrase(DLG_TEXT_BASE[398],DLG_TEXT_BASE[399]) +DLG_TEXT_BASE[400]+ GetSexPhrase(DLG_TEXT_BASE[401],DLG_TEXT_BASE[402]) +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true; 
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[313], 
					DLG_TEXT_BASE[314], 
					DLG_TEXT_BASE[315]);
				link.l1 = DLG_TEXT_BASE[316];
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = DLG_TEXT_BASE[317];
					link.l1 = DLG_TEXT_BASE[318];
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[319], 
						DLG_TEXT_BASE[320], 
						DLG_TEXT_BASE[321]);
					link.l1 = DLG_TEXT_BASE[322];
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = DLG_TEXT_BASE[323];
			link.l1 = DLG_TEXT_BASE[324];
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = DLG_TEXT_BASE[325];
			link.l1 = DLG_TEXT_BASE[326];
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = DLG_TEXT_BASE[327];
			link.l1 = DLG_TEXT_BASE[328];
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = DLG_TEXT_BASE[329];
				link.l1 = DLG_TEXT_BASE[330];
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[331];
				link.l1 = DLG_TEXT_BASE[332];
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = DLG_TEXT_BASE[333];
			link.l1 = DLG_TEXT_BASE[334];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = DLG_TEXT_BASE[403]+pchar.GenQuest.Badboy.Brothel.Name+DLG_TEXT_BASE[404];
			link.l1 = DLG_TEXT_BASE[405];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[406];
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = DLG_TEXT_BASE[407];
			link.l1 = DLG_TEXT_BASE[408];
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = DLG_TEXT_BASE[409];
			link.l1 = DLG_TEXT_BASE[410];
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = DLG_TEXT_BASE[411];
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = DLG_TEXT_BASE[412];
			link.l1 = DLG_TEXT_BASE[413];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_BASE[414]+DLG_TEXT_BASE[415];
			link.l1 = DLG_TEXT_BASE[416];
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			//создаем Хьюго
			sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
			sld.name = "Hugo";
			sld.lastname = "Avendell";
			sld.dialog.FileName = "Quest\Portugal_dialog.c";
			sld.dialog.currentnode = "Avendel_tavern";
			sld.greeting = "avendel_1";
			sld.rank = 12;
			LAi_SetHP(sld, 80, 80);
			SetSelfSkill(sld, 10, 12, 10, 10, 70);
			SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
			SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			TakeNItems(sld, "bullet", 10);
			AddItems(sld, "gunpowder", 10);
			LAi_SetCharacterUseBullet(sld, "bullet");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetImmortal(sld, true);
			LAi_SetSitType(sld);
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = DLG_TEXT_BASE[417];
			link.l1 = DLG_TEXT_BASE[418];
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = DLG_TEXT_BASE[419];
			link.l1 = DLG_TEXT_BASE[420];
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = DLG_TEXT_BASE[421]+DLG_TEXT_BASE[422]+DLG_TEXT_BASE[423];
			link.l1 = DLG_TEXT_BASE[424];
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
				
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = DLG_TEXT_BASE[433];
			link.l1 = DLG_TEXT_BASE[434];
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = DLG_TEXT_BASE[435];
			link.l1 = DLG_TEXT_BASE[436];
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = DLG_TEXT_BASE[437];
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = DLG_TEXT_BASE[438];
			link.l1 = DLG_TEXT_BASE[439];
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = DLG_TEXT_BASE[440];
			link.l1 = DLG_TEXT_BASE[441];
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = DLG_TEXT_BASE[442];
			link.l1 = DLG_TEXT_BASE[443];
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = DLG_TEXT_BASE[444];
			link.l1 = DLG_TEXT_BASE[445];
			link.l1.go = "exit";
			sTotalTemp = npchar.id;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(pchar, 23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
				else 												AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_R":
            dialog.text = DLG_TEXT_BASE[446];
			link.l1 = DLG_TEXT_BASE[447];
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = DLG_TEXT_BASE[448];
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = DLG_TEXT_BASE[449];
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[450];
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = DLG_TEXT_BASE[451];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" || sti(rCharacter.location == City+"_Brothel" && rCharacter.id == "GigoloGirl"))
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}