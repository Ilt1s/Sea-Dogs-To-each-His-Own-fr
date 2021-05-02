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
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = DLG_TEXT_STR[351];
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//ѕортугалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = DLG_TEXT_STR[352];
                link.l1.go = "Portugal";
            }
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = DLG_TEXT_STR[353];
			link.l1 = DLG_TEXT_STR[354];
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = DLG_TEXT_STR[355]+DLG_TEXT_STR[356]+DLG_TEXT_STR[357];
			link.l1 = DLG_TEXT_STR[358];
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = DLG_TEXT_STR[359];
			link.l1 = DLG_TEXT_STR[360];
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = DLG_TEXT_STR[361];
			link.l1 = DLG_TEXT_STR[362];
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = DLG_TEXT_STR[363];
			link.l1 = DLG_TEXT_STR[364] + npchar.name + DLG_TEXT_STR[365];
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = DLG_TEXT_STR[366];
			link.l1 = DLG_TEXT_STR[367] + npchar.name + DLG_TEXT_STR[368];
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = DLG_TEXT_STR[369] + pchar.name + DLG_TEXT_STR[370];
			link.l1 = DLG_TEXT_STR[371];
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = DLG_TEXT_STR[372];
			link.l1 = DLG_TEXT_STR[373];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_STR[374];
			link.l1 = DLG_TEXT_STR[375];
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = DLG_TEXT_STR[376];
			link.l1 = DLG_TEXT_STR[377]+npchar.name+" !";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

