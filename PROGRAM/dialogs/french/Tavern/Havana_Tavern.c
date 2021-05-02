#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[73]+ GetCityName(npchar.city) +DLG_TEXT_STR[74],
                          DLG_TEXT_STR[75], DLG_TEXT_STR[76],
                          DLG_TEXT_STR[77], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[78] + NPChar.name + DLG_TEXT_STR[79], DLG_TEXT_STR[80],
                      DLG_TEXT_STR[81], DLG_TEXT_STR[82], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = DLG_TEXT_STR[304] + pchar.questTemp.Slavetrader.ShipName+ DLG_TEXT_STR[305];
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = DLG_TEXT_STR[306];
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = DLG_TEXT_STR[307];
				link.l1.go = "caleuche";
			}
			if (pchar.questTemp.Ascold == "ToHavanna") // квест јскольда
            {
    			Link.l1 = DLG_TEXT_STR[500];
    			Link.l1.go = "Step_A1";
            }
		break;

		case "Havana_ratT_1":
			dialog.text = DLG_TEXT_STR[308];
			Link.l1 = DLG_TEXT_STR[309];
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = DLG_TEXT_STR[310];
			Link.l1 = DLG_TEXT_STR[311];
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = DLG_TEXT_STR[312];
			Link.l1 = DLG_TEXT_STR[313];
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = DLG_TEXT_STR[314];
			Link.l1 = DLG_TEXT_STR[315] + npchar.name + DLG_TEXT_STR[316];
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = DLG_TEXT_STR[317];
			link.l1 = DLG_TEXT_STR[318];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_STR[319]+DLG_TEXT_STR[320];
			link.l1 = DLG_TEXT_STR[321];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_STR[322];
			link.l1 = "...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_STR[323];
			link.l1 = DLG_TEXT_STR[324];
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;

		case "Step_A1":
			dialog.text = DLG_TEXT_STR[501];
			Link.l1 = DLG_TEXT_STR[502];
			Link.l1.go = "Step_A2";
		break;

		case "Step_A2":
			dialog.text = DLG_TEXT_STR[503];
			Link.l1 = DLG_TEXT_STR[504];
			Link.l1.go = "Step_A3";
		break;

		case "Step_A3":
			dialog.text = DLG_TEXT_STR[505];
			Link.l1 = DLG_TEXT_STR[506];
			Link.l1.go = "Step_A4";
		break;

		case "Step_A4":
			dialog.text = DLG_TEXT_STR[507];
			Link.l1 = DLG_TEXT_STR[508];
			Link.l1.go = "Step_A5";
		break;

		case "Step_A5":
			dialog.text = DLG_TEXT_STR[509];
			Link.l1 = DLG_TEXT_STR[510];
			Link.l1.go = "exit";
			pchar.questTemp.Ascold = "SeekInformatorHavanna";
			AddQuestRecord("Ascold", "6");
            ref sld = GetCharacter(NPC_GenerateCharacter("FernandoGonsales", "off_spa_1", "man", "man", 28, SPAIN, -1, true, "quest"));
            FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol5", "bullet", 200);
            LAi_SetBarmanType(sld);
           	sld.name 	= DLG_TEXT_STR[511];
			sld.lastname 	= DLG_TEXT_STR[512];
			sld.Dialog.Filename = "Quest\AscoldNpc.c";
			ChangeCharacterAddressGroup(sld, "Havana_townhallroom", "goto", "goto2");
            LAi_LocationFightDisable(&Locations[FindLocation("Havana_townhallroom")], true);
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

