#include "SD\TEXT\DIALOGS\Quest_Shipyard.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[0], DLG_TEXT_SHY[1]), DLG_TEXT_SHY[2], DLG_TEXT_SHY[3],
                          DLG_TEXT_SHY[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[5], DLG_TEXT_SHY[6]), DLG_TEXT_SHY[7],
                      DLG_TEXT_SHY[8], DLG_TEXT_SHY[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = DLG_TEXT_SHY[44];
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = DLG_TEXT_SHY[45]+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_OIL))+DLG_TEXT_SHY[46];
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ФМК-Мартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = DLG_TEXT_SHY[47]+GetFullName(pchar)+DLG_TEXT_SHY[48];
			link.l1 = DLG_TEXT_SHY[49];
			link.l1.go = "FMQM_1";
		break;
		
		case "FMQM_1":
			dialog.text = DLG_TEXT_SHY[50];
			link.l1 = DLG_TEXT_SHY[51];
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = DLG_TEXT_SHY[52];
			link.l1 = DLG_TEXT_SHY[53];
			link.l1.go = "FMQM_3";
			link.l2 = DLG_TEXT_SHY[54];
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = DLG_TEXT_SHY[55];
			link.l1 = DLG_TEXT_SHY[56];
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратская линейка
			dialog.text = DLG_TEXT_SHY[57]+sTemp+DLG_TEXT_SHY[58];
			link.l1 = DLG_TEXT_SHY[59];
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = DLG_TEXT_SHY[60];
			link.l1 = DLG_TEXT_SHY[61];
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = DLG_TEXT_SHY[62];
			link.l1 = DLG_TEXT_SHY[63];
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = DLG_TEXT_SHY[64];
			link.l1 = DLG_TEXT_SHY[65];
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = DLG_TEXT_SHY[66];
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = DLG_TEXT_SHY[67];
			link.l1 = DLG_TEXT_SHY[68];
			link.l1.go = "FMQM_10";
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

