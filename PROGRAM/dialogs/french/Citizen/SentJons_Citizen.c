#include "SD\TEXT\DIALOGS\Quest_Citizen.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CZ[0], DLG_TEXT_CZ[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CZ[2], DLG_TEXT_CZ[3]);
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = DLG_TEXT_CZ[66];
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = DLG_TEXT_CZ[67];
				link.l1 = DLG_TEXT_CZ[68];
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_CZ[69],DLG_TEXT_CZ[70],DLG_TEXT_CZ[71]);
				link.l1 = DLG_TEXT_CZ[72];
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_CZ[73],DLG_TEXT_CZ[74],DLG_TEXT_CZ[75]), LinkRandPhrase(DLG_TEXT_CZ[76],DLG_TEXT_CZ[77],DLG_TEXT_CZ[78]));
			link.l1 = DLG_TEXT_CZ[79];
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = DLG_TEXT_CZ[80];
			link.l1 = DLG_TEXT_CZ[81];
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = DLG_TEXT_CZ[4]+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = DLG_TEXT_CZ[5];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[6];
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = DLG_TEXT_CZ[7];

            link.l1 = DLG_TEXT_CZ[8];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[9];
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

