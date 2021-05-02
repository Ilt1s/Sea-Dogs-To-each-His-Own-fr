#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
#include "SD\TEXT\DIALOGS\Common_poorman.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && sti(Pchar.money) >= 2000) 
			{
				dialog.text = DLG_TEXT_BASE[185];
				link.l1 = DLG_TEXT_BASE[186];
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10] + GetFullName(npchar) + DLG_TEXT_BASE[11], 
					DLG_TEXT_BASE[12] + GetAddress_Form(NPChar) +  DLG_TEXT_BASE[13] + GetFullName(npchar) + ".", 
					DLG_TEXT_BASE[14] + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + DLG_TEXT_BASE[15]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[16], DLG_TEXT_BASE[17]);
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = DLG_TEXT_BASE[187];
					link.l2.go = "trial";
				}
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[24], 
					DLG_TEXT_BASE[25], 
					DLG_TEXT_BASE[26],
					DLG_TEXT_BASE[27], "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[33], 
					DLG_TEXT_BASE[34],
					DLG_TEXT_BASE[35], 
					DLG_TEXT_BASE[36], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[37], DLG_TEXT_BASE[38]);
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = DLG_TEXT_BASE[188];
					link.l2.go = "trial";
				}
				link.l3 = LinkRandPhrase(DLG_TEXT_BASE[39], 
					DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]);
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[44], 
				DLG_TEXT_BASE[45]);
			link.l1 = DLG_TEXT_BASE[46];
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase(DLG_TEXT_BASE[47] + GetAddress_Form(NPChar) +  DLG_TEXT_BASE[48],
					DLG_TEXT_BASE[49] + GetAddress_Form(NPChar) +  DLG_TEXT_BASE[50]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[51], DLG_TEXT_BASE[52]);
				link.l1.go = "exit";
				Link.l2 = DLG_TEXT_BASE[53];
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase(DLG_TEXT_BASE[54], DLG_TEXT_BASE[55] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[56]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = DLG_TEXT_BASE[59] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[60];
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = DLG_TEXT_BASE[61];
				link.l1 = DLG_TEXT_BASE[62];
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = DLG_TEXT_BASE[63] + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + DLG_TEXT_BASE[64];
				link.l1 = DLG_TEXT_BASE[65];
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = DLG_TEXT_BASE[66] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[67];
				link.l1 = DLG_TEXT_BASE[68];
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = DLG_TEXT_BASE[72] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[73];
				link.l1 = DLG_TEXT_BASE[74];
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = DLG_TEXT_BASE[69] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[70];
				link.l1 = DLG_TEXT_BASE[71];
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = DLG_TEXT_BASE[75] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[76];
				link.l1 = DLG_TEXT_BASE[77];
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 10000)
			{
				dialog.text = DLG_TEXT_BASE[78] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[79] + FindRussianMoneyString(iTemp) + DLG_TEXT_BASE[80];
				link.l1 = DLG_TEXT_BASE[81];
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			dialog.text = DLG_TEXT_BASE[189];
			link.l1 = DLG_TEXT_BASE[190];
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = DLG_TEXT_BASE[191];
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = DLG_TEXT_BASE[192];
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = DLG_TEXT_BASE[193];
			link.l1 = DLG_TEXT_BASE[194];
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = DLG_TEXT_BASE[195];
			link.l1 = DLG_TEXT_BASE[196];
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			LAi_RemoveLoginTime(npchar);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 23.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = DLG_TEXT_BASE[197];
			link.l1 = DLG_TEXT_BASE[198];
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = DLG_TEXT_BASE[199];
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = DLG_TEXT_BASE[200];
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[201];
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = DLG_TEXT_BASE[202];
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = DLG_TEXT_BASE[203];
			link.l1 = DLG_TEXT_BASE[204];
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = DLG_TEXT_BASE[205];
			link.l1 = DLG_TEXT_BASE[206];
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = DLG_TEXT_BASE[207];
			link.l1 = DLG_TEXT_BASE[208];
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = DLG_TEXT_BASE[209];
			link.l1 = DLG_TEXT_BASE[210];
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info(DLG_TEXT_BASE[211]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[212];
			link.l1 = DLG_TEXT_BASE[213];
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = DLG_TEXT_BASE[214];
			link.l1 = DLG_TEXT_BASE[215];
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
	}
}