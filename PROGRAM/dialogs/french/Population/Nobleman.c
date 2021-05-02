#include "SD\TEXT\DIALOGS\Common_population.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[436]+NationNameGenitive(sti(pchar.nation))+DLG_TEXT_BASE[437], 
					DLG_TEXT_BASE[438]+NationNameAblative(sti(pchar.nation))+DLG_TEXT_BASE[439], 
					DLG_TEXT_BASE[440],
					DLG_TEXT_BASE[441], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[496], 
					DLG_TEXT_BASE[442],
					DLG_TEXT_BASE[443], 
					DLG_TEXT_BASE[444], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[445], 
					DLG_TEXT_BASE[446], 
					DLG_TEXT_BASE[447],
					DLG_TEXT_BASE[448], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[497], 
					DLG_TEXT_BASE[449],
					DLG_TEXT_BASE[450], 
					DLG_TEXT_BASE[451], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//дворянин-пассажир
				{
					dialog.text = DLG_TEXT_BASE[452]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[453];
					link.l1 = DLG_TEXT_BASE[454]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[455];
					link.l1.go = "passenger";
					link.l2 = DLG_TEXT_BASE[456]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[457];
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = DLG_TEXT_BASE[458];
					link.l1 = DLG_TEXT_BASE[459];
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = DLG_TEXT_BASE[460]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[461];
					link.l1 = DLG_TEXT_BASE[462];
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = DLG_TEXT_BASE[463];
					link.l1 = ""+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[464]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[465], DLG_TEXT_BASE[466]);
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[467];
				link.l1.go = "question";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[468],DLG_TEXT_BASE[469]);
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[470], 
					DLG_TEXT_BASE[471], 
					DLG_TEXT_BASE[472],
					DLG_TEXT_BASE[473], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[474], 
					DLG_TEXT_BASE[475],
					DLG_TEXT_BASE[476], 
					DLG_TEXT_BASE[477], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[478],DLG_TEXT_BASE[479],DLG_TEXT_BASE[480]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[481],DLG_TEXT_BASE[482],DLG_TEXT_BASE[483]);
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			dialog.text = DLG_TEXT_BASE[484] + XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City)+DLG_TEXT_BASE[485]+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+DLG_TEXT_BASE[486]+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+DLG_TEXT_BASE[487]+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+DLG_TEXT_BASE[488];
			link.l1 = DLG_TEXT_BASE[489];
			link.l1.go = "passenger_1";
			link.l2 = DLG_TEXT_BASE[490]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[491];
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = DLG_TEXT_BASE[492];
			link.l1 = DLG_TEXT_BASE[493];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = DLG_TEXT_BASE[494];
			link.l1 = DLG_TEXT_BASE[495]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[496];
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + DLG_TEXT_BASE[499] + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = DLG_TEXT_BASE[500];
			link.l1 =  DLG_TEXT_BASE[501]+GetAddress_FormToNPC(NPChar)+ DLG_TEXT_BASE[502];
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = DLG_TEXT_BASE[503]+sTemp+ DLG_TEXT_BASE[504];
			link.l1 = DLG_TEXT_BASE[505];
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = drand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text =  DLG_TEXT_BASE[506]+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+ DLG_TEXT_BASE[507];
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = DLG_TEXT_BASE[508];
				link.l1.go = "donation_2";
			}
			link.l2 = DLG_TEXT_BASE[509];
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = DLG_TEXT_BASE[510]+GetAddress_Form(NPChar)+ DLG_TEXT_BASE[511];
			link.l1 = DLG_TEXT_BASE[512];
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text =  DLG_TEXT_BASE[513]+pchar.GenQuest.Noblelombard.Item+ DLG_TEXT_BASE[514];
			link.l1 = DLG_TEXT_BASE[515]+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text =  DLG_TEXT_BASE[516]+pchar.GenQuest.Noblelombard.Text+ DLG_TEXT_BASE[517];
			link.l1 = DLG_TEXT_BASE[518];
			link.l1.go = "lombard_2";
			link.l2 = DLG_TEXT_BASE[519];
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = DLG_TEXT_BASE[520];
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+drand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = drand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = DLG_TEXT_BASE[521]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[522];
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = DLG_TEXT_BASE[523];
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = DLG_TEXT_BASE[524];
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = DLG_TEXT_BASE[525];
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = DLG_TEXT_BASE[526]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[527];
				link.l1 = DLG_TEXT_BASE[528];
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[529]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[530];
				link.l1 = DLG_TEXT_BASE[531];
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+DLG_TEXT_BASE[532];
			link.l1 = DLG_TEXT_BASE[533]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[534];
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = DLG_TEXT_BASE[535]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[536];
			link.l1 = DLG_TEXT_BASE[537];
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = DLG_TEXT_BASE[538];
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+drand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+drand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = DLG_TEXT_BASE[539]+LinkRandPhrase(DLG_TEXT_BASE[540],DLG_TEXT_BASE[541],DLG_TEXT_BASE[542])+DLG_TEXT_BASE[543]+sti(npchar.quest.slaves.qty)+DLG_TEXT_BASE[544]+sti(npchar.quest.slaves.price)+"."+DLG_TEXT_BASE[545];
			link.l1 = DLG_TEXT_BASE[546];
			link.l1.go = "slaves_1";
			link.l2 = DLG_TEXT_BASE[547];
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = DLG_TEXT_BASE[548];
			link.l1 = DLG_TEXT_BASE[549]+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = DLG_TEXT_BASE[550]+sti(npchar.quest.slaves.qty)+DLG_TEXT_BASE[551];
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = DLG_TEXT_BASE[552];
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[553];
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[554];
				link.l1 = DLG_TEXT_BASE[555];
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = DLG_TEXT_BASE[556];
			link.l1 = DLG_TEXT_BASE[557];
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = DLG_TEXT_BASE[558]+sti(npchar.quest.slaves.price)+DLG_TEXT_BASE[559];
			link.l1 = DLG_TEXT_BASE[560];
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info(DLG_TEXT_BASE[561]+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[562];
			link.l1 = DLG_TEXT_BASE[563]+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[564], DLG_TEXT_BASE[565]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[566],DLG_TEXT_BASE[567],DLG_TEXT_BASE[568]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = DLG_TEXT_BASE[569] break;
		case 1: sText = DLG_TEXT_BASE[570] break;
		case 2: sText = DLG_TEXT_BASE[571] break;
		case 3: sText = DLG_TEXT_BASE[572] break;
		case 4: sText = DLG_TEXT_BASE[573] break;
		case 5: sText = DLG_TEXT_BASE[574] break;
	}
	return sText;
}

void LombardText()
{
	switch (drand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = DLG_TEXT_BASE[575];
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple(DLG_TEXT_BASE[576],DLG_TEXT_BASE[577]);
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = DLG_TEXT_BASE[578];
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple(DLG_TEXT_BASE[579],DLG_TEXT_BASE[580]);
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = DLG_TEXT_BASE[581];
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple(DLG_TEXT_BASE[582],DLG_TEXT_BASE[583]);
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = DLG_TEXT_BASE[584];
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple(DLG_TEXT_BASE[585],DLG_TEXT_BASE[586]);
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = DLG_TEXT_BASE[587];
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple(DLG_TEXT_BASE[588],DLG_TEXT_BASE[589]);
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = DLG_TEXT_BASE[590];
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple(DLG_TEXT_BASE[591],DLG_TEXT_BASE[592]);
		break;
	}
}