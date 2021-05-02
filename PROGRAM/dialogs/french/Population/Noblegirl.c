#include "SD\TEXT\DIALOGS\Common_population.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = DLG_TEXT_BASE[405]+NationNameGenitive(sti(pchar.nation))+DLG_TEXT_BASE[406];
					link.l1 = DLG_TEXT_BASE[407];
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[408]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[409], DLG_TEXT_BASE[410]);
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[411];
					link.l1.go = "question";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[412], DLG_TEXT_BASE[413]);
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = DLG_TEXT_BASE[414]+NationNameAblative(sti(pchar.nation))+DLG_TEXT_BASE[415];
					link.l1 = DLG_TEXT_BASE[416];
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[417], 
					DLG_TEXT_BASE[418], 
					DLG_TEXT_BASE[419],
					DLG_TEXT_BASE[420], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[421], 
					DLG_TEXT_BASE[422],
					DLG_TEXT_BASE[423], 
					DLG_TEXT_BASE[424], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[425],DLG_TEXT_BASE[426],DLG_TEXT_BASE[427]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[428],DLG_TEXT_BASE[429],DLG_TEXT_BASE[430]);
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[431],DLG_TEXT_BASE[432]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[433],DLG_TEXT_BASE[434],DLG_TEXT_BASE[435]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
