#include "SD\TEXT\DIALOGS\Quest_Mayor.h"// ������ �� �������
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
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = DLG_TEXT_MR[14];
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_MR[15];
			link.l1 = DLG_TEXT_MR[16];
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}


