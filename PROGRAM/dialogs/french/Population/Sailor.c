#include "SD\TEXT\DIALOGS\Common_population.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = DLG_TEXT_BASE[593]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[594];
					link.l1 = DLG_TEXT_BASE[595]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[596];
					link.l1.go = "crew";
					link.l2 = DLG_TEXT_BASE[597]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[598];
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[599],DLG_TEXT_BASE[600],DLG_TEXT_BASE[601]);
				link.l1 = DLG_TEXT_BASE[602]+GetFullName(pchar)+DLG_TEXT_BASE[603];
				link.l1.go = "question";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[604], DLG_TEXT_BASE[605]);
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = DLG_TEXT_BASE[606];
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[607];
				link.l1 = DLG_TEXT_BASE[608];
				link.l1.go = "question";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[609], DLG_TEXT_BASE[610]);
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = DLG_TEXT_BASE[611];
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+DLG_TEXT_BASE[612], 
				DLG_TEXT_BASE[613], 
				DLG_TEXT_BASE[614],
                DLG_TEXT_BASE[615], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[616], 
				DLG_TEXT_BASE[617],
                DLG_TEXT_BASE[618], 
				DLG_TEXT_BASE[619], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (drand(2))
			{
				case 0: sTemp = DLG_TEXT_BASE[620]; break;
				case 1: sTemp = DLG_TEXT_BASE[621]; break;
				case 2: sTemp = DLG_TEXT_BASE[622]; break;
			}
			dialog.text = sTemp;
			link.l1 = DLG_TEXT_BASE[623];
			link.l1.go = "crew_1";
			link.l2 = DLG_TEXT_BASE[624];
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = DLG_TEXT_BASE[625]; break;
				case 1: sTemp = DLG_TEXT_BASE[626]; break;
				case 2: sTemp = DLG_TEXT_BASE[627]; break;
			}
			dialog.text = DLG_TEXT_BASE[628]+sti(npchar.quest.crew.qty)+DLG_TEXT_BASE[629]+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = DLG_TEXT_BASE[630];
				link.l1.go = "crew_2";
				link.l2 = DLG_TEXT_BASE[631];
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[632];
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+DLG_TEXT_BASE[633];
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = DLG_TEXT_BASE[634]+pchar.ship.name+DLG_TEXT_BASE[635];
				link.l1.go = "crew_3";
			}
			link.l2 = DLG_TEXT_BASE[636];
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = DLG_TEXT_BASE[637];
			link.l1 = DLG_TEXT_BASE[638];
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[639], DLG_TEXT_BASE[640]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[641],DLG_TEXT_BASE[642],DLG_TEXT_BASE[643]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
