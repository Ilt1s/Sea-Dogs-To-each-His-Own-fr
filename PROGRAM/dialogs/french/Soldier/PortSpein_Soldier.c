#include "SD\TEXT\DIALOGS\Quest_Soldier.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SLD[0], DLG_TEXT_SLD[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_SLD[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_SLD[3],
                          DLG_TEXT_SLD[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SLD[5], DLG_TEXT_SLD[6]), DLG_TEXT_SLD[7],
                      DLG_TEXT_SLD[8], DLG_TEXT_SLD[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//���� �������
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = DLG_TEXT_SLD[10];
				link.l1.go = "Consumption";
			}
		break;
		
		//���� �������
		case "Consumption":
			dialog.text = DLG_TEXT_SLD[11];
			link.l1 = DLG_TEXT_SLD[12];
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}