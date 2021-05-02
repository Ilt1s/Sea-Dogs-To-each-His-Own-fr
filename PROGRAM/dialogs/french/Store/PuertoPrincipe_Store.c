#include "SD\TEXT\DIALOGS\Quest_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.BlueBird == "toPuertoPrincipe")
			{
				link.l1 = DLG_TEXT_STR[143];
				link.l1.go = "BlueBird_1";
			}			
		break;
		case "BlueBird_1":
			if (isBadReputation(pchar, 5)) 
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[144], 
					DLG_TEXT_STR[145], 
					DLG_TEXT_STR[146],
					DLG_TEXT_STR[147], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[148], 
					DLG_TEXT_STR[149],
					DLG_TEXT_STR[150], 
					DLG_TEXT_STR[151], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("BlueBird_close", "", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = DLG_TEXT_STR[152];
				link.l1 = DLG_TEXT_STR[153];
				link.l1.go = "BlueBird_2";
			}
		break;

		case "BlueBird_close":
			dialog.text = DLG_TEXT_STR[154];
			link.l1 = DLG_TEXT_STR[155];
			link.l1.go = "exit";
		break;

		case "BlueBird_2":
			dialog.text = DLG_TEXT_STR[156];
			link.l1 = DLG_TEXT_STR[157];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_STR[158];
			link.l1 = DLG_TEXT_STR[159];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_STR[160];
			link.l1 = DLG_TEXT_STR[161];
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = DLG_TEXT_STR[162];
			link.l1 = DLG_TEXT_STR[163];
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = DLG_TEXT_STR[164];
			link.l1 = DLG_TEXT_STR[165];
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = DLG_TEXT_STR[166];
			link.l1 = DLG_TEXT_STR[167];
			link.l1.go = "BlueBird_8";
		break;
		case "BlueBird_8":
			dialog.text = DLG_TEXT_STR[168];
			link.l1 = DLG_TEXT_STR[169];
			link.l1.go = "BlueBird_9";
		break;
		case "BlueBird_9":
			dialog.text = DLG_TEXT_STR[170];
			link.l1 = DLG_TEXT_STR[171];
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toSeekBermudes";
			AddQuestRecord("Xebeca_BlueBird", "4");
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);
}
