#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[83], DLG_TEXT_STR[84] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_STR[85] + GetAddress_Form(NPChar) + "...", DLG_TEXT_STR[86],
                          DLG_TEXT_STR[87], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[88], DLG_TEXT_STR[89]), DLG_TEXT_STR[90],
                      DLG_TEXT_STR[91], DLG_TEXT_STR[92], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Ecoutez, "+npchar.name+ DLG_TEXT_STR[215];
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Ecoutez, "+npchar.name+ DLG_TEXT_STR[216];
				link.l1.go = "tieyasal";
			}
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = DLG_TEXT_STR[475];
				link.l1.go = "BlueBird_1";
			}
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_STR[217];
			link.l1 = DLG_TEXT_STR[218];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_STR[219];
			link.l1 = DLG_TEXT_STR[220];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_STR[221]+DLG_TEXT_STR[222]+DLG_TEXT_STR[223];
			link.l1 = DLG_TEXT_STR[224];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_STR[225];
			link.l1 = DLG_TEXT_STR[226];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = DLG_TEXT_STR[227]+DLG_TEXT_STR[228];
			link.l1 = DLG_TEXT_STR[229];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = DLG_TEXT_STR[230];
			link.l1 = DLG_TEXT_STR[231];
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = DLG_TEXT_STR[232];
			link.l1 = DLG_TEXT_STR[233]+npchar.name+DLG_TEXT_STR[234];
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = DLG_TEXT_STR[235]+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = DLG_TEXT_STR[236];
			link.l1 = DLG_TEXT_STR[237];
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = DLG_TEXT_STR[238];
			link.l1 = DLG_TEXT_STR[239];
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = DLG_TEXT_STR[240];
			link.l1 = DLG_TEXT_STR[241];
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
		
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[479], 
				DLG_TEXT_STR[480], 
				DLG_TEXT_STR[481],
                DLG_TEXT_STR[482], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[483], 
				DLG_TEXT_STR[484],
                DLG_TEXT_STR[485], 
				DLG_TEXT_STR[486], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "BlueBird_2":
			dialog.text = DLG_TEXT_STR[487];
			link.l1 = DLG_TEXT_STR[488];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_STR[489];
			link.l1 = DLG_TEXT_STR[490];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_STR[491];
			link.l1 = DLG_TEXT_STR[492];
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = DLG_TEXT_STR[493];
			link.l1 = DLG_TEXT_STR[494];
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = DLG_TEXT_STR[495];
			link.l1 = DLG_TEXT_STR[496];
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = DLG_TEXT_STR[497] + GetAddress_Form(NPChar) + DLG_TEXT_STR[498];
			link.l1 = DLG_TEXT_STR[499];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "3");
			pchar.questTemp.BlueBird = "toPuertoPrincipe";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}