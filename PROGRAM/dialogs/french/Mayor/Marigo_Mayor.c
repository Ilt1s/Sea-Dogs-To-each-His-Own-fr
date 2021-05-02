#include "SD\TEXT\DIALOGS\Quest_Mayor.h"// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = DLG_TEXT_MR[60];
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = DLG_TEXT_MR[268];
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = DLG_TEXT_MR[269];
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[61],DLG_TEXT_MR[62]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[63], DLG_TEXT_MR[64]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = DLG_TEXT_MR[65];
			link.l1 = DLG_TEXT_MR[66];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_MR[67];
			link.l1 = DLG_TEXT_MR[68];
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = DLG_TEXT_MR[69];
			link.l1 = DLG_TEXT_MR[70];
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = DLG_TEXT_MR[71]+DLG_TEXT_MR[72]+DLG_TEXT_MR[73];
			link.l1 = DLG_TEXT_MR[74];
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			dialog.text = DLG_TEXT_MR[270];
			link.l1 = DLG_TEXT_MR[271];
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = DLG_TEXT_MR[272];
			link.l1 = DLG_TEXT_MR[273];
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = DLG_TEXT_MR[274];
			link.l1 = DLG_TEXT_MR[275];
			link.l1.go = "FMQN_3";
			link.l2 = DLG_TEXT_MR[276];
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = DLG_TEXT_MR[277];
			link.l1 = DLG_TEXT_MR[278];
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = DLG_TEXT_MR[279];
			link.l1 = DLG_TEXT_MR[280];
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
		break;
		
		case "FMQN_7":
			dialog.text = DLG_TEXT_MR[281]+GetFullName(pchar)+DLG_TEXT_MR[282];
			link.l1 = DLG_TEXT_MR[283];
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = DLG_TEXT_MR[284];
			link.l1 = DLG_TEXT_MR[285];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = DLG_TEXT_MR[286];
			link.l1 = DLG_TEXT_MR[287];
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = DLG_TEXT_MR[288];
			link.l1 = DLG_TEXT_MR[289];
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = DLG_TEXT_MR[290];
			link.l1 = DLG_TEXT_MR[291];
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = DLG_TEXT_MR[292];
			link.l1 = DLG_TEXT_MR[293];
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = DLG_TEXT_MR[294];
			link.l1 = DLG_TEXT_MR[295];
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = DLG_TEXT_MR[296];
			link.l1 = DLG_TEXT_MR[297];
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = DLG_TEXT_MR[298];
			link.l1 = DLG_TEXT_MR[299];
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

