#include "SD\TEXT\DIALOGS\Common_cemeteryman.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3]+ GetSexPhrase("sale pirate","salope") +" !", ""+ GetSexPhrase("Sale tueur ! Garde !!!", DLG_TEXT_BASE[4]+ GetSexPhrase("sale pirate","salope") +DLG_TEXT_BASE[5]));
				link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7] + XI_ConvertString("Colony" + npchar.city + "Gen") + " !"), 
					RandPhraseSimple("Allez au diable !", DLG_TEXT_BASE[8]));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[9]+GetFullName(npchar)+DLG_TEXT_BASE[10], DLG_TEXT_BASE[11]+GetFullName(npchar)+DLG_TEXT_BASE[12]);
				link.l1 = "Salutation, "+npchar.name+" ! Mon nom est : "+GetFullName(pchar)+DLG_TEXT_BASE[13];
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[14]+GetFullName(pchar)+" ! Entrez, entrez !";
				link.l1 = DLG_TEXT_BASE[15];
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = DLG_TEXT_BASE[16];
			link.l1 = DLG_TEXT_BASE[17];
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = DLG_TEXT_BASE[18];
			link.l1 = DLG_TEXT_BASE[19];
			link.l1.go = "trade";
			link.l2 = DLG_TEXT_BASE[20];
			link.l2.go = "quests";
			link.l3 = DLG_TEXT_BASE[21];
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = DLG_TEXT_BASE[22];
			link.l1 = DLG_TEXT_BASE[23];
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = DLG_TEXT_BASE[24];
			link.l1 = DLG_TEXT_BASE[25];
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = DLG_TEXT_BASE[26]+npchar.name+DLG_TEXT_BASE[27]+npchar.name+DLG_TEXT_BASE[28];
			link.l1 = DLG_TEXT_BASE[29];
			link.l1.go = "trade";
			link.l2 = DLG_TEXT_BASE[30];
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Vous "+GetFullName(pchar)+", vous vous prenez pour un voleur ? Embobineur !!!", DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]);
			link.l1 = DLG_TEXT_BASE[33];
			link.l1.go = "fight";
		break;
	}
}