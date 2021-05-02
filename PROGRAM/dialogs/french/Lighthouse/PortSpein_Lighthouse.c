#include "SD\TEXT\DIALOGS\Quest_lighthouse.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_LI[0], DLG_TEXT_LI[1]), DLG_TEXT_LI[2] + GetAddress_Form(NPChar) + " ?", DLG_TEXT_LI[3], DLG_TEXT_LI[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_LI[5], DLG_TEXT_LI[6]), DLG_TEXT_LI[7],
                      DLG_TEXT_LI[8], DLG_TEXT_LI[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = DLG_TEXT_LI[13];
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_LI[14];
			link.l1 = DLG_TEXT_LI[15];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_LI[16]+DLG_TEXT_LI[17]+DLG_TEXT_LI[18]+DLG_TEXT_LI[19];
			link.l1 = DLG_TEXT_LI[20];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_LI[21];
			link.l1 = DLG_TEXT_LI[22];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_LI[23];
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = DLG_TEXT_LI[24];
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = DLG_TEXT_LI[25];
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}