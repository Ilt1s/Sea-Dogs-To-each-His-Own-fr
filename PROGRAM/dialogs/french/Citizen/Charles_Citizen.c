#include "SD\TEXT\DIALOGS\Quest_Citizen.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CZ[0], DLG_TEXT_CZ[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CZ[2], DLG_TEXT_CZ[3]);
		    link.l1.go = "exit";
		break;
		
		case "info":
        // �������� �� �������� ����� ���, �� �������
			dialog.text = DLG_TEXT_CZ[4]+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = DLG_TEXT_CZ[5];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[6];
			link.l2.go = "new question";
		break;
		
		case "town":
        // �������� �� �������� ��� ������, �� �������
			dialog.text = DLG_TEXT_CZ[7];

            link.l1 = DLG_TEXT_CZ[8];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[9];
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
